import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    width: 800
    height: 440

    Component.onCompleted: {

    }

    Button {
        id: startBtn
        x: 26
        y: 377
        text: qsTr("Start")
        onClicked: audioController.startRecord()
    }

    Rectangle {
        id: content
        x: 26
        y: 27
        width: 754
        height: 327
        color: "#d3d7cf"
    }

    Button {
        id: stopBtn
        x: 143
        y: 377
        text: qsTr("Stop")
        onClicked: audioController.stopRecord()
    }
}
