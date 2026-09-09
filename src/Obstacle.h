#include <QObject>
#include <QList>

class Obstacle : public QObject
{
  Q_OBJECT

  Q_PROPERTY(double x READ x WRITE setX NOTIFY xChanged)
  Q_PROPERTY(double y READ y WRITE setY NOTIFY yChanged)
  Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
  Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)

public:
  Obstacle(QObject* parent=nullptr, double x=0, double y=0, double width=50, double height=50);

  double x()
  {
    return o_x;
  }

  double y()
  {
    return o_y;
  }

  double width()
  {
    return o_width;
  }

  double height()
  {
    return o_height;
  }

  void setX(double val)
  {
    if (o_x != val){
      o_x = val;
      emit xChanged();
    }
  }

  void setY(double val)
  {
    if (o_y != val) {
      o_y = val;
      emit yChanged();
    }
  }

  void setWidth(double val)
  {
    if (o_width != val) {
      o_width = val;
      emit widthChanged();
    }
  }

  void setHeight(double val)
  {
    if (o_height != val) {
      o_height = val;
      emit heightChanged();
    }
  }

signals:
  void xChanged();
  void yChanged();
  void widthChanged();
  void heightChanged();

private:
  // top left corner position in pixels
  double o_x;
  double o_y;

  // size in pixels
  double o_width;
  double o_height;
};