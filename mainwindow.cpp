#include "mainwindow.h"
#include "ui_mainwindow.h"



//static int sockfd; // Main socket

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Устанавливаем графинтерфейс
    ui->setupUi(this);
    // Настраиваем кнопку
    ui->butt_send->setIcon(QPixmap(":/key_Enter.png").scaled(ui->butt_send->size()));
    ui->butt_send->setIconSize(ui->butt_send->size());
    // Открываем окно ввода данных
    if(!d_win.exec()){
        exit(0);
    }
    // Обрабатываем считанные данные
    QStringList date_serv = d_win.get_date().split("/");
    // Заполлняем поля данными
    username = date_serv[0];
    ip = date_serv[1];
    port = date_serv[2].toInt();
    sockfd = 0;
    // Меняем имя главного окна
    this->setWindowTitle("Чат пользователя " + username);
    // Инициализируем сокет
    init_sock();
    // Конектим кнопку с отправкой сообщения
    connect(ui->butt_send, SIGNAL(clicked()), this, SLOT(slot_butt_send()));
}

void MainWindow::slot_butt_send(){
    // При нажатии на кнопку отправляем сообщение на сервер
    send(sockfd, ui->plane_send->toPlainText().toUtf8().constData(), ui->plane_send->toPlainText().size() + 1, 0);
    // Чистим поле ввода
    ui->plane_send->clear();
}

void MainWindow::update (QString str)
{
    // Записываем ответ сервера в поле вывода
    ui->plane_recv->insertPlainText(str);
}

void MainWindow::init_sock(){
    struct sockaddr_in server_addr;
    // Настраиваем сокет
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip.toStdString().c_str());
    server_addr.sin_port = htons(port);
    // Конектим сокет с сервером
    int err = ::connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (err == -1) {
        perror("ERROR: can not connect to server\n");
        exit(0);
    }
    // Отправляем имя пользователя
    send(sockfd, username.toUtf8().constData(), 32, 0);
    // Запускаем отдельный поток для обработки приема
    thread = new MyThread(sockfd);
    connect(thread, SIGNAL(send(QString)), this, SLOT(update(QString)));
    thread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

