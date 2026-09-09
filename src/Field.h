#include <QObject>
#include <QTimer>
#include <QQmlListProperty>
#include "Kart.h"
#include "Ball.h"
#include "Obstacle.h"
#include <fstream>

class Field : public QObject
{
  Q_OBJECT

  Q_PROPERTY(int width  READ width  WRITE setWidth  NOTIFY widthChanged)
  Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
  Q_PROPERTY(QQmlListProperty<Obstacle> obstacles READ obstacles NOTIFY obstaclesChanged)

  public:
    Field(QObject* parent = nullptr, int width = 960, int height = 540);

    int width()
    {
      return f_width;
    }

    void setWidth(int val)
    {
      if (val != f_width){
        f_width = val;
        emit widthChanged();
      }
    }

    int height()
    {
      return f_height;
    }

    void setHeight(int val)
    {
      if (val != f_height){
        f_height = val;
        emit heightChanged();
      }
    }

    Kart* kart()
    {
      return &f_kart;
    }

    Ball* ball()
    {
      return &f_ball;
    }

    void update();
    void updateCollision();
    bool detectCollision();
    bool detectObstCollision(Obstacle*  obst, double x, double y, double radius);
    bool scored();

    Q_INVOKABLE void resetBall();

    Q_INVOKABLE int obstaclesCount() 
    {
      return obstacleList.count();
    }

    QQmlListProperty<Obstacle> obstacles()
    {
      return QQmlListProperty<Obstacle>(this, &obstacleList);
    }

  signals:
    void widthChanged();
    void heightChanged();
    void obstaclesChanged();

  private:
    int f_width;
    int f_height;
    Ball f_ball;
    Kart f_kart;
    QTimer timer;
    int score;
    QTimer timeLeft;
    QList<Obstacle*> obstacleList;
    ifstream file;
    bool controllerActive;
    int refresh_time;
};

Q_DECLARE_METATYPE(QQmlListProperty<Obstacle>) // TODO CEST CHELOU