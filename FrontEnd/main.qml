import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import "Theme.js" as Theme
import QMLLiveImage.Images 1.0

Window {
    id: mainWindow
    visible: true
    width: Theme.defaultWidth
    height: Theme.defaultWidth
    title: qsTr("Hello World")
    property var selectedSort: ""

    Connections {
        target: frontEndObject
        // Traditional QML voodoo where "on" + capitalised signal connections to this slot
        onDisplayErrorPopup: {
            errorText.text = errorMsg
            errorPopup.open()
        }
        onDisplaySortingTime: {
            sortingDurationText.text = sortingText
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
            text: "No source image selected.\nDrag and drop a new image in."
        }
        LiveImage {
            id: rgbLoadedImage
            anchors.margins: Theme.imageMargins
            anchors.fill: parent
            image: LoadedImageProvider.image
        }

        DropArea {
            id: loadImageDropAread
            anchors.fill: parent
            onDropped: {
                frontEndObject.loadImage(drop.text)
            }
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
            image: SortedImageProvider.image
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
            id: processImageButton
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
            Text {
                anchors.centerIn: parent
                wrapMode: Text.Wrap
                text: "Process Image"
            }

            onClicked: {
                submitProcessImage()
            }
        }

        // Sort selection radio buttons
        CustomRadioButton {
            id: bubbleSortButton
            anchors.left: processImageButton.left
            anchors.top: processImageButton.bottom
            anchors.topMargin: Theme.buttonMargins
            text: "Bubble sort"
            onClicked: {
                if (isChecked) {
                    radioButtonEnabling("bubble")
                    mainWindow.selectedSort = "bubble"
                }
            }
        }
        CustomRadioButton {
            id: selectionSortButton
            anchors.left: processImageButton.left
            anchors.top: bubbleSortButton.bottom
            anchors.topMargin: Theme.buttonMargins
            text: "Selection sort"
            onClicked: {
                if (isChecked) {
                    radioButtonEnabling("selection")
                    mainWindow.selectedSort = "selection"
                }
            }
        }

        Text {
            id: sortingDurationText
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.margins: Theme.imageMargins
            text: "Sorting time: 0ms"
            wrapMode: Text.Wrap
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
                errorPopup.close()
            }
        }
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
    }

    function radioButtonEnabling(sortType) {
        // As we have multiple sorts, only one can be active at a time
        // This function ensures that each time a button is clicked
        if (sortType !== "bubble") {
            bubbleSortButton.isChecked = false
        }
        if (sortType !== "selection") {
            selectionSortButton.isChecked = false
        }
    }
    function submitProcessImage() {
        // There are some arugment checks to perform and pass to the frontend.cpp slot
        // This function runs through that and forms the correct argument set

        // Check the user has selected a sort
        if (selectedSort === "") {
            errorText.text = "No sort selected, please select one."
            errorPopup.open()
            return
        }

        frontEndObject.processImage(selectedSort)
    }
}
