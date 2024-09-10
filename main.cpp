#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "audioconfig.h"
#include "audiocontroller.h"
#include "audiochart.h"
#include "audiochart2.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;   // Dùng QQmlApplicationEngine thay vi QQuickView
    engine.addImportPath("qrc:/qml/imports"); // Thêm phần QML vô C++

    AudioConfig audioConfig;
    qDebug() << "Address of audioConfig in main:" << &audioConfig;
    AudioController audioController(&audioConfig);

    engine.rootContext()->setContextProperty("audioConfig", &audioConfig);  // AudioConfig dùng setContextProperty
    engine.rootContext()->setContextProperty("audioController", &audioController);



    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);      

    return app.exec();

}
