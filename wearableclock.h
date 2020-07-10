#ifndef WEARABLECLOCK_H
#define WEARABLECLOCK_H

#include "mainview.h"

#include <QQuickView>
#include <QObject>
#include <QTimer>
#include <QTime>
#include <iostream>
#include <string>
#include <QString>

using namespace std;

class WearableClock : public QObject
{
public:
    Q_OBJECT
    Q_PROPERTY(bool p_bool READ getbool WRITE setbool NOTIFY boolchanged)   // timer를 시작할지 끝낼지 결정해주는 변수
    Q_PROPERTY(bool p_show READ getshow WRITE setshow NOTIFY showchanged)

    Q_PROPERTY(QString p_nowtime READ gettime NOTIFY timechanged)           // 현재 시간을 담고 있는 변수
    Q_PROPERTY(QString p_ampm READ getampm NOTIFY ampmchanged)              // 시간 표기법을 담고 있는 변수

public:
    WearableClock();

    //void setWindow(QQuickWindow *Window);
    //void siganlAndSlot();

    bool getbool();             // startOrStop 값을 읽어오는 Q_PROPERTY READ 함수
    void setbool(bool value);   // startOrStop 값을 수정하는 Q_PROPERTY WRITE 함수

    bool getshow();             // show 값을 읽어오는 Q_PROPERTY READ 함수
    void setshow(bool value);   // show 값을 수정하는 Q_PROPERTY WRITE 함수

    QString gettime();          // 현재 시간을 읽어오는 Q_PROPERTY READ 함수

    QString getampm();          // 시간 표기법을 읽어오는 Q_PROPERTY READ 함수

signals:
    //void startChangeComplete(); // start의 값을 변경하고 나면 실행되는 signal
    //void nowTimeToQml(QVariant); // 현재 시간을 qml로 넘겨주는 signal
    //void amOrPm(QVariant);  // am pm을 넘겨주는 signal

    void boolchanged(const bool value); // startOrStop 값이 변경되었을 때 실행되는 Q_PROPERTY signal
    void showchanged(const bool value); // show 값이 변경되었을 때 실행되는 Q_PROPERTY signal
    void timechanged();                 // 현재 시간이 변경되었을 때 실행되는 Q_PROPERTY signal
    void ampmchanged();                 // 시간 표기법이 변경되었을 때 실행되는 Q_PROPERTY signal

public slots:
    void startTimer();  // QTimer 객체를 만들어서 timer를 시작하는 함수
    void stopTimer();   // QTimer를 객체를 없애는 함수
    void whatTimeNow(); // 현재 시간을 구해주는 함수

    //void showChange(const bool value);  // 시간 표기법 관련 함수

private:
    //QQuickWindow *mainQml;

    //bool start;             // qml에서 startTimerSignal을 받았을 때 true 값으로 바꿔주어 timer를 실행하기 위한
    QTimer *timer;
    QTime time;
    QString nowTimeText;    // 현재 시간을 담고 있는 변수

    bool show;              // 시간 표기법 관련 변수

    bool startOrStop;       // timer를 start 할건지 stop 할 건지 구분해주는 변수

    QString nowAmPm;        // 오전/오후/"" 값을 담고 있는 변수
};

#endif // WEARABLECLOCK_H
