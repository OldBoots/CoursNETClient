#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "singin.h"
#include "mythread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

private:
    void init_sock();
    void *recvMsgHandler(void *);

private slots:
    void slot_butt_send();
    void update (QString str);
private:
    Ui::MainWindow *ui;
    QStringList date_serv;
    SingIn d_win;

    QString nick_me;

    int max_clients;
    int buffer_size;
    int lenght;
    int max_msg_len;
    int packet_len;
    int sockfd;

    MyThread *thread;
};

#endif // MAINWINDOW_H
