import QtQuick 2.15
import QtQuick.Window 2.15

Window {
  width: field.width
  height: field.height
  visible: true
  title: qsTr("Kart")

  // Field
  Image {
    id: field_img
    anchors.fill: parent
    source: "../img/grass.jpg"
  }

  // Ball
  Image {
    id: ball_img
    width: ball.size()
    height: ball.size()
    source: "../img/ball.png"
    x: ball.x - ball.size()/2
    y: ball.y - ball.size()/2
    rotation: ball.angle
  }

  // Kart
  Image {
    id: kart_img
    source: kart.getSrcImg()
    width: kart.getWidth()
    height: kart.getHeight()
    x: kart.x - kart.getWidth()/2
    y: kart.y - kart.getHeight()/2
    focus: true
    rotation: kart.angle

    Keys.onPressed: (event) =>
    {
      if (event.key == Qt.Key_Left) {
        kart.left()
      }
      if (event.key == Qt.Key_Right) {
        kart.right();
      }
      if (event.key == Qt.Key_Up) {
        kart.up();
      }
      if (event.key == Qt.Key_Down) {
        kart.down();
      }
      if (event.key == Qt.Key_Z) {
        kart.setGasing(true);
      }
      if (event.key == Qt.Key_R) { // reset the ball
        field.resetBall();
      }
      if (event.key == Qt.Key_Shift) {
        kart.setBraking(true);
      }
    }

    Keys.onReleased: (event) =>
    {
      if (event.key == Qt.Key_Z) {
        kart.setGasing(false);
      }
      if (event.key == Qt.Key_Shift) {
        kart.setBraking(false);
      }
    }
  }

  // Goal
  Rectangle {
    id: goal
    width: 50
    height: 200
    color: "red"
    x: parent.width - goal.width
    y: parent.height/2 - goal.height/2
  }


  Rectangle {
    id: obst1
    x: parent.width / 1.5
    y: parent.height / 2 - 25
    width: 100
    height: 300
    color: "blue"
  }

  Rectangle {
    id: obst2
    x: parent.width / 4
    y: parent.height / 2 - 25
    width: 100
    height: 600
    color: "blue"
  }

  Rectangle {
    id: obst3
    x: parent.width / 1.2
    y: parent.height / 5 - 25
    width: 200
    height: 200
    color: "blue"
  }
  // obstacleList.append(new Obstacle(this, f_wi dth/1.5, f_height/2 - 25, 100, 300));
  // obstacleList.append(new Obstacle(this, f_width/4, f_height/2 - 25, 100, 600));
  // obstacleList.append(new Obstacle(this, f_width/1.2, f_height/5 - 25, 200, 200));

  MouseArea { 
    anchors.fill: parent
    hoverEnabled: true; 
    onPositionChanged: (mouse) => {
      kart.targetMouse(mouse.x, mouse.y);
    }
  }

  Repeater{
    model: field.obstacles
    delegate: Obstacle{}
  }

  Component.onCompleted: {
    console.log("field.obstacles.size()=", field.obstaclesCount());
  }
}
