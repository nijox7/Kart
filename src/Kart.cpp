#include "Kart.h"
#include <cmath>

Kart::Kart(QObject* parent, double max_x, double max_y, double max_speed, char* src_img):  
  k_x(10),
  k_y(10),
  k_speedx(0),
  k_speedy(0),
  k_angle(0),
  max_speed(max_speed),
  max_x(max_x),
  max_y(max_y),
  mouse_x(k_x),
  mouse_y(k_y),
  gasing(false),
  braking(false),
  src_img(src_img)
{
  if(img.load(src_img) == false) {
    cout << "Problème d'ouverture du fichier: " << src_img << "\n";
    exit(1);
  }
  width = img.width() * 0.02;
  height = img.height() * 0.02;
}

void Kart::up()
{
  Kart::setAngle(0);
}

void Kart::right()
{
  Kart::setAngle(90);
}

void Kart::down()
{
  Kart::setAngle(180);
}

void Kart::left()
{
  Kart::setAngle(270);
}

void Kart::brake()
{
  /* Slowing the kart */
  double new_speed = speed - 2.5;
  if (new_speed < 1) speed = 0;
  else speed = new_speed;
}

void Kart::gas()
{
  /* Increasing the speed */
  double new_speed = speed + (max_speed - new_speed)/max_speed * 5;
  if (new_speed >= max_speed) speed = max_speed;
  else speed = new_speed;
}

void Kart::printState()
{
  cout  << "Kart state: x=" << k_x
        << ", y=" << k_y
        << ", speedx=" << k_speedx
        << ", speedy=" << k_speedy
        << ", angle=" << k_angle
        << "\n";
}

double radToDeg(double radAngle)
{
  /* Converts radians to degrees */
  return radAngle * 180 / 3.14159;
}

double degToRad(double degAngle)
{
  /* Converts degrees to radians */
  return degAngle * 3.14159 / 180;
}

void Kart::updateSpeedxy()
{
  /*
    Updating speed vector with the angle
  */

  // Calculating (speedx, speedy) with the angle and the speed
  double rad;
  if (0 <= k_angle && k_angle < 90) {
    rad = degToRad(k_angle);
    k_speedx = sin(rad) * speed;
    k_speedy = - cos(rad) * speed;
  }
  else if (90 <= k_angle && k_angle < 180) {
    rad = degToRad(k_angle - 90);
    k_speedx = cos(rad) * speed;
    k_speedy = sin(rad) * speed;
  }
  else if (180 <= k_angle && k_angle < 270) {
    rad = degToRad(k_angle - 180);
    k_speedx = - sin(rad) * speed;
    k_speedy = cos(rad) * speed;
  }
  else if (270 <= k_angle && k_angle < 360) {
    rad = degToRad(k_angle - 270);
    k_speedx = - cos(rad) * speed;;
    k_speedy = - sin(rad) * speed;;
  }
  else { // error, k_angle >= 360
    cout << "Error condition \"0 <= k_angle <= 359\" not respected.\n";
    exit(1);
  }
}

void Kart::updatePosition()
{
  // Checks if the next position is available
  if (k_x + k_speedx < 0 || k_x + k_speedx > max_x || k_y + k_speedy < 0 || k_y + k_speedy > max_y) {
    speed = 0; // if nex position is unavailable, speed down to 0
  }
  else { // update the position
    Kart::setX(k_x + k_speedx);
    Kart::setY(k_y + k_speedy);
  }
}

void Kart::updateMovement()
{
  /*
    Updating movement: speed, position of the Kart
  */

  Kart::updateSpeedxy();
  Kart::updatePosition();
  if (gasing) Kart::gas();
  if (braking) Kart::brake();
  if (speed>1) speed = speed - 0.1; // losing speed at each frame (frictional force)
}


void Kart::targetMouse(double m_x, double m_y)
{
  /*
    Target the mouse by changing the kart's angle
  */

  double diff_x, diff_y, angle;
  diff_x = m_x - k_x;
  diff_y = m_y - k_y;

  if (diff_x > 0 && diff_y >= 0) {
    angle = 90 + radToDeg(atan(diff_y / diff_x));
  }
  else if (diff_x < 0 && diff_y <= 0) {
    angle = 270 + radToDeg(atan(diff_y / diff_x));
  }
  else if (diff_x >= 0 && diff_y < 0) {
    angle = -radToDeg(atan(diff_x / diff_y));
  }
  else if (diff_x <= 0 && diff_y > 0) {
    angle = 180 - radToDeg(atan(diff_x / diff_y));
  }
  else {
    cout << "Error, no case possible\n";
    exit(1);
  }
  Kart::setAngle(angle);
}