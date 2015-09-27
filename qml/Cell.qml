import QtQuick 2.3
import QtQuick.Controls 1.2

Item {
    id: cellItem
    width: 25
    height: 25
    antialiasing: true

    Rectangle {
        id: cell
        anchors.fill: parent

    }
    state: "empty"
    states: [
        State {
            name: "empty"
        },
        State {
            name: "X"
        },
        State {
            name: "O"
        }
    ]
}

