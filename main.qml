import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import "./"

Window {
    visible: true
    width: 320
    height: 320
    title: qsTr("Wearable Clock")

    property bool clickLabel: false

    //signal startTimerSignal;    // timer를 시작하기 위한 signal
    //signal stopTimerSignal;     // timer를 멈추기 위한 signal
    signal howShowTimeSignal(bool clickData);

    function timeSetLabel(data) {   // cpp에서 현재시간을 담아서 보낸 signal과 짝인 slot함수
        console.log("timeSetLabel()!! " + data);
        timeLabel.text = data;
    }

    function amPmSetLabel(data) {   // cpp에서 현재시간을 담아서 보낸 signal과 짝인 slot함수
        console.log("amPmSetLabel()!! " + data);
        amPmLabel.text = data;
    }

    Rectangle {
        id: clockIconRectangle
        anchors.fill: parent
        visible: true

        Image { // 시계 아이콘
            id: goclockscreen
            visible: true
            anchors.centerIn: parent
            width: 100
            height: 100
            source: "clock1.png"

            MouseArea {
                id: clockMouseArea
                anchors.fill: parent

                onClicked: {    // 마우스를 한 번 클릭한 상태
                    KMJ.p_bool = true

                    //console.log("startTimerSignal()!!")
                    //startTimerSignal();     // qml에서 cpp로 signal을 보낸다. (타이머 시작 시그널)

                    clockIconRectangle.visible = false
                    clockScreenRectangle.visible = true}

                onPressed: {    // 마우스를 누르고 있는 상태
                    goclockscreen.source = "clock2.png"
                }

                onReleased: {   // 마우스에서 손을 땐 상태
                    goclockscreen.source = "clock1.png"
                }
            }
        }
    }

    Rectangle {
        id: clockScreenRectangle
        anchors.fill: parent
        visible: false

        Image { // 뒤로가기 버튼
            id: backButton
            source: "back.png"
            width: 30
            height: 30
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    KMJ.p_bool = false;

                    //console.log("stopTimerSignal()!!")
                    //stopTimerSignal();  // timer 없애는 signal 보내기

                    clockIconRectangle.visible = true
                    clockScreenRectangle.visible = false
                }
            }
        }

        Label { // 시간을 보여주긴 위한 label
            id: timeLabel
            anchors.centerIn: parent
            text: "loading..." //KMJ.p_nowtime
            font.pixelSize: 50
            font.bold: true
            font.family: "나눔스퀘어_ac"

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    if (clickLabel == false)    // am pm으로 보여주기
                    {
                        howShowTimeSignal(false);
                        //KMJ.p_show = false
                        clickLabel = true
                    }

                    else if (clickLabel == true)    // 24시간으로 보여주기
                    {
                        howShowTimeSignal(true);
                        //KMJ.p_show = true
                        clickLabel = false
                    }
                }
            }
        }

        Label {
            id: amPmLabel
            y: 163
            text: "" //KMJ.p_ampm
            anchors.left: timeLabel.right
            anchors.leftMargin: 2
            font.bold: true
            font.family: "나눔스퀘어_ac"
        }
    }
}

/*##^##
Designer {
    D{i:9;anchors_x:283}
}
##^##*/
