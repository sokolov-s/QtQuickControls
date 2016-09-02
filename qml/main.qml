import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import com.TicTacToe.ViewModel 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    color: "#f2f1f0"
    title: qsTr("Tic-Tack-Toe")

    Connections {
        target: viewmodel
        onGenerateFieldInQml : {
            if(size == 3) {
                clearField();
                generateField3x3();
            }
        }
        onPlayerCanged : {
            curActionText.y = field.y - curActionText.height - 50;
            curActionText.text = player + " " + qsTr("turn");
            curActionText.visible = true;
        }
        onPlayerWin : {
            gameEndDialog.text = player + " " + qsTr("win");
            gameEndDialog.open();
        }
        onStandoff : {
            gameEndDialog.text = qsTr("Standoff");
            gameEndDialog.open();
        }
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("&Game")
            MenuItem {
                text: qsTr("&New Game");
                onTriggered: opponentDialog.open();
            }
            MenuItem {
                text: qsTr("&Exit");
                onTriggered: Qt.quit();
            }
        }
    }

    Rectangle {
        id: curActionText
        width: 100
        height: 50
        color: mainWindow.color
        visible: false
        property string text: ""
        x: (mainWindow.width - width) / 2
        Text {
            id: textAction
            text: qsTr(parent.text)
            anchors.centerIn: parent
        }
    }

    Dialog {
        id : gameEndDialog
        width: mainWindow.width / 2
        height: mainWindow.height / 2
        visible: false
        title : qsTr("Game end")
        property string text: ""
        standardButtons: StandardButton.Ok | StandardButton.Cancel
        contentItem: Rectangle {
            id: dialogRectangle
            anchors.fill: parent
            color: mainWindow.color
            Text {
                id : dialogText
                anchors.centerIn: parent
                text : gameEndDialog.text
            }
            Button {
                id: buttonOk
                anchors.horizontalCenter: dialogRectangle.horizontalCenter
                anchors.top: dialogText.bottom
                anchors.topMargin: 40
                text: qsTr("Ok")
                onClicked: gameEndDialog.close()
            }
        }
    }

    Dialog {
        id: opponentDialog
        visible: false
        title: qsTr("Choose an opponent")
        contentItem: Rectangle {
            Button {
                id: buttonHuman
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: (parent.height - height * 4 - 20) / 2
                text: qsTr("Human")
                onClicked: {
                    opponentDialog.close();
                    viewmodel.NewGame(0, 3);
                }
            }
            Button {
                id: buttonAi1
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: buttonHuman.bottom
                anchors.topMargin: 10
                text: qsTr("AI level 1")
                onClicked: {
                    opponentDialog.close();
                    viewmodel.NewGame(1, 3);
                }
            }
            Button {
                id: buttonAi2
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: buttonAi1.bottom
                anchors.topMargin: 10
                text: qsTr("AI level 2")
                onClicked: {
                    opponentDialog.close();
                    viewmodel.NewGame(2, 3);
                }
            }
            Button {
                id: buttonAi3
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: buttonAi2.bottom
                anchors.topMargin: 10
                text: qsTr("AI level 3")
                onClicked: {
                    opponentDialog.close();
                    viewmodel.NewGame(3, 3);
                }
            }
        }
    }

    Rectangle {
        id: field
        visible: false
        color: mainWindow.color
    }

    function generateField3x3() {
        var cellComponent = Qt.createComponent("Cell.qml");
        var objWidth = 0;
        var objHeight = 0;
        for(var i = 0; i < 3; ++i) {
            for(var j = 0; j < 3; ++j) {
                var obj = cellComponent.createObject(field);
                obj.x = obj.width * j;
                obj.y = obj.height * i;
                obj.arrayX = j;
                obj.arrayY = i;
                objWidth = obj.width;
                objHeight = obj.height;
            }
        }
        field.x = (mainWindow.width - objWidth * 3) / 2;
        field.y = (mainWindow.height - objHeight * 3) / 2;
        field.width = objWidth * 3;
        field.height = objHeight * 3;
        field.visible = true
    }

    function clearField() {
        field.visible = false;
        var tmp = field.children
        for(var i = 0; i < tmp.length; ++i) {
            tmp[i].destroy();
        }
    }
}

