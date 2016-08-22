import QtQuick 2.3
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import com.TicTacToe.ViewModel 1.0

Item {
    id: cellItem
    width: 25
    height: 25
    antialiasing: true
    signal clicked
    property int arrayX : 0
    property int arrayY : 0

    Connections {
        target: viewmodel
        onChangeCellState: {
            if(x == arrayX && y == arrayY) {
                cellItem.state = stateString;
            }
        }
    }

    Rectangle {
        id: cell
        anchors.fill: parent
        color: "transparent"


        RectangularGlow {
            id: cellGlow
            visible: false
            anchors.fill: cellRect
            glowRadius:  2
            cornerRadius: 5
            spread: 0.2
            color: "#55ff55"
        }

        Rectangle {
            id: cellRect
            anchors.centerIn: parent
            width: parent.width
            height: parent.height
            radius: 3
            border.width: 0
            color: "transparent"
            Image {
                id: cellImg
                width: parent.width
                height: parent.height
                anchors.centerIn: parent
                source: "CellGray.png"
            }
        }
        Gradient {
            id: gradientFocused
            GradientStop { position: 0.0; color: "#d4dee1"}
            GradientStop { position: 1.0; color: "#a9c0c8"}
        }

        Gradient {
            id: gradientDefault
            GradientStop { position: 0.0; color: "#f2f5f6"}
            GradientStop { position: 1.0; color: "#c8d7dc"}
        }
    }

    MouseArea {
        id: mouseArea
        hoverEnabled: true
        anchors.fill: cellItem
        onClicked:  {
            cellItem.clicked();
        }

        onEntered: {
            onFocusIn()
        }

        onCanceled:{
            onFocusOut()
        }

        onExited: {
            onFocusOut()
        }
    }

    state: "empty"

    states: [
        State {
            name: "empty"
            StateChangeScript {
                script: {
                    cellImg.source="CellGray.png"
                }
            }
        },
        State {
            name: "X"
            StateChangeScript {
                script: {
                    cellImg.source="X.png"
                }
            }
        },
        State {
            name: "O"
            StateChangeScript {
                script: {
                    cellImg.source="O.png"
                }
            }
        }
    ]

    function onFocusIn () {

        cellGlow.visible = true
    }

    function onFocusOut() {

        cellGlow.visible = false
    }

    onClicked: {
        viewmodel.OnCellCliced(arrayX, arrayY);
    }
}

