#include <QObject>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Field.h"

#define WINDOW_WIDTH  1440 //1920
#define WINDOW_HEIGHT 810  //1080

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Field field(&engine, WINDOW_WIDTH, WINDOW_HEIGHT);

    engine.rootContext()->setContextProperty("field", &field);
    engine.rootContext()->setContextProperty("kart", field.kart());
    engine.rootContext()->setContextProperty("ball", field.ball());

    const QUrl url("src/Main.qml");
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}