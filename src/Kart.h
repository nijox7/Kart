#include <QObject>
#include <QImage>
#include <iostream>

using namespace std;

class Kart : public QObject
{
  Q_OBJECT
  Q_PROPERTY(double x READ x WRITE setX NOTIFY xChanged)
  Q_PROPERTY(double y READ y WRITE setY NOTIFY yChanged)
  Q_PROPERTY(double angle READ angle WRITE setAngle NOTIFY angleChanged)

public:
  Kart(QObject* parent = nullptr, double max_x=960, double max_y=540, double max_speed = 15, char* src_img="img/vecteezy_car.png");

  double x()
  {
    return k_x;
  }

  double y()
  {
    return k_y;
  }

  double angle()
  {
    return k_angle;
  }

  double speedx()
  {
    return k_speedx;
  }

  double speedy()
  {
    return k_speedy;
  }

  void setX(double val)
  {
    if (k_x != val){
      k_x = val;
      emit xChanged();
    }
  }

  void setY(double val)
  {
    if (k_y != val){
      k_y = val;
      emit yChanged();
    }
  }

  void setAngle(double val)
  {
    while (val < 0) val += 360;
    while (val >= 360) val -= 360;
    if (k_angle != val){
      k_angle = val;
      emit angleChanged();
    }
  }

  void setSpeedx(double val)
  {
    if (k_speedx != val) k_speedx = val;
  }

  void setSpeedy(double val)
  {
    if (k_speedy != val) k_speedy = val;
  }

  Q_INVOKABLE void setGasing(bool val)
  {
    gasing = val;
  }

  Q_INVOKABLE void setBraking(bool val)
  {
    braking = val;
  }

  Q_INVOKABLE double getHeight()
  {
    return height;
  }

  Q_INVOKABLE double getWidth()
  {
    return width;
  }

  Q_INVOKABLE void setSpeed(double val)
  {
    if (speed != val) speed = val;
  }

  Q_INVOKABLE QString getSrcImg()
  {
    /* Returns the source image for Qml's code */
    // std::cout << "../" + QString(src_img); 
    return "../" + QString(src_img); // add "../" to go to the project's root
  }

  Q_INVOKABLE void up();
  Q_INVOKABLE void right();
  Q_INVOKABLE void down();
  Q_INVOKABLE void left();
  Q_INVOKABLE void brake();
  Q_INVOKABLE void gas();
  Q_INVOKABLE void targetMouse(double m_x, double m_y);

  void printState();
  void updateSpeedxy();
  void updatePosition();
  void updateMovement();

signals:
  void xChanged();
  void yChanged();
  void angleChanged();

private:
  // std::string source_image;
  QImage img;
  double height;
  double width;
  char* src_img;
  double k_x;
  double k_y;
  double k_speedx;
  double k_speedy;
  double speed;
  double k_angle; // angle in degrees
  double mouse_x;
  double mouse_y;

  double max_speed;
  double max_x;
  double max_y;
  bool gasing;
  bool braking;
};