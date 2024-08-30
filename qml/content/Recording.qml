import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    width: 800
    height: 440

    Button {
        id: startBtn
        x: 26
        y: 393
        text: qsTr("Start")
        onClicked: {
            audioController.startRecord()
        }
    }

    Rectangle {
        id: content
        x: 26
        y: 8
        width: 750
        height: 380
        color: "#d3d7cf"

        AudioChart {
            id: minhtest
            width: 750
            height: 380
            anchors.centerIn: parent
        }
    }

    Button {
        id: stopBtn
        x: 141
        y: 393
        text: qsTr("Stop")
        onClicked:
            audioController.stopRecord()
    }
}
