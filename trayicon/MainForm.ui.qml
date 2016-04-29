import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3

Item {
    width: 640
    height: 480

    property alias button: button1

    GridLayout {
        id: gridLayout1
        anchors.rightMargin: 5
        anchors.leftMargin: 5
        anchors.bottomMargin: 5
        anchors.topMargin: 5
        anchors.fill: parent
        columns: 2

        Label {
            id: label1
            text: qsTr("Here would be a simple form:")
        }

        TextField {
            id: textField2
            Layout.fillWidth: true
        }

        Button {
            id: button1
            text: qsTr("Refresh")
        }
    }
}
