#include "Field.h"
#include <cmath>

#define ARDUINO_PATH "/dev/ttyACM0"

Field::Field(QObject* parent, int width, int height):
  f_width(width),
  f_height(height),
  f_ball(parent),
  f_kart(parent, width, height),
  obstacleList(),
  file(ARDUINO_PATH),
  refresh_time(1)
{
  // Initialize obstacles
  obstacleList.append(new Obstacle(this, f_width/1.5, f_height/2 - 25, 100, 300));
  obstacleList.append(new Obstacle(this, f_width/4, f_height/2 - 25, 100, 600));
  obstacleList.append(new Obstacle(this, f_width/1.2, f_height/5 - 25, 200, 200));

  if (!file) {
    cout << "ERROR: Failed to open " << ARDUINO_PATH << ".\n";
    controllerActive = false;
    refresh_time = 16;
    // exit(1);
  }

  // Starting the timer to update all the objects
  connect(&timer, &QTimer::timeout, this, &Field::update);
  timer.start(refresh_time); // 16 ms => 60 frames per second
}

bool Field::detectCollision()
{
  /*
    Detects collisions between the kart and the ball
  */

  double distance = sqrtl(powl((f_ball.x() - f_kart.x()), 2) + powl((f_ball.y() - f_kart.y()), 2));
  if (distance < f_ball.size()) return true; 
  return false;
}

double distance(double x1, double y1, double x2, double y2)
{
  return sqrtl(powl((x1 - x2), 2) + powl((y1 - y2), 2));
}

bool Field::detectObstCollision(Obstacle* obs, double x, double y, double radius)
{
  /*
    Detects collision between the ball and the obstacle
    --
    Considers obstacle hitbox as a circle inside the rectangle
  */
  double topleft_x = obs->x();
  double topleft_y = obs->y();
  double topright_x = obs->x() + obs->width();
  double topright_y = obs->y();
  double bottleft_x = obs->x() ;
  double bottleft_y = obs->y() + obs->height();
  double bottright_x = obs->x() + obs->width();
  double bottright_y = obs->y() + obs->height();

  // Left
  if (y > topleft_y && y < bottleft_y && (topleft_x - x < radius) && (topright_x - x > 0))
    return true;

  // Top
  if (x > topleft_x && x < topright_x && (topleft_y - y < radius) && (bottleft_y - y > 0))
    return true;

  // Right
  if (y > topleft_y && y < bottleft_y && (x - topright_x < radius) && (x - topleft_x > 0))
    return true;

  // Bottom
  if (x > topleft_x && x < topright_x && (y - bottleft_y < radius) && (y - topleft_y > 0))
    return true;

  if (distance(x, y, bottleft_x,  bottleft_y) < radius) return true;
  if (distance(x, y, bottright_x, bottright_y) < radius) return true;
  if (distance(x, y, topright_x, topright_y) < radius) return true;
  if (distance(x, y, topleft_x, topleft_y) < radius) return true;

  return false;
}

void Field::updateCollision()
{
  double next_ball_x = f_ball.x() + f_ball.speedx();
  double next_ball_y = f_ball.y() + f_ball.speedy();

  // Collisions between the Ball and the Kart
  if (detectCollision() == true){
    f_ball.setSpeedx(f_ball.speedx() + f_kart.speedx());
    f_ball.setSpeedy(f_ball.speedy() + f_kart.speedy());
  }

  // Collisions between the Ball and the walls
  if (next_ball_x > f_width  || next_ball_x < 0) f_ball.setSpeedx(-f_ball.speedx());
  if (next_ball_y > f_height || next_ball_y < 0) f_ball.setSpeedy(-f_ball.speedy());

  // Collisions between the Ball and the obstacles
  for (Obstacle* obst : obstacleList){
    if (detectObstCollision(obst, next_ball_x, next_ball_y, f_ball.size()/2)){
      if (f_ball.x() > obst->x() && f_ball.x() < obst->x() + obst->width()){
        // top or bottom
        f_ball.setSpeedy(-f_ball.speedy());
      }
      else if (f_ball.y() > obst->y() && f_ball.y() < obst->y() + obst->height()){
        // right or left
        f_ball.setSpeedx(-f_ball.speedx());
      }
      break; // stop on the first collision detected
    }
  }

  // Collisions between the Kart and the obstacles
  for (Obstacle* obst : obstacleList){
    if (detectObstCollision(obst, f_kart.x() + f_kart.speedx(), f_kart.y() + f_kart.speedy(), f_kart.getWidth()/2)){
      f_kart.setSpeed(0);
    }
  }
}

bool Field::scored()
{
  /*
    Happens when scored (when ball collides with the goal)
  */
  if (f_ball.x() > f_width - 50 
      && f_ball.x() < f_width 
      && f_ball.y() > f_height/2 - 100 
      && f_ball.y() < f_height/2 + 100) return true;
  return false;
}

void Field::resetBall()
{
  /*
    Move the ball to the center of the field and resets its speed
  */
  f_ball.setX(f_width/2);
  f_ball.setY(f_height/2);
  f_ball.setSpeedx(0);
  f_ball.setSpeedy(0);
}

void Field::update()
{
  /*
    Updating movements on the field
  */

  if (controllerActive){
  string line;
    getline(file, line);
    cout << "Arduino: " << line << "\n";
    bool gas = false;
    for (int i = 0; i < line.size(); i++){
      if (line[i] == 'R') f_kart.setAngle(f_kart.angle() + 5);
      if (line[i] == 'L') f_kart.setAngle(f_kart.angle() - 5);
      if (line[i] == 'A') gas = true;
    }
    f_kart.setGasing(gas);
  }

  if (scored()) resetBall();
  f_kart.updateSpeedxy();
  updateCollision();
  f_kart.updateMovement();
  f_ball.updateMovement();
  timer.start(refresh_time);
}