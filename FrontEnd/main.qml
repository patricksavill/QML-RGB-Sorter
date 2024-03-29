import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import "Theme.js" as Theme
import QMLLiveImage.Images 1.0
import ImageSort 1.0

Window {
    id: mainWindow
    visible: true
    width: Theme.defaultWidth
    height: Theme.defaultWidth
    title: qsTr("QML RGB Image Sorter")
    property var selectedSort: ImageSortEnum.NONE
    property var selectedMetric: ImageSortEnum.RGB_INTENSITY

    Connections {
        target: frontEndObject
        // Traditional QML voodoo where "on" + capitalised signal connections to this slot
        onDisplayErrorPopup: {
            errorPopup.text = errorMsg
            errorPopup.open()
        }
        onDisplaySortingTime: {
            sortingDurationText.text = sortingText
        }
    }

    Rectangle {
        id: dynamicVerticalBox
        width: Theme.paneSliderWidth
        height: Theme.paneSliderHeight
        y: mainWindow.height / 2
        x: (parent.width - menuBox.width) / 2
        color: "transparent"
        border.color: "transparent"
        Image {
            id: img
            anchors.centerIn: parent
            source: "qrc:/icons/arrow-resize.svg"
            width: 30
            height: 30
            fillMode: Image.PreserveAspectFit
        }

        MouseArea {
            anchors.fill: parent
            drag {
                target: dynamicVerticalBox
                axis: Drag.YAxis
                minimumY: 0
                maximumY: mainWindow.height
            }
            onDoubleClicked: {
                parent.y = mainWindow.height / 2
            }
        }
    }

    // Image viewer 1
    Rectangle {
        id: imageBox1
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: menuBox.left
        anchors.bottom: dynamicVerticalBox.top
        anchors.bottomMargin: -dynamicVerticalBox.height / 2
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
        anchors.top: dynamicVerticalBox.bottom
        anchors.topMargin: -dynamicVerticalBox.height / 2
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
                    mainWindow.selectedSort = ImageSortEnum.BUBBLE_SORT
                    radioButtonEnabling()
                } else {
                    mainWindow.selectedSort = ImageSortEnum.NONE
                }
            }
        }
        CustomRadioButton {
            id: insertionSortButton
            anchors.left: processImageButton.left
            anchors.top: bubbleSortButton.bottom
            anchors.topMargin: Theme.buttonMargins
            text: "Insertion sort"
            onClicked: {
                if (isChecked) {
                    mainWindow.selectedSort = ImageSortEnum.INSERTION_SORT
                    radioButtonEnabling()
                } else {
                    mainWindow.selectedSort = ImageSortEnum.NONE
                }
            }
        }
        CustomRadioButton {
            id: selectionSortButton
            anchors.left: processImageButton.left
            anchors.top: insertionSortButton.bottom
            anchors.topMargin: Theme.buttonMargins
            text: "Selection sort"
            onClicked: {
                if (isChecked) {
                    mainWindow.selectedSort = ImageSortEnum.SELECTION_SORT
                    radioButtonEnabling()
                } else {
                    mainWindow.selectedSort = ImageSortEnum.NONE
                }
            }
        }

        Rectangle {
            id: horizontalDivider
            width: Theme.menuWidth - Theme.buttonMargins * 2
            height: Theme.dividerHeight
            color: "black"
            anchors.top: selectionSortButton.bottom
            anchors.topMargin: Theme.buttonMargins
            anchors.left: menuBox.left
            anchors.leftMargin: Theme.buttonMargins
        }

        CustomRadioButton {
            id: dualAxisSort
            anchors.left: processImageButton.left
            anchors.top: horizontalDivider.bottom
            anchors.topMargin: Theme.buttonMargins
            text: "Sort x and y"
        }

        // combo box for metric selection
        ComboBox {
            id: metricComboBox
            anchors.top: dualAxisSort.bottom
            anchors.topMargin: Theme.buttonMargins
            width: Theme.buttonWidth
            height: Theme.buttonHeight
            anchors.left: dualAxisSort.left
            hoverEnabled: true

            currentIndex: 0
            background: Rectangle {
                anchors.fill: parent
                color: metricComboBox.down ? Theme.buttonPressed : metricComboBox.hovered ? Theme.buttonHovered : "transparent"
                border.color: "black"
                border.width: Theme.borderWidth
                radius: Theme.radius
            }

            // This contains the elements of the combo box
            model: ListModel {
                id: pixelMetricModel
                ListElement {
                    metric_text: "RGB Intensity"
                    //                    metric_enum: ImageSortEnum.RGB_INTENSITY
                }
                ListElement {
                    metric_text: "HSV Hue"
                    //                    metric_enum: ImageSortEnum.HUE
                }
            }

            // This controls how elements are shown
            delegate: ItemDelegate {
                width: parent.width
                contentItem: Text {
                    text: metric_text
                }
            }

            onCurrentIndexChanged: {
                if (currentIndex == 0) {
                    selectedMetric = ImageSortEnum.RGB_INTENSITY
                } else if (currentIndex == 1) {
                    selectedMetric = ImageSortEnum.HUE
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

    PopupError {
        id: errorPopup
    }
    PopupConfirm {
        id: confirmBubbleSortPopup
        onAccepted: {
            frontEndObject.processImage(selectedSort, selectedMetric,
                                        dualAxisSort.isChecked)
        }
    }

    function radioButtonEnabling() {
        // As we have multiple sorts, only one can be active at a time
        // This function ensures that each time a button is clicked
        if (selectedSort !== ImageSortEnum.BUBBLE_SORT) {
            bubbleSortButton.isChecked = false
        }
        if (selectedSort !== ImageSortEnum.INSERTION_SORT) {
            insertionSortButton.isChecked = false
        }
        if (selectedSort !== ImageSortEnum.SELECTION_SORT) {
            selectionSortButton.isChecked = false
        }
    }
    function submitProcessImage() {
        // There are some arugment checks to perform and pass to the frontend.cpp slot
        // This function runs through that and forms the correct argument set

        // Check the user has selected a sort
        if (selectedSort === ImageSortEnum.NONE) {
            errorPopup.text = "No sort selected, please select one."
            errorPopup.open()
            return
        }

        if (selectedSort == ImageSortEnum.BUBBLE_SORT) {
            confirmBubbleSortPopup.text
                    = "You have selected bubble sort, this is SLOW.\nDo you want to continue?"
            confirmBubbleSortPopup.open()
            return
        }

        frontEndObject.processImage(selectedSort, selectedMetric,
                                    dualAxisSort.isChecked)
    }
}
