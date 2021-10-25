#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <armo_image_global.h>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    armo_Image_Global ar;
    ar.armoServ.setArgs(argc, argv);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    QObject::connect(&engine,SIGNAL(objectCreated(QObject*, const QUrl &)),
                     &ar,SLOT(onEngineCreated(QObject*, const QUrl &)),
                     Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
