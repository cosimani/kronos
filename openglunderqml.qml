import QtQuick 2.0
import OpenGLUnderQML 1.0

Item {
    id : item

    width: 320
    height: 480

    Timer  {
        id: timer1
        interval: 4000; running: true; repeat: false
        onTriggered:  {
            recuadro.visible = true
            timer2.start()
        }
    }

    Timer  {
        id: timer2
        interval: 4000; running: false; repeat: false
        onTriggered: label.visible = true
    }

    Image {
        id : imagen
        source: "resources/images/isologo3.png"
        anchors.fill: item

        Squircle {
            SequentialAnimation on t {
                NumberAnimation { to: 1; duration: 2500; easing.type: Easing.InQuad }
                NumberAnimation { to: 0; duration: 2500; easing.type: Easing.OutQuad }
                loops: Animation.Infinite
                running: true
            }
        }

        Rectangle {
            id: recuadro
            color: Qt.rgba(0.663, 0.008, 0.188, 0.75)  // 0.663, 0.008, 0.188
            radius: 10
            border.width: 1
            border.color: "white"
            anchors.fill: label
            anchors.margins: -10
            visible: false
        }

        Text {
            id: label
            color: "white"
            wrapMode: Text.WordWrap
            text: "La aplicación se está configurando y se cerrará en unos segundos. Por favor, inicie la aplicación nuevamente para comenzar."
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.margins: 20
            visible: false
        }
    }
}
