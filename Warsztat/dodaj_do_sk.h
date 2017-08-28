#ifndef DODAJ_DO_SK_H
#define DODAJ_DO_SK_H

#include <QDialog>

namespace Ui {
class dodaj_do_sk;
}

class dodaj_do_sk : public QDialog
{
    Q_OBJECT

public:
    explicit dodaj_do_sk(QWidget *parent = 0);
    ~dodaj_do_sk();

private slots:
    void on_skrzynka_activated(const QString &arg1);

    void on_dodaj_clicked();

    void on_akcesorium_activated(const QString &arg1);

private:
    Ui::dodaj_do_sk *ui;
    QString skrzynka_qstring="Przybornik narzedziowy";
    QString akcesorium_qstring="Wiertla";
};

#endif // DODAJ_DO_SK_H
