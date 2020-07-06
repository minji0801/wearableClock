import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4

Window {
    visible: true
    width: 320
    height: 320
    title: qsTr("Wearable Clock")

    signal startTimerSignal;    // qml에서 cpp로 보낼 signal

    function timeSetLabel(data) {   // cpp에서 현재시간을 담아서 보낸 signal과 짝인 slot함수
        console.log("timeSetLabel()!! " + data);
    }

    StackView {
        id: stackView
        anchors.fill: parent


        initialItem: Item { // StackView에서 이부분을 설정하지 않으면 처음 화면으로 돌아가려고 할 때 돌아갈 수가 없다.
            id: element


            Image { // 시계 아이콘 -> 클릭하면 clockscreen으로 넘어간다.
                id: goclockscreen
                anchors.centerIn: parent
                width: 100
                height: 100
                source: "clock1.png"

                MouseArea {
                    anchors.fill: parent

                    onClicked: {    // 마우스를 한 번 클릭한 상태
                        console.log("startTimerSignal()!!")
                        startTimerSignal();                                     // qml에서 cpp로 signal을 보낸다. (타이머 시작 시그널)

                        stackView.push(Qt.resolvedUrl("qrc:/clockscreen.qml"))  // StackView에 clockscreen을 push하여 보여준다.
                    }

                    onPressed: {    // 마우스를 누르고 있는 상태
                        goclockscreen.source = "clock2.png"
                    }

                    onReleased: {   // 마우스에서 손을 땐 상태
                        goclockscreen.source = "clock1.png"
                    }
                }
            }
        }
    }
}
