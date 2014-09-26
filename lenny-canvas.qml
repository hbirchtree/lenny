import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    id: display
    anchors.fill: parent
    width: 800
    height: 600
    antialiasing: true
    border.width: 0
    color: "#000000"
    RadialGradient {
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
    GridView {

    }
}
