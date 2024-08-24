import QtQuick 2.15
import QtQuick.Controls 2.15
import ProjectImport 1.0

Rectangle {
    width: Constants.width
    height: 90
    anchors.bottom: parent.bottom
    color: Constants.darkColor

    property int selectedIndex: -1

    ListModel {
        id: buttonModel
        ListElement { name: "Record"; screenPath: "../RecordModule.qml" }
        ListElement { name: "Process"; screenPath: "../Processing.qml" }
        ListElement { name: "Training"; screenPath: "../RecordModule.qml" }
        ListElement { name: "Profile"; screenPath: "../RecordModule.qml" }
        ListElement { name: "Help"; screenPath: "../RecordModule.qml" }
        ListElement { name: "Help"; screenPath: "../RecordModule.qml" }
        ListElement { name: "Help"; screenPath: "../RecordModule.qml" }
    }

    Row {
        width: parent.width
        height: 90
        anchors.centerIn: parent
        spacing: 8

        Repeater {
            model: buttonModel
            delegate: ButtonWithEffect {}
        }
    }
}
