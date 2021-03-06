#include "singin.h"
#include "ui_singin.h"

SingIn::SingIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SingIn)
{
    ui->setupUi(this);
    this->setWindowTitle("Присоединиться к серверу");
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(slot_comp_date()));
}

void SingIn::slot_comp_date(){
    str_date = ui->line_name->text() + "/" + ui->line_ip->text() + "/" + ui->line_port->text();
}

QString SingIn::get_date(){
    return str_date;
}

SingIn::~SingIn()
{
    delete ui;
}
