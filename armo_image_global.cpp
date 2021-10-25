#include "armo_image_global.h"

armo_Image_Global::armo_Image_Global(QObject *parent) : QObject(parent)
{

}

void armo_Image_Global::onEngineCreated(QObject *obj, const QUrl &objUrl){

    if(!obj){
        QCoreApplication::exit(-1);
        return;
    }

    proot = obj;

    QObject::connect(&armoServ, SIGNAL(showID(const QString)),
                     this, SLOT(onShowID(const QString)),
                     Qt::QueuedConnection);

    QObject::connect(&armoServ, SIGNAL(showImage(const QString)),
                     this, SLOT(onShowImage(const QString)),
                     Qt::QueuedConnection);

    QObject::connect(this, SIGNAL(showImage(QString)),
                     proot, SIGNAL(showImage(QString)),
                     Qt::QueuedConnection);

    armoServ.startServer();

}

void armo_Image_Global::onShowID(const QString id){

    QMetaObject::invokeMethod(proot,
                              "setServID",
                              Qt::QueuedConnection,
                              Q_ARG(QVariant, id));

}

void armo_Image_Global::onShowImage(const QString imgSource){

    emit showImage(imgSource);

}
