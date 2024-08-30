import QtQuick 2.15
import QtQuick.Controls 2.15
import AudioChartImport2 1.0

Rectangle {
    width: 800
    height: 440

    property var audioData: []

    Canvas {
        id: audioWaveform
        anchors.fill: parent

        property int maxAmplitude: 32767 // Assuming 16-bit PCM

        onPaint: {
            console.log("start paint");
            // console.log("qml data:", AudioChart2.displayData[0]);

            var ctx = getContext("2d");
            ctx.clearRect(0, 0, width, height);

            // Draw grid
            ctx.strokeStyle = "#444";
            ctx.lineWidth = 1;
            for (var i = 0; i < width; i += width / 10) {
                ctx.beginPath();
                ctx.moveTo(i, 0);
                ctx.lineTo(i, height);
                ctx.stroke();
            }
            for (var j = 0; j < height; j += height / 10) {
                ctx.beginPath();
                ctx.moveTo(0, j);
                ctx.lineTo(width, j);
                ctx.stroke();
            }

            // Draw waveform
            ctx.strokeStyle = "#00ff00";
            ctx.lineWidth = 2;
            ctx.beginPath();
            for (var k = 0; k < audioData.length; k++) {
                var x = k * width / audioData.length;
                var y = height / 2 - (audioData[k] / maxAmplitude) * height / 2;
                if (k === 0) {
                    ctx.moveTo(x, y);
                } else {
                    ctx.lineTo(x, y);
                }
            }
            ctx.stroke();
        }
    }

    Connections {
        target: AudioChart2
        function onDisplayDataChanged() {
            audioData = AudioChart2.displayData;
            audioWaveform.requestPaint();
            console.log("qml data:", AudioChart2.displayData[0]);
        }
    }
}
