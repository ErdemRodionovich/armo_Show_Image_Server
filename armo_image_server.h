#ifndef ARMO_IMAGE_SERVER_H
#define ARMO_IMAGE_SERVER_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QDebug>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QPixmap>
#include <armoShowImage.hh>

class armo_Image_Server : public QThread
{
    Q_OBJECT

private:
    QMutex mutex;
    QWaitCondition condition;
    bool abort;
    int argc;
    char **argv;

public:
    armo_Image_Server(QObject *parent = 0);
    ~armo_Image_Server();

    void setArgs(int argcount, char** arguments);
    void startServer();
    void runServer();

signals:
    void showImage(const QString imgSource);
    void showID(const QString id);

public slots:
    void onCallShowImage(const QString imgSource);

protected:
    void run() override;

};

class Armo_Show_Image_i : public POA_armoShowImage
{
public:
    inline Armo_Show_Image_i(){}
    virtual ~Armo_Show_Image_i(){}
    virtual char* showImageByString(const char *mesg);

    armo_Image_Server *armServ;

};

#endif // ARMO_IMAGE_SERVER_H
