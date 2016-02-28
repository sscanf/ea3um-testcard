import QtQuick 2.0

Item {
    property string source
    property bool isCurrentItem:false

    //property alias dimming: dimmer.opacity

    id      : item
    opacity : 1
    width   : image.width
    height  : image.height

    Rectangle{
        id      : itemRect
        z       : 0
        clip    : true
        opacity : 1
        color   : Qt.rgba(220, 220, 220, 0.8)
        width   : 720/1.5
        height  : 322
        radius  : 20


        Column{
            id          : column
            anchors.top : parent.top
            spacing     : 10
            width       : parent.width
            //height: image.height

            Image {
                id: image
                width           : itemRect.width
                height          : itemRect.height
                source          : item.source
                smooth          : true
                onStatusChanged:{
                    if (image.status==Image.Error){
                        image.source="file:///usr/src/Game/jerry.jpg";
                        console.log ("Image source = " + image.source)
                    }
                }
            }

            transitions: Transition {
                NumberAnimation { target: rotation; property: "angle"; duration: 300 }
                NumberAnimation { target: itemRect; property: "scale"; duration: 300 }
            }
        }
    }
}
