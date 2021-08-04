import QtQuick 2.12
import QtQuick.Window 2.12

import "Theme.js" as Theme

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Rectangle{
        anchors.centerIn: parent
        width: parent.width/2
        height: parent.height/2
        color: Theme.background
        Text{
            anchors.centerIn: parent
            text: "Theme colour text"
            color: Theme.textColour
        }
    }
}
