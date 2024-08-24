import QtQuick 2.15

Item {
    Rectangle {
        border.color: "black"
        border.width: 2
        radius: 10
        width: 20
        height: 20
        color: recStatus ? "red" : "green"

        // Flicker effect when recording
        SequentialAnimation on color {
            loops: Animation.Infinite
            running: recStatus
            ColorAnimation { duration: 300; from: "red" }
            ColorAnimation { duration: 300; to: "darkred" }
        }
    }
}
