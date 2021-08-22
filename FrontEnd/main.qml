import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import "Theme.js" as Theme

Window {
    visible: true
    width: Theme.defaultWidth
    height: Theme.defaultWidth
    title: qsTr("Hello World")
    // Image viewer 1
    Rectangle {
        id: imageBox1
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: menuBox.left
        height: parent.height / 2
        color: "transparent"
        border.color: "black"
        border.width: Theme.borderWidth
        Text {
            anchors.centerIn: parent
            text: "No source image selected"
        }
        Image {
            id: rgbSourceImage
            anchors.margins: Theme.imageMargins
            anchors.fill: parent
            source: "example-image.jpg"
        }
    }

    // Image viewer 2
    Rectangle {
        id: imageBox2
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: menuBox.left
        height: parent.height / 2
        color: "transparent"
        border.color: "black"
        border.width: Theme.borderWidth
        Text {
            anchors.centerIn: parent
            text: "Image not processed yet."
        }

        Image {
            id: rgbSortedImage
            anchors.margins: Theme.imageMargins
            anchors.fill: parent
        }
    }

    // Menu bar right hand side
    Rectangle {
        id: menuBox
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: Theme.menuWidth
        color: "transparent"
        border.color: "black"
        border.width: Theme.borderWidth

        Button {
            anchors.top: parent.top
            anchors.topMargin: Theme.buttonHeight
            anchors.horizontalCenter: parent.horizontalCenter
            width: Theme.buttonWidth
            height: Theme.buttonHeight
            hoverEnabled: true
            background: Rectangle {
                radius: Theme.radius
                color: parent.down ? Theme.buttonPressed : parent.hovered ? Theme.buttonHovered : "transparent"
                border.color: "black"
                border.width: Theme.borderWidth
            }
            text: "Process Image"
            onClicked: {
                frontEndObject.processImage()
            }
        }
    }

    //    Rectangle {
    //        anchors.centerIn: parent
    //        width: parent.width / 2
    //        height: parent.height / 2
    //        color: Theme.background
    //        Text {
    //            anchors.centerIn: parent
    //            text: "Theme colour text"
    //            color: Theme.textColour
    //        }
    //    }
}
