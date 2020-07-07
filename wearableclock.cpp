#include "wearableclock.h"

WearableClock::WearableClock()
{
    show = true;
}

void WearableClock::setWindow(QQuickWindow *Window)
{
    mainQml = Window;
    siganlAndSlot();
}

void WearableClock::siganlAndSlot()
{
    QObject::connect(mainQml, SIGNAL(startTimerSignal()), this, SLOT(startTimer())); // qml에서 보낸 signal로 인해 startTimer () slot 함수 실행
    QObject::connect(mainQml, SIGNAL(stopTimerSignal()), this, SLOT(stopTimer()));  // qml에서 보낸 signal로 인해 stopTimer() slot 함수 실행
    QObject::connect(this, SIGNAL(nowTimeToQml(QVariant)), mainQml, SLOT(timeSetLabel(QVariant)));    // 현재 시간을 담아서 cpp에서 qml로 signal을 보내어 qml에 있는 timeSetLabel() slot 함수 실행

    QObject::connect(mainQml, SIGNAL(howShowTimeSignal(bool)), this, SLOT(showChange(bool)));
    QObject::connect(this, SIGNAL(amOrPm(QVariant)), mainQml, SLOT(amPmSetLabel(QVariant)));
}

void WearableClock::startTimer()    // QTimer 시작하는 함수
{
    cout << "startTimer()!!" << endl;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(whatTimeNow()));
    timer->start(1000);
}

void WearableClock::stopTimer() // QTimer 없애는 함수
{
    cout << "stopTimer()!!" << endl;
    delete timer;
}

void WearableClock::whatTimeNow()   // 현재 시간을 담아 보내는 함수
{
    cout << "whatTimeNow()!!" << endl;
    time = QTime::currentTime();    // 현재 시간을 time 변수에 담기

    if (show == false) {
        // am pm으로 보여주기
        QString hourText = time.toString("hh"); // 오전 오후로 나누기 위해서 시만 hourText에 담기

        if (hourText.toInt() >= 12) {
            // 오후인 경우
            int hourInt = hourText.toInt() - 12;
            nowTimeText = QString::number(hourInt) + ":" + time.toString("mm:ss");
            emit amOrPm("오후");
            emit nowTimeToQml(nowTimeText);
        } else if (hourText.toInt() < 12) {
            // 오전인 경우
            nowTimeText = time.toString("h:mm:ss");
            emit amOrPm("오전");
            emit nowTimeToQml(nowTimeText);
        }
    } else if (show == true) {
        // 24시간으로 보여주기
        nowTimeText = time.toString("hh:mm:ss");
        emit amOrPm("");
        emit nowTimeToQml(nowTimeText);
    }
}

void WearableClock::showChange(bool clickData)
{
    show = clickData;
}
