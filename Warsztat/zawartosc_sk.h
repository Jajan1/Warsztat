#ifndef ZAWARTOSC_SK_H
#define ZAWARTOSC_SK_H

#include <QDialog>

namespace Ui {
class zawartosc_sk;
}

class zawartosc_sk : public QDialog
{
    Q_OBJECT

public:
    explicit zawartosc_sk(QWidget *parent = 0);
    ~zawartosc_sk();

private slots:
    void on_comboBox_activated(const QString &arg1);

private:
    Ui::zawartosc_sk *ui;
};

#endif // ZAWARTOSC_SK_H
