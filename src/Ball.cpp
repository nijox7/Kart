#include "Ball.h"

Ball::Ball(QObject* parent, double max_speed): 
  b_x(100),
  b_y(100),
  b_angle(0),
  b_speedx(0),
  b_speedy(0),
  b_size(50),
  max_speed(max_speed)
{
}

void Ball::right()
{
  b_speedx += 2;
}

void Ball::left()
{
  b_speedx -= 2;
}

void Ball::updateAngle()
{
  double new_angle;
  new_angle = b_angle + b_speedx;
  if (b_speedx > 0){
    while(new_angle >= 360) new_angle = new_angle - 360;
  }
  else if (b_speedx <= 0){
    while(new_angle < 0) new_angle = new_angle + 360;
  }
  Ball::setAngle(new_angle);
}

void Ball::updateSpeed()
{
  // Frictional force (speed decreasing each time)
  double frictional_force = 0.05;
  double threshold = 0.5;
  if (b_speedx > threshold)       b_speedx = b_speedx - frictional_force;
  else if (b_speedx < -threshold) b_speedx = b_speedx + frictional_force;
  else                            b_speedx = 0;

  if (b_speedy > threshold)       b_speedy = b_speedy - frictional_force;
  else if (b_speedy < -threshold) b_speedy = b_speedy + frictional_force;
  else                            b_speedy = 0;
}

void Ball::updateMovement()
{
  Ball::updateSpeed();
  Ball::updateAngle();
  Ball::setX(b_x + b_speedx);
  Ball::setY(b_y + b_speedy);
}