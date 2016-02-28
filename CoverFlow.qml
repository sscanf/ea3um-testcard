import QtQuick 2.1

PathView{
    id: pathView
    anchors.fill: parent
    focus:true
    property int yPosition
    property int itemSize: 720

    preferredHighlightBegin: 0.5
    preferredHighlightEnd: 0.5
     Path {
         id: oscar2

         startX: coverFlow.width -200
         startY: -200
         PathAttribute { name: "itemScale"; value: 0.2 }
         PathAttribute { name: "z"; value: 0 }
         PathAttribute { name: "itemOpacity"; value: 0.5 }

         PathQuad { x: coverFlow.width/2; y : coverFlow.height-400; controlX: coverFlow.width/2; controlY: coverFlow.height -400 }
         PathAttribute { name: "itemScale"; value: 1.5 }
         PathAttribute { name: "z"; value: 10 }
         PathAttribute { name: "itemOpacity"; value: 1 }
     }

     Path {
         id: circlePath

         startX: -200; startY: coverFlow.height
         PathAttribute { name: "itemScale"; value: 0.8 }
         PathAttribute { name: "z"; value: 0 }
         PathAttribute { name: "angle"; value: 80 }
         PathAttribute { name: "angle2"; value: 0 }
         PathAttribute { name: "dimming"; value: 0 }

         PathCubic {
             x: coverFlow.width + 100; y: coverFlow.height
             control1X: -30; control1Y: coverFlow.height / 2
             control2X: coverFlow.width + 30; control2Y: coverFlow.height / 2
         }
         PathAttribute { name: "itemScale"; value: 0.8 }
         PathAttribute { name: "z"; value: 10 }
         PathAttribute { name: "angle"; value: -80 }
         PathAttribute { name: "angle2"; value: 0 }
         PathAttribute { name: "dimming"; value: 0.0 }
     }

     Path {
        id: oscar3
        startX: -720; startY: mainPage.height * 1/3
        PathAttribute { name: "z"; value: 0 }
        PathAttribute { name: "itemAngle"; value: 50 }
        PathAttribute { name: "itemScale"; value: 0.2 }
        PathAttribute { name: "itemOpacity"; value: 0 }

        PathLine { x: mainPage.width / 3; y: (yPosition + mainPage.height) * 1/3;  }
        PathAttribute { name: "z"; value: 100 }
        PathAttribute { name: "itemAngle"; value: 0 }
        PathAttribute { name: "itemScale"; value: 1 }
        PathAttribute { name: "itemOpacity"; value: 1 }

        PathLine { x: mainPage.width+720; y: yPosition} //mainPage.height * 1/3; }
        PathAttribute { name: "z"; value: 0 }
 //       PathAttribute { name: "itemAngle"; value: -50 }
        PathAttribute { name: "itemScale"; value: 0.2 }
        PathAttribute { name: "itemOpacity"; value: 0 }
    }

     Path {
         id     : oscar4
         startX : -720
         startY : yPosition  + mainPage.height * 1 / 3
         PathAttribute { name: "z"; value: 0 }
         PathAttribute { name: "itemScale"; value: 0.1 }
         PathAttribute { name: "itemOpacity"; value: 0 }
         PathAttribute { name: "itemAngle"; value: 50 }

         PathLine { x: 0; y: yPosition  + mainPage.height * 1/3; }
         PathAttribute { name: "z"; value: 100 }
         PathAttribute { name: "itemAngle"; value: 0 }
         PathAttribute { name: "itemScale"; value: 1}
         PathAttribute { name: "itemOpacity"; value: 1 }

         PathQuad { x: mainPage.width; y: yPosition  + mainPage.height* 1/3; controlX: 3*mainPage.width/4; controlY: yPosition  +mainPage.height *1/3}
         PathAttribute { name: "z"; value: 0 }
         PathAttribute { name: "itemAngle"; value: -50 }
         PathAttribute { name: "itemScale"; value: 0.1 }
         PathAttribute { name: "itemOpacity"; value: 0 }
     }

     Path {
         id     : oscar5
         startX :0
         startY : 0
         PathAttribute { name: "z"; value: 0 }

         PathQuad { x: mainPage.width; y: yPosition  + mainPage.height* 1/3; controlX: 3*mainPage.width/4; controlY: yPosition  +mainPage.height *1/3}
             PathAttribute { name: "z"; value: 180 }

         PathLine { x: 0; y: 0; }
         PathAttribute { name: "z"; value: 0 }
     }

     path: oscar5
}
