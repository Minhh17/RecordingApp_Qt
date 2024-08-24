import QtQuick 2.15

Rectangle {
    width: 1024
    height: 50
    color: "#000000"
    anchors.top: parent.top

    Text {
        id: text1
        color: "#ffffff"
        text: qsTr("D-ESCA3")
        anchors.fill: parent
        font.pixelSize: 36
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: "Oxanium"
    }
}
