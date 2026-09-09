#include <QObject>
#include <iostream>

using namespace std;

class Ball : public QObject
{
  Q_OBJECT
  Q_PROPERTY(double x READ x WRITE setX NOTIFY xChanged)
  Q_PROPERTY(double y READ y WRITE setY NOTIFY yChanged)
  Q_PROPERTY(double angle READ angle WRITE setAngle NOTIFY angleChanged)

public:
  Ball(QObject* parent = nullptr, double max_speed=20);

  double x()
  {
    return b_x;
  }

  double y()
  {
    return b_y;
  }

  double angle()
  {
    return b_angle;
  }

  double speedx()
  {
    return b_speedx;
  }

  double speedy()
  {
    return b_speedy;
  }

  void setX(double val)
  {
    if (b_x != val){
      b_x = val;
      emit xChanged();
    }
  }

  void setY(double val)
  {
    if (b_y != val) {
      b_y = val;
      emit yChanged();
    }
  }

  void setAngle(double val)
  {
    if (b_angle != val){
      b_angle = val;
      emit angleChanged();
    }
  }

  void setSpeedx(double val)
  {
    if (b_speedx != val) {
      if (val > max_speed)        b_speedx = max_speed;
      else if (val < -max_speed)  b_speedx = -max_speed;
      else                        b_speedx = val;
    }
  }

  void setSpeedy(double val)
  {
    if (b_speedy != val) {
      if (val > max_speed)        b_speedy = max_speed;
      else if (val < -max_speed)  b_speedy = -max_speed;
      else                        b_speedy = val;
    }
  }

  Q_INVOKABLE int size()
  {
    return b_size;
  }

  Q_INVOKABLE void right();
  Q_INVOKABLE void left();

  void updateMovement();
  void updateAngle();
  void updateSpeed();

signals:
  void xChanged();
  void yChanged();
  void angleChanged();

private:
  double b_x;
  double b_y;
  double b_angle;
  double b_speedx;
  double b_speedy;
  double max_speed;
  double direction; // angle between 0 and 360 degrees
  int b_size;
};