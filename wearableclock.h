#ifndef WEARABLECLOCK_H
#define WEARABLECLOCK_H

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

public:
    WearableClock();

    void setWindow(QQuickWindow *Window);
    void siganlAndSlot();

signals:
    void startChangeComplete(); // start의 값을 변경하고 나면 실행되는 signal
    void nowTimeToQml(QVariant); // 현재 시간을 qml로 넘겨주는 signal

public slots:
    void startChangeTrue(); // start의 값을 true로 바꿔주는 slot 함수
    void startTimer();  // Timer를 시작하는 함수
    void whatTimeNow(); // 현재 시간을 구해주는 함수

private:
    QQuickWindow *mMainView;

    bool start; // qml에서 startTimerSignal을 받았을 때 true 값으로 바꿔주어 timer를 실행하기 위한
    QTimer *timer;
    QTime time;
    QString nowTimeText;
};

#endif // WEARABLECLOCK_H
