#ifndef SINGIN_H
#define SINGIN_H

#include <QDialog>

namespace Ui {
class SingIn;
}

class SingIn : public QDialog
{
    Q_OBJECT

public:
    explicit SingIn(QWidget *parent = nullptr);
    ~SingIn();
    QString get_date();
private slots:
    void slot_comp_date();

private:
    Ui::SingIn *ui;
    QString str_date;
};

#endif // SINGIN_H
