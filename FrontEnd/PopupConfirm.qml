import QtQuick 2.12
import QtQuick.Controls 2.12

import "Theme.js" as Theme

Popup {
    id: root

    property alias text: confirmText.text

    // Used to connect to a confirming/negating action
    signal accepted
    signal cancelled

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
        radius: Theme.radius
    }

    Text {
        id: titleText
        anchors.top: parent.top
        anchors.left: parent.left
        text: "Confirm"
        font.bold: true
        font.pixelSize: 25
        color: Theme.popupConfirmText
    }

    Text {
        id: confirmText
        anchors.centerIn: parent
        width: parent.width
        text: ""
        wrapMode: Text.Wrap
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
            root.accepted()
            root.close()
        }
    }

    Button {
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        width: Theme.buttonWidth
        height: Theme.buttonHeight
        background: Rectangle {
            radius: Theme.radius
            color: parent.down ? Theme.buttonPressed : parent.hovered ? Theme.buttonHovered : "transparent"
            border.color: "black"
            border.width: Theme.borderWidth
        }
        text: "Cancel"
        onClicked: {
            root.cancelled()
            root.close()
        }
    }
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
}
