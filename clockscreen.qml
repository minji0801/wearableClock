import QtQuick 2.0
import QtQuick.Controls 2.5

Item {
    id: element
    width: 320
    height: 320

    Component.onCompleted: {
        var previousItem = stackView.get(StackView.index - 1);  // stackview의 이전 index의 objectName을 가져온다.
        if (previousItem.objectName === "mainScreen") {
            console.log("data2: " + previousItem.data2);
        }
    }

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
                stackView.pop();    // StackView에서 pop 하기 -> 이 화면은 날라가고 이전 화면이 보여진다.
            }
        }
    }

    Label { // 시간을 보여주긴 위한 label
        id: timeLabel
        anchors.centerIn: parent
        text: "00:00:00"
        font.pixelSize: 60
        font.bold: true
        font.family: "나눔스퀘어_ac"
    }
}
