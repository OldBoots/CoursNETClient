#include "mainwindow.h"
#include "ui_mainwindow.h"

static QString nick_me;

static int max_clients;
static int buffer_size;
static int lenght;
static int max_msg_len;
static int packet_len;

static int sockfd; // Main socket

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
    connect(ui->butt_send, SIGNAL(clicked()), this, SLOT());
}

void *MainWindow::sendMsgHandler(void* t) {
    QString message;
    char buffer[64] = {};
    while (1) {
        if (::strcmp(message.toStdString().c_str(), "exit") == 0) // exit app when user input "exit"
            break;
        else {
            sprintf(buffer, "%s: %s\n", nick_me.toUtf8().constData(), message.toStdString().c_str());
            send(sockfd, buffer, strlen(buffer), 0);
        }
        message.clear();
        memset(&buffer, 0, lenght + 32);
    }
    qDebug("fffdfdfd");
    return t;
}

void *MainWindow::recvMsgHandler(void* t) {
    QString message;
    while (1) {
        int receive = ::recv(sockfd, message.data(), packet_len, 0);
        if (receive > 0) { // succesfully
            printf("%s", message.data());
            //            customPrintStr();
        }
        message.clear();
//        memset(message.data(), 0, message.size() + 1/*sizeof(message)*/);
    }
    return t;
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
    pthread_t sendMsgThread;
    if (::pthread_create(&sendMsgThread, NULL, sendMsgHandler, NULL) != 0) {
        perror("ERROR: can not create sending thread\n");
        exit(0);
    }
    pthread_t recvMsgThread;
    if (::pthread_create(&recvMsgThread, NULL, recvMsgHandler, NULL) != 0) {
        perror("ERROR: can not create receving thread\n");
        exit(0);
    }
    ::close(sockfd);
}

MainWindow::~MainWindow()
{
    delete ui;
}

