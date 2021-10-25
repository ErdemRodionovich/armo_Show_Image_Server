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
      //catch (omni::COMM_FAILURE_LookupTable &ex){
      //  qDebug() << "Caught CORBA::COMM_FAILURE: " << ex._name() << endl;
      //}

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

char* Armo_Show_Image_i::showImageByString(const char *mesg){

    //TODO show
    //qDebug()<<"Image showed!!! "<<mesg;
    //CORBA::String_var ans = "Success";
    //QString str = "Success";
    //QByteArray ba_str = str.toLocal8Bit();
    return CORBA::string_dup(mesg);

}
