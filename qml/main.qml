import QtQuick 2.3
import QtQuick.Controls 1.2
//import com.TicTacToe.ViewModel 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Tic-Tack-Toe")
    Connections {
        target: viewmodel
        onGenerateFieldInQml : {
            if(size == 3) {
                generateField3();
            }
        }
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("Game")
            MenuItem {
                text: qsTr("&New Game")
                onTriggered: viewmodel.NewGame(3);
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    function generateField3() {
        var cellComponent = Qt.createComponent("Cell.qml");
        var y = mainWindow.height / 2;
        var x = mainWindow.width / 2;
        for(var i = 0; i < 3; i++) {
            for(var j = 0; j < 3; j++) {
                var obj = cellComponent.createObject(mainWindow);
                obj.x = x - (obj.width * 3) / 2 + obj.width * j;
                obj.y = y - (obj.height * 3) / 2 + obj.height * i;
            }
        }
    }

}

