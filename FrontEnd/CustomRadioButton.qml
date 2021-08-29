import QtQuick 2.12
import QtQuick.Controls 2.12

import "Theme.js" as Theme

Item {
    id: root
    property var isChecked: false
    property alias text: customText.text
    signal clicked

    width: parent.width
    height: Theme.radioButtonHeight

    Button {
        id: radioButton
        width: Theme.radioButtonHeight
        height: Theme.radioButtonHeight
        hoverEnabled: true
        background: Rectangle {
            border.color: "black"
            border.width: 2
            radius: width / 2
            color: parent.pressed ? Theme.buttonPressed : parent.hovered ? Theme.buttonHovered : root.isChecked ? Theme.radioButtonChecked : "transparent"
        }

        onClicked: {
            root.isChecked = !root.isChecked
            root.clicked()
        }
    }
    Text {
        id: customText
        text: ""
        anchors.left: radioButton.right
        anchors.verticalCenter: radioButton.verticalCenter
        anchors.leftMargin: Theme.buttonMargins
    }
}
