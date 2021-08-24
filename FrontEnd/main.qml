import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import "Theme.js" as Theme
import MyApp.Images 1.0

Window {
    visible: true
    width: Theme.defaultWidth
    height: Theme.defaultWidth
    title: qsTr("Hello World")

    Connections {
        target: frontEndObject
        // Traditional QML voodoo where "on" + capitalised signal connections to this slot
        onDisplayErrorPopup: {
            errorText.text = errorMsg
            errorPopup.open()
        }
    }

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

        LiveImage {
            id: rgbSortedImage
            anchors.margins: Theme.imageMargins
            anchors.fill: parent
            image: LiveImageProvider.image
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

    Popup {
        id: errorPopup
        width: Theme.popupWidth
        height: Theme.popupHeight
        anchors.centerIn: parent
        modal: true
        focus: true
        background: Rectangle {
            anchors.fill: parent
            color: Theme.popupBackground
            border.color: "black"
            border.width: Theme.borderWidth
        }

        Text {
            id: errorText
            anchors.centerIn: parent
            text: ""
        }
        Button {
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: Theme.buttonWidth
            height: Theme.buttonHeight
            background: Rectangle {
                radius: Theme.radius
                color: parent.down ? Theme.buttonPressed : parent.hovered ? Theme.buttonHovered : "transparent"
                border.color: "black"
                border.width: Theme.borderWidth
            }
            text: "Ok"
            onClicked: {
                errorPopup.close()
            }
        }
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
    }
}
