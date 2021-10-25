#ifndef ARMO_IMAGE_GLOBAL_H
#define ARMO_IMAGE_GLOBAL_H

#include <QObject>
#include <QCoreApplication>
#include <armo_image_server.h>

class armo_Image_Global : public QObject
{
    Q_OBJECT

private:

    QObject* proot;

public:
    explicit armo_Image_Global(QObject *parent = nullptr);

    armo_Image_Server armoServ;

public slots:
    void onEngineCreated(QObject *obj, const QUrl &objUrl);
    void onShowID(const QString id);
    void onShowImage(const QImage &img);

};

#endif // ARMO_IMAGE_GLOBAL_H
