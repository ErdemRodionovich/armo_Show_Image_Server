import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Badluev Erdem for ARMO")

    function setServID(id_of_server){
        servID.text = id_of_server;
    }

    Text{
        id: captionOfServID
        text: qsTr("Server ID (copy it and put into client):")
        anchors.top: parent.top
    }

    TextEdit {
        id: servID
        text: qsTr("server identifier")
        readOnly: true
        wrapMode: TextInput.WrapAnywhere
        selectByMouse: true
        selectByKeyboard: true
        anchors.top: captionOfServID.bottom
    }

}
