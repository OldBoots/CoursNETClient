#include "mainwindow.h"
#include "ui_mainwindow.h"



//static int sockfd; // Main socket

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(!d_win.exec()){
        exit(0);
    }
    date_serv = d_win.get_date().split("/");

    max_clients = 100;
    buffer_size = 255;
    lenght = 255;
    max_msg_len = 255;
    packet_len =  255 + 32;
    nick_me = date_serv[0];

    sockfd = 0;

    init_sock();

    ui->butt_send->setIcon(QPixmap(":/key_Enter.png").scaled(ui->butt_send->size()));
    ui->butt_send->setIconSize(ui->butt_send->size());

    connect(ui->butt_send, SIGNAL(clicked()), this, SLOT(slot_butt_send()));
}

void MainWindow::slot_butt_send(){
    send(sockfd, ui->plane_send->toPlainText().toUtf8().constData(), ui->plane_send->toPlainText().size() + 1, 0);
    ui->plane_send->clear();
}

void MainWindow::update (QString str)
{
    ui->plane_recv->insertPlainText(str);
}

void *MainWindow::recvMsgHandler(void *) {
    //    QString message;
    char msg[255];
    while (1) {
        int receive = ::recv(sockfd, msg, strlen(msg) + 1, 0);
        if (receive > 0) { // succesfully
            ui->plane_recv->setText(ui->plane_recv->toPlainText() + "\n\nghghg");
            printf("%s", msg);
        }
        //        message.clear();
        memset(&msg, 0, strlen(msg) + 1);
    }
    pthread_exit(0);
}

void MainWindow::init_sock(){
    struct sockaddr_in server_addr;
    /* Socket settings */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(date_serv[1].toStdString().c_str());
    server_addr.sin_port = htons(date_serv[2].toInt());
    // Connect to Server
    int err = ::connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (err == -1) {
        perror("ERROR: can not connect to server\n");
        exit(0);
    }
    // Send username
    send(sockfd, nick_me.toUtf8().constData(), 32, 0);

    thread = new MyThread(sockfd);
    connect(thread, SIGNAL(send(QString)), this, SLOT(update(QString)));
    thread->start();

//    pthread_t recvMsgThread;
//    if (::pthread_create(&recvMsgThread, NULL, MainWindow::recvMsgHandler, NULL) != 0) {
//        perror("ERROR: can not create receving thread\n");
//        exit(0);
//    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

