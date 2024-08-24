// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 2.15
import QtQuick.Controls 2.15
import ProjectImport 1.0 // IMport component: Constants, Animation, ...
import QtQuick.VirtualKeyboard 2.15
import "component"

ApplicationWindow {
    width: Constants.width
    height: Constants.height
    color: Constants.backgroundColor
    visible: true


    Loader {
        id: screenLoader
        anchors.top: topbar.bottom
        anchors.bottom: mainmenu.top
        source: "./RecordModule.qml"
    }

    TopBar {
        id: topbar
    }

    // Bottom bar
    BottomMenu {
        id: mainmenu
    }

    InputPanel {
        id: inputPanel
        y: Constants.showKeyboard ? parent.height - height : parent.height
        Behavior on y {     // animation chuyển động trượt lênS
            NumberAnimation {
                duration: 200
                easing.type: Easing.InOutQuad
            }
        }
        anchors.leftMargin: Constants.width/10
        anchors.rightMargin: Constants.width/10
        anchors.left: parent.left
        anchors.right: parent.right

    }
}

