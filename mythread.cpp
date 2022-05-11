#include "mythread.h"

MyThread::MyThread(int sock_id) :
    socket(sock_id)
{

}

void MyThread::run(){
    char msg[255];
    while (1) {
        int receive = ::recv(socket, msg, strlen(msg) + 1, 0);
        if (receive > 0) { // succesfully
            emit send(msg);
        }
        memset(&msg, 0, strlen(msg) + 1);
    }
}
