#ifndef DODAJ_SK_H
#define DODAJ_SK_H

#include <QDialog>

namespace Ui {
class dodaj_sk;
}

class dodaj_sk : public QDialog
{
    Q_OBJECT

public:
    explicit dodaj_sk(QWidget *parent = 0);
    ~dodaj_sk();

private slots:
    void on_producent_activated(const QString &arg1);

    void on_dodaj_clicked();

private:
    Ui::dodaj_sk *ui;
    QString producent_qstring="Castorama";
};

#endif // DODAJ_SK_H
