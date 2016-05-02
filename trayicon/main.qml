import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2
import Model 1.0

ApplicationWindow {
    visible: false
    width: 640
    height: 480
    title: qsTr("Main")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Model {
        id: myModel
    }

    MainForm {
        anchors.fill: parent
        button.onClicked: myModel.refresh()
    }

    Timer {
        triggeredOnStart: true
        running: true
        repeat: true
        interval: 3600000 // every hour in ms
        onTriggered: myModel.refresh()
    }
}
