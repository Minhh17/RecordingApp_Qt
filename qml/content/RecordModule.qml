import QtQuick 2.15
import QtQuick.Controls 2.15
import ProjectImport 1.0 // IMport component: Constants, Animation, ...
import QtCharts 2.6
import QtMultimedia 5.15
import "component"

Rectangle {
    width: Constants.width
    height: Constants.height - 140
    color: Constants.backgroundColor

    property string selectedBtn: "visualize"
    property bool recStatus: audioController.recStatus

    Rectangle {
        id: rectangle
        x: 13
        y: 10
        width: 180
        height: 440
        color: "#161525"
        radius: 20

        StatusLight {
            id: statusLight
        }

        Column {
            id: column
            x: 0
            y: 0
            width: 180
            height: 312
            spacing: 10
            topPadding: 20

            Rectangle {
                id: visualizeRec
                width: 180
                height: 60
                color: "#00ffffff"

                Text {
                    id: text1
                    color: selectedBtn === "visualize" ? Constants.focusColor : "#ffffff"
                    anchors.centerIn: parent
                    text: qsTr("Visualize")
                    font.pixelSize: 22
                    font.family: "Oxanium"
                }

                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    onClicked: {
                        selectedBtn = "visualize"
                        contentLoader.setSource("Recording.qml");
                    }
                }
            }

            Rectangle {
                id: configRec
                width: 180
                height: 60
                color: "#00ffffff"
                Text {
                    color: selectedBtn === "config" ? Constants.focusColor : "#ffffff"
                    text: qsTr("Config")
                    font.pixelSize: 22
                    font.family: "Oxanium"
                    anchors.centerIn: parent
                }

                MouseArea {
                    id: mouseArea1
                    anchors.fill: parent
                    onClicked: {
                        selectedBtn = "config"
                        contentLoader.setSource("ConfigAudio.qml");
                    }
                }
            }

            Rectangle {
                id: timerRec
                width: 180
                height: 60
                color: "#00ffffff"
                Text {
                    color:  selectedBtn === "timer" ? Constants.focusColor : "#ffffff"
                    text: qsTr("Timer")
                    font.pixelSize: 22
                    font.family: "Oxanium"
                    anchors.centerIn: parent
                }

                MouseArea {
                    id: mouseArea2
                    anchors.fill: parent
                    onClicked: {
                        selectedBtn = "timer"
                        contentLoader.setSource("AudioChart.qml");
                    }
                }
            }

            Rectangle {
                id: fileManagerRec
                width: 180
                height: 60
                color: "#00ffffff"
                Text {
                    color:  selectedBtn === "fileManager" ? Constants.focusColor : "#ffffff"
                    text: qsTr("FileManager")
                    font.pixelSize: 22
                    font.family: "Oxanium"
                    anchors.centerIn: parent
                }

                MouseArea {
                    id: mouseArea3
                    anchors.fill: parent
                    onClicked: {
                        selectedBtn = "fileManager"
                        contentLoader.setSource("ConfigAudio.qml");
                    }
                }
            }
        }
    }

    Rectangle {
        id: contentRec
        x: 207
        y: 12
        width: 800
        height: 440
        color: "#2a2a2a"
        radius: 20

        Loader {
            id: contentLoader
            anchors.fill: parent
            source: "Recording.qml"
        }
    }
}
