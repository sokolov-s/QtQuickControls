import QtQuick 2.3
import QtQuick.Controls 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Label {
        id: click_cntr
        text: "0"
        anchors.centerIn: parent
    }

    Button {
        text: qsTr("Inc")
        anchors.top: click_cntr.bottom
        anchors.topMargin: 5
        anchors.horizontalCenter: click_cntr.horizontalCenter
        onClicked: onBtnCounterCliced()
    }

    function onBtnCounterCliced() {
        click_cntr.text = parseInt(click_cntr.text) + 1;
    }
}

