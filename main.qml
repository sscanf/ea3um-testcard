import QtQuick 2.5
import QtMultimedia 5.5
import QtQuick.Window 2.2
import Qt.labs.folderlistmodel 2.1

Window {
    property int idx;
    property int timelapse;
    property int slideEnabled;
    property int videoEnabled;

    visible : true
    id      : mainPage
    width   : Screen.width;
    height  : Screen.height;
    color   : "black"
    idx     : 0
    timelapse   : 3000
    slideEnabled: 0
    videoEnabled: 1

    Component.onCompleted: {
        banner.enabled      = Settings.value ("banner/enabled",1);
        banner.text         = Settings.value ("banner/text","EA3UM carta ATV ** ");
        timelapse           = Settings.value ("slide/timelapse","3000")*1000;
        slideEnabled        = Settings.value ("slide/enabled","0");
        videoEnabled        = Settings.value ("video/enabled","1");

        console.log (timelapse);
        console.log (slideEnabled);
        if (camera.availability == 0 && videoEnabled == 1){
            camara.opacity=1
            flipable.opacity=0
        }
        cardImageFront.source = "file://mnt/imagen/carta.jpg"
    }

    Rectangle{
        color       : "black"
        anchors.fill: parent

        Flipable {
            property bool flipped: false

            id          :flipable
            anchors.fill: parent

            front: Image {id: cardImageFront; anchors.fill: parent}
            back:  Image {id: cardImageBack;  anchors.fill: parent}

            transform: Rotation {
                id: rotation
                origin.x: flipable.width/2
                origin.y: flipable.height/2
                axis.x: 0; axis.y: 1; axis.z: 0
                angle: 0
            }

            states: State {
                name: "back"
                PropertyChanges { target: rotation; angle: 180 }
                when: flipable.flipped
            }

            transitions: Transition {
                NumberAnimation { target: rotation; property: "angle"; duration: 1000 }
            }

        }

        Rectangle{
            id      : camara
            opacity : 0
            color   : "black"
//            border.color: "black"
            visible : true
            width   : 640
            height  : 480
            x       : (parent.width/2) - width/2
            y       : (parent.height/2) - height/2
            clip    : true

            Camera {
                id  : camera
            }

            VideoOutput {
                source      : camera
                anchors.fill: parent
                focus       : visible // to receive focus and capture key events when visible
            }
        }

        Timer {
            id      : timer
            interval: timelapse
            running : slideEnabled
            repeat  : true
            onTriggered: {

                console.log (model.get(idx,"fileName"))

                if (model.get(idx,"fileName") !== "undefined"){
                    if (!flipable.flipped){
                        cardImageBack.source = "file://mnt/imagen/"+model.get(idx++,"fileName");
                    }
                    else
                        cardImageFront.source = "file://mnt/imagen/"+model.get(idx++,"fileName");

                    flipable.flipped = !flipable.flipped
                }
                if (idx>model.count)
                    idx=0;
            }
        }

        Rectangle {
            color   : Qt.rgba(0, 0, 0, 0.7)
            y       : parent.height-50
            height  : 20
            width   : Screen.width

            MarqueeText {
                opacity : 1
                id      : banner
                anchors.fill: parent
                color   : "white"
                text    : "-hola- esto es una prueba que estoy haciendo aquí y además estoy haciendo que esto"
            }
        }
    }

    FolderListModel {
        id: model
        showDirs    : false
        folder  : "file:///mnt/imagen/"
        nameFilters : ["*.jpg","*.png"]
    }
}
