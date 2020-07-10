#include "wearableclock.h"

WearableClock::WearableClock()
{
    show = true;                // 12시간으로 보여줄지(false) 24시간으로 보여줄지(true)
    startOrStop = true;         // timer 시작할건지(true) 없앨건지(false)
    nowTimeText = "loading..."; // 현재 시간 초기화
    nowAmPm = "";               // 오전오후 초기화
}

/* signal slot 사용했을 때의 부분
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
*/

bool WearableClock::getbool() // startOrStop 값을 읽어오는 Q_PROPERTY READ 함수 - 사실상 쓰이지 않는다.
{
    cout << "WearableClock::getbool value : " << startOrStop << endl;
    return startOrStop;
}

void WearableClock::setbool(bool value) //  startOrStop값을 수정하는 Q_PROPERTY WRITE 함수
{
    cout << "WearableClock::setbool value : " << value << endl;
    startOrStop = value;
    emit boolchanged(value);    // 값이 바꼈으므로 signal을 반드시 실행시켜야 업데이트된다. ★★★

    if(startOrStop == true)
    {
        startTimer();   // startOrStop 값이 true면 timer 시작하기
    }

    else if (startOrStop == false)
    {
        stopTimer();    // startOrStop 값이 false면 timer 없애기
    }
}


bool WearableClock::getshow() // show 값을 읽어오는 Q_PROPERTY READ 함수 - 사실상 쓰이지 않는다.
{
    cout << "WearableClock::getshow value : " << show << endl;
    return show;
}

void WearableClock::setshow(bool value) //  show 값을 수정하는 Q_PROPERTY WRITE 함수
{
    cout << "WearableClock::setshow value : " << value << endl;
    show = value;
    emit showchanged(value);    // 값이 바꼈으므로 반드시 signal을 실행시켜야 업데이트된다. ★★★
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

    if (show == false)  // am pm으로 보여주기
    {
        QString hourText = time.toString("hh"); // 오전 오후로 나누기 위해서 시만 hourText에 담기

        if (hourText.toInt() > 12)
        {
            // 오후인 경우
            int hourInt = hourText.toInt() - 12;
            nowTimeText = QString::number(hourInt) + ":" + time.toString("mm:ss");
            cout << "nowTimeText value : " << nowTimeText.toUtf8().data() << endl;
            emit timechanged(); // ★★★★★ WRITE 함수를 사용해서 값을 업데이트하지 않아도 signal을 사용해야지만 값이 업데이트 된다!!!

            //emit amOrPm("오후");
            //emit nowTimeToQml(nowTimeText);

            nowAmPm = "오후";
            cout << "nowAmPm value : " << nowAmPm.toLocal8Bit().data() << endl;
            emit ampmchanged();
        }

        else if (hourText.toInt() == 12)
        {
            // 오후 12시 인 경우
            nowTimeText = time.toString("h:mm:ss");
            cout << "nowTimeText value : " << nowTimeText.toUtf8().data() << endl;
            emit timechanged();

            //emit amOrPm("오후");
            //emit nowTimeToQml(nowTimeText);

            nowAmPm = "오후";
            cout << "nowAmPm value : " << nowAmPm.toLocal8Bit().data() << endl;
            emit ampmchanged();
        }

        else if (hourText.toInt() < 12)
        {
            // 오전인 경우
            nowTimeText = time.toString("h:mm:ss");
            cout << "nowTimeText value : " << nowTimeText.toUtf8().data() << endl;
            emit timechanged();

            //emit amOrPm("오전");
            //emit nowTimeToQml(nowTimeText);

            nowAmPm = "오전";
            cout << "nowAmPm value : " << nowAmPm.toLocal8Bit().data() << endl;
            emit ampmchanged();
        }
    }

    else if (show == true)  // 24시간으로 보여주기
    {
        nowTimeText = time.toString("hh:mm:ss");
        cout << "nowTimeText value : " << nowTimeText.toUtf8().data() << endl;
        emit timechanged();

        //emit amOrPm("");
        //emit nowTimeToQml(nowTimeText);

        nowAmPm = "";
        cout << "nowAmPm value : " << nowAmPm.toLocal8Bit().data() << endl;
        emit ampmchanged();
    }
}

/*
void WearableClock::showChange(bool clickData)
{
    show = clickData;
}
*/

QString WearableClock::gettime()    // 현재 시간을 읽어오는 Q_PROPERTY READ 함수
{
    return nowTimeText;
}

QString WearableClock::getampm()    // 시간 표기법을 읽어오는 Q_PROPERTY READ 함수
{
    return nowAmPm;
}
