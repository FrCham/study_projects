import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import blurEngine 1.0

Window {
    id: root
    title: qsTr("Blur filter by FrCham")
    width: 640
    height: 480
    visible: true

    QmlConnector { id: engine }

    Rectangle{
        id: deskImg
        width: root.width
        height: root.height * 8 / 9
        transformOrigin: Item.TopLeft
    }

    Image {
        id: srcImg
        width: deskImg.width * 9 / 20
        height: deskImg.height
        anchors.left: deskImg.left
        anchors.top: deskImg.top
        fillMode: Image.PreserveAspectFit
        source: "/plug_mephi.jpg"
    }

    Image {
        id: blurImg
        width: deskImg.width * 9 / 20
        height: deskImg.height
        anchors.right: deskImg.right
        anchors.top: deskImg.top
        fillMode: Image.PreserveAspectFit
        source: "/plug_mephi.jpg"
        Connections {
            target: engine
            onImgBytesChanged: {
                blurImg.source = imgBytes
            }
        }
    }

    Rectangle {
        id: openImg
        width: deskImg.width / 10
        height: deskImg.height / 4
        anchors.left: srcImg.right
        anchors.top: srcImg.top
        color: "#F3E2A9"
        border.color: "#BDBDBD"
        TapHandler{
            onTapped: openImgDialog.open()
        }
        Text {
            text: qsTr("Open")
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 12
        }
    }

    Rectangle {
        id: start
        width: deskImg.width / 10
        height: deskImg.height / 4
        anchors.left: srcImg.right
        anchors.top: openImg.bottom
        color: "#81F7BE"
        border.color: "#BDBDBD"
        TapHandler{
            onTapped: engine.start(srcImg.source, blurRad.text, threadCnt.text)
        }
        Text {
            text: qsTr("Start")
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 12
        }
    }

    Rectangle {
        id: stop
        width: deskImg.width / 10
        height: deskImg.height / 4
        anchors.left: srcImg.right
        anchors.top: start.bottom
        color: "#F5A9BC"
        border.color: "#BDBDBD"
        TapHandler{
            onTapped: engine.stopQML()
        }
        Text {
            text: qsTr("Stop")
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 12
        }
    }

    Rectangle {
        id: save
        width: deskImg.width / 10
        height: deskImg.height / 4
        anchors.left: srcImg.right
        anchors.top: stop.bottom
        color: "#A9BCF5"
        border.color: "#BDBDBD"
        TapHandler{
            onTapped: saveDialog.open()
        }
        Text {
            text: qsTr("Save")
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 12
        }
    }

    Rectangle{
        id: infoBar
        width: root.width
        height: root.height / 9
        color: "red"
        anchors.top: deskImg.bottom
    }

    Rectangle{
        id: radiusInfoTxt
        width: infoBar.width * 5 / 32
        height: infoBar.height
        border.color: "#BDBDBD"
        anchors.top: infoBar.top
        anchors.left: infoBar.left
        Text {
            text: qsTr("Radius:")
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 12
        }
    }

    Rectangle{
        id: radiusInfoIn
        width: infoBar.width * 3 / 32
        height: infoBar.height
        border.color: "#BDBDBD"
        anchors.top: infoBar.top
        anchors.left: radiusInfoTxt.right
        TextField{
            id: blurRad
            text: qsTr("0")
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: TextEdit.AlignHCenter
            font.pointSize: 12
            validator: IntValidator {bottom: 0; top: 9999}
        }
    }

    Rectangle{
        id: threadInfoTxt
        width: infoBar.width * 5 / 32
        height: infoBar.height
        border.color: "#BDBDBD"
        anchors.top: infoBar.top
        anchors.left: radiusInfoIn.right
        Text {
            text: qsTr("Threads:")
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 12
        }
    }

    Rectangle{
        id: threadInfoIn
        width: infoBar.width * 3 / 32
        height: infoBar.height
        border.color: "#BDBDBD"
        anchors.top: infoBar.top
        anchors.left: threadInfoTxt.right
        TextField{
            id: threadCnt
            text: qsTr("1")
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: TextEdit.AlignHCenter
            font.pointSize: 12
            validator: IntValidator {bottom: 1; top: 9999}
        }
    }


    Rectangle{
        id: processInfoTxt
        width: infoBar.width * 5 / 32
        height: infoBar.height
        border.color: "#BDBDBD"
        anchors.top: infoBar.top
        anchors.left: threadInfoIn.right
        Text {
            text: qsTr("Process:")
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 12
        }
    }

    Rectangle{
        id: processInfoOut
        width: infoBar.width * 3 / 32
        height: infoBar.height
        border.color: "#BDBDBD"
        anchors.top: infoBar.top
        anchors.left: processInfoTxt.right
        Text{
            id: progress
            text: qsTr("0")
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 12
        }
        Connections{
            target: engine
            onProgressChanged: {
                progress.text = engine.progress + "%"
                time.text = engine.time/1000 + " s."
            }
        }
    }

    Rectangle{
        id: timeInfoTxt
        width: infoBar.width / 8
        height: infoBar.height
        border.color: "#BDBDBD"
        anchors.top: infoBar.top
        anchors.left: processInfoOut.right
        Text {
            text: qsTr("Time(s):")
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 12
        }
    }

    Rectangle{
        id: timeInfoOut
        width: infoBar.width / 8
        height: infoBar.height
        border.color: "#BDBDBD"
        anchors.top: infoBar.top
        anchors.left: timeInfoTxt.right
        Text{
            id: time
            text: qsTr("0")
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 12
        }
    }

    FileDialog{
        id: openImgDialog
        title: "Choose an image"
        folder: shortcuts.home
        selectMultiple: false
        nameFilters: ["Image files (*.jpg *.png *.bmp)"]

        onAccepted: {
            srcImg.source = openImgDialog.fileUrl
            srcImg.update()
            openImgDialog.close()
        }

        onRejected: openImgDialog.close()
    }

    FileDialog{
        id: saveDialog
        title: "Save blur Image"
        folder: shortcuts.home
        selectMultiple: false
        selectExisting: false
        nameFilters: ["Image files (*.jpg *.png *.bmp)"]
        onAccepted: {
            var url = (fileUrl+"").replace('file:///', '');
            blurImg.grabToImage(function(result) {
                result.saveToFile(url);
            });
        }
    }

}
