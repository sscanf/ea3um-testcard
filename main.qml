import QtQuick 2.5
import QtMultimedia 5.5
import QtQuick.Window 2.2
import Qt.labs.folderlistmodel 2.1
import OFilter 1.0

Window {
    property int idx;
    property int timelapse;
    property int slideEnabled;
    property int videoEnabled;

    visible     : true
    id          : mainPage
    width       : Screen.width;
    height      : Screen.height;
    color       : "black"
    idx         : 0
    timelapse   : 3000
    slideEnabled: 0
    videoEnabled: 1

    Component.onCompleted: {
        banner.enabled  = Settings.value ("banner/enabled",1);
        banner.text     = Settings.value ("banner/text","EA3UM carta ATV ** ");
        timelapse       = Settings.value ("slide/timelapse","3000")*1000;
        slideEnabled    = Settings.value ("slide/enabled","0");
        videoEnabled    = Settings.value ("video/enabled","1");

        if (camera.availability === 0 && videoEnabled === 1){
            timer.stop()
            camara.opacity=1
            flipable.opacity=0
        }

        if (videoEnabled === 0)
            camera.stop();

        if (slideEnabled === 0) {
            cardImageFront.source = "file://mnt/imagen/carta.jpg";
            cardImageBack.source = "file://mnt/imagen/carta.jpg";
            timer.stop();
         }
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
                id      : rotation
                origin.x: flipable.width/2
                origin.y: flipable.height/2
                axis.x  : 0;
                axis.y  : 1;
                axis.z  : 0
                angle   : 0
            }

            states: State {
                name: "back"
                PropertyChanges { target: rotation; angle: 180 }
                when: flipable.flipped
            }

            transitions: Transition {
                NumberAnimation { target: rotation; property: "angle"; easing.period: 0.5; easing.type: Easing.OutElastic; duration: 1500 }
            }
        }

        Rectangle {
            id      : camara
            opacity : 0
            color   : "black"
            visible : true
            width   : 640
            height  : 480
            x       : (parent.width/2) - width/2
            y       : (parent.height/2) - height/2
            clip    : true

            Camera {
                id  : camera
            }

//            MyFilter {
//                id        : filter
//                onFinished: console.log ("Finished result = " + result);
//            }

            VideoOutput {
                source      : camera
//                filters     : [filter]
                anchors.fill: parent
                focus       : visible // to receive focus and capture key events when visible
            }
        }

        Timer {
            id                  : timer
            interval            : timelapse
            running             : slideEnabled
            triggeredOnStart    : true
            repeat              : true

            onTriggered: {

                do {
                    var fileName = model.get(idx,"fileName");
                    console.log ("'"+fileName+"'")
                    idx = (idx + 1) % model.count;
                }while ( fileName === undefined );

                if ( fileName !== undefined) {
                    if (!flipable.flipped)
                        cardImageBack.source = "file://mnt/imagen/"+fileName;
                    else
                        cardImageFront.source = "file://mnt/imagen/"+fileName;
                }
                if (model.count>1) {
                   flipable.flipped = !flipable.flipped
                }
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
        folder      : "file:///mnt/imagen/"
        nameFilters : ["*.jpg","*.png"]
    }
}
