import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    id: display
    anchors.fill: parent
    width: 800
    height: 600
    signal itemSelected(string id)
    onItemSelected: console.log(id)
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
    ListModel {
        id: listModel
        ListElement {
            icon: "file:///home/havard/Code/build-Lenny-Desktop_Qt_5_3_0_GCC_64bit-Debug/assets/ffx.png"
            title: "Final Fantasy X"
            itemId: "jason"
        }
        ListElement {
            icon: "file:///home/havard/Code/build-Lenny-Desktop_Qt_5_3_0_GCC_64bit-Debug/assets/dishonored.png"
            title: "Dishonored"
            itemId: "steam"
        }
    }

    GridView {
        id: grid
        anchors.fill: parent
        model: items_
        clip: true
        focus: true
        cellWidth: 100*itemscale_
        cellHeight: 175*itemscale_
        delegate: Column {
            MouseArea {height: grid.cellHeight;width:grid.cellWidth;id: delMA;
                onClicked: display.itemSelected(itemId)
                Rectangle{id: delSel;radius: 5*itemscale_;
                    color:"black";opacity:0;
                    x:grid.currentItem.x;y:grid.currentItem.y;
                    width:grid.cellWidth;height:grid.cellHeight;
                    transitions: Transition{
                        NumberAnimation{duration: 280;properties:"opacity";easing.type: Easing.InCirc}
                    }
                }
                Glow{id:delGlow;anchors.fill: delImg;radius: 12;samples: 16;color:"white";source:delImg;opacity: 0;transitions: Transition{
                        NumberAnimation{duration: 400;properties:"opacity";easing.type: Easing.InCirc}
                    }}

                Image {id: delImg;source: icon;anchors.horizontalCenter: parent.horizontalCenter;asynchronous: true;
                    fillMode: Image.PreserveAspectFit;width:grid.cellWidth;height:grid.cellHeight-25}
                Text {id:delText;text: title;color:"#ffffff";
                    anchors.horizontalCenter: parent.horizontalCenter;x:parent.width/2;y:parent.height-18;}

                states: [ State {name:"selected";when:delMA.pressed
                        PropertyChanges{target: delSel;opacity:0.25}
//                        PropertyChanges{target: delGlow;opacity:1}
                    },
                    State {name:"deselected";when:delMA.left
                        PropertyChanges{target: delSel;opacity:0}
//                        PropertyChanges{target: delGlow;opacity:0}
                    }]
            }
        }
    }
}
