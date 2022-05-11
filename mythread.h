#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <arpa/inet.h>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(int sock_id);
    void run() override;
private:
    int socket;
signals:
    void send(QString);
};

#endif // MYTHREAD_H
