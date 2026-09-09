import QtQuick 2.15

Rectangle {
  width:  20 //model.width
  height: 20 // model.height
  x: 0//model.x
  y: 0//model.y
  color: "blue"
  Component.onCompleted: {
        console.log("Obstacle créé");
  }
}
