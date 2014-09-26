import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    id: display
    anchors.fill: parent
    width: 800
    height: 600
    signal itemSelected(string id)
    border.width: 0
    color: "#000000"
    RadialGradient {
        id:background
        anchors.fill: parent
        cached: true
        gradient: Gradient {
            GradientStop {position: 0.0;color: "#3a3a3a";}
            GradientStop {position: 1.0;color: "#000000";}
        }
        verticalOffset: -(parent.width/2)
        verticalRadius: parent.height*2
        horizontalRadius: parent.width*(3/2)
    }
    Rectangle {id:testRect;width:100*itemscale_;height:100*itemscale_;color:"#450045";x:20;y:20;}
    GridView {
        id: grid
        anchors.fill: parent
        model: items_
        delegate: Column {
            Image {source: icon;anchors.horizontalCenter: parent.horizontalCenter}
            Text {text: title;anchors.horizontalCenter: parent.horizontalCenter}
        }
    }
}
