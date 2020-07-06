#include "wearableclock.h"

WearableClock::WearableClock()
{

}

void WearableClock::setWindow(QQuickWindow *Window)
{
    mMainView = Window;
    siganlAndSlot();
}

void WearableClock::siganlAndSlot()
{
    QObject::connect(mMainView, SIGNAL(startTimerSignal()), this, SLOT(startChangeTrue())); // qml에서 보낸 signal로 인해 startChangeTrue () slot 함수 실행
    QObject::connect(this, SIGNAL(startChangeComplete()), this, SLOT(startTimer()));        // startChangeTrue() 함수가 제대로 실행되면 signal을 발생하여 startTimer() slot 함수 실행
    QObject::connect(this, SIGNAL(nowTimeToQml(QVariant)), mMainView, SLOT(timeSetLabel(QVariant)));    // 현재 시간을 담아서 cpp에서 qml로 signal을 보내어 qml에 있는 timeSetLabel() slot 함수 실행
}

void WearableClock::startChangeTrue()   // start의 값을 true로 바꿔주는 slot 함수
{
    cout << "startChangeTrue()!!" << endl;
    start = true;
    cout << "change start value: " << start << endl;
    emit startChangeComplete();
}

void WearableClock::startTimer()    // timer 함수
{
    if (start == true){
        cout << "startTimer()!!" << endl;
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(whatTimeNow()));
        timer->start(1000);
    }
}

void WearableClock::whatTimeNow()   // 현재 시간을 담아 보내는 함수
{
    cout << "whatTimeNow()!!" << endl;
    time = QTime::currentTime();
    nowTimeText = time.toString("hh:mm:ss");
    cout << "nowTimeText value: " << nowTimeText.toUtf8().constData() << endl;
    emit nowTimeToQml(nowTimeText);
}
