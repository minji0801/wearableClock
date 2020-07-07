#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <wearableclock.h>
#include <QQuickView>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    WearableClock *event = new WearableClock();

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject *root = engine.rootObjects()[0];

    event->setWindow(qobject_cast<QQuickWindow *>(root));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
