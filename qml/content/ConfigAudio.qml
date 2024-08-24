import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    width: 800
    height: 440

    Component.onCompleted: {
        console.log("hell0"+audioConfig.listEndianz);
        for (var i = 0; i < audioConfig.listSampleRate.length; i++){
            sampleRateMl.append({"name" : audioConfig.listSampleRate[i]});
        }
        for (i = 0; i < audioConfig.listChannel.length; i++){
            channelMl.append({"name" : audioConfig.listChannel[i]});
        }
        for (i = 0; i < audioConfig.listEndianz.length; i++){
            endianzMl.append({"name" : ""+audioConfig.listEndianz[i]});
        }
    }

    ComboBox {
        id: deviceCb
        x: 57
        y: 35
        width: 686
        height: 40
        font.pointSize: 18
        font.family: "Oxanium"
        // currentIndex: 0
        enabled: !audioController.recStatus

        model: audioConfig.listDevices

        onCurrentIndexChanged: {
            console.log("Selected choose_device Item:", deviceCb.currentText)
            audioConfig.changeDevice(deviceCb.currentIndex)
            audioConfig.selectedParams.device = currentText
            console.log("Selected choose_device Item:", audioConfig.selectedParams);
            // Add logic here
        }
    }

    Text {
        id: text1
        x: 374
        y: 8
        width: 53
        height: 26
        text: qsTr("device")
        font.pixelSize: 12
    }

    ComboBox {
        id: codecCb
        x: 44
        y: 124
        width: 157
        height: 40
        currentIndex: 0
        model: audioConfig.listCodecs
        font.pointSize: 18
        font.family: "Oxanium"
        enabled: !audioController.recStatus

        onCountChanged: {

        }
    }

    Text {
        id: codecTx
        x: 44
        y: 98
        width: 53
        height: 26
        text: qsTr("codec")
        font.pixelSize: 12
    }

    Text {
        id: text3
        x: 298
        y: 98
        width: 53
        height: 26
        text: qsTr("samplerate")
        font.pixelSize: 12
    }

    ComboBox {
        id: sampleRateCb
        x: 298
        y: 124
        width: 178
        height: 40
        currentIndex: 0
        enabled: !audioController.recStatus

        model: ListModel {
            id: sampleRateMl
        }

        font.pointSize: 18
        font.family: "Oxanium"
    }

    Button {
        id: button
        x: 343
        y: 363
        text: qsTr("Save")
        enabled: !audioController.recStatus

        onClicked: {
            //Load to Record Device
            audioConfig.saveConfig(codecCb.currentIndex, sampleRateCb.currentIndex, channelsCb.currentIndex, endianzCb.currentIndex)
            console.log("from qml: " + audioConfig.listDevices[0])
            // console.log("click: " +devicename)
        }
    }

    ComboBox {
        id: channelsCb
        x: 590
        y: 124
        font.family: "Oxanium"
        currentIndex: 0
        font.pointSize: 18
        enabled: !audioController.recStatus

        model: ListModel {
            id: channelMl
        }
    }

    Text {
        id: channelTx
        x: 590
        y: 98
        width: 53
        height: 26
        text: qsTr("channels")
        font.pixelSize: 12
    }

    ComboBox {
        id: endianzCb
        x: 309
        y: 233
        width: 157
        height: 40
        font.pointSize: 18
        currentIndex: 0
        font.family: "Oxanium"
        enabled: !audioController.recStatus

        model: ListModel {
            id: endianzMl
        }
    }

    Text {
        id: text5
        x: 309
        y: 207
        width: 53
        height: 26
        text: qsTr("endianz")
        font.pixelSize: 12
    }
}
