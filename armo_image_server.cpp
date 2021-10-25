#include "armo_image_server.h"

armo_Image_Server::armo_Image_Server(QObject *parent) : QThread(parent)
{
    abort = false;
}

armo_Image_Server::~armo_Image_Server(){
    mutex.lock();
    abort = true;
    condition.wakeOne();
    mutex.unlock();
    wait();
}

void armo_Image_Server::run(){
    runServer();
}

void armo_Image_Server::runServer(){

    try {
        CORBA::ORB_var          orb = CORBA::ORB_init(argc, argv);
        CORBA::Object_var       obj = orb->resolve_initial_references("RootPOA");
        PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);

        PortableServer::Servant_var<Armo_Show_Image_i> myShowImage = new Armo_Show_Image_i();
        myShowImage->armServ = this;
        PortableServer::ObjectId_var myShowImageId = poa->activate_object(myShowImage);
        // Obtain a reference to the object, and print it out as a
        // stringified IOR.
        obj = myShowImage->_this();
        CORBA::String_var sior(orb->object_to_string(obj));
        emit showID(QString(sior));
        qDebug()<<sior;
        PortableServer::POAManager_var pman = poa->the_POAManager();
        pman->activate();

        // Block until the ORB is shut down.
        orb->run();
      }
      catch (CORBA::SystemException& ex) {
        qDebug() << "Caught CORBA::" << ex._name() << "\n";
      }
      catch (CORBA::Exception& ex) {
        qDebug() << "Caught CORBA::Exception: " << ex._name() << endl;
      }
      catch (...){
        qDebug() << "Caught unknonw expetion ";
      }

}

void armo_Image_Server::setArgs(int argcount, char **arguments){
    argc = argcount;
    argv = arguments;
}

void armo_Image_Server::startServer(){

    QMutexLocker locker(&mutex);

    if(!isRunning()){
        start(NormalPriority);
    }

}

void armo_Image_Server::onCallShowImage(const QString imgSource){
    emit showImage(imgSource);
}

char* Armo_Show_Image_i::showImageByString(const char *mesg){

    QByteArray ba = mesg;
    QJsonDocument jsdoc(QJsonDocument::fromJson(ba));
    QJsonObject js = jsdoc.object();
    QString extension = js["ext"].toString();
    //QPixmap pm;
    //QByteArray ba_ext = extension.toLocal8Bit();
    //pm.loadFromData(QByteArray::fromBase64(js["data"].toString().toLatin1()), ba_ext.data());
    QString imgSource = "data:image/"+extension+";base64,"+js["data"].toString();

    emit armServ->showImage(imgSource);

    return CORBA::string_dup("Success");

}
