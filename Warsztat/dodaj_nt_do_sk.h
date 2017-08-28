#ifndef DODAJ_NT_DO_SK_H
#define DODAJ_NT_DO_SK_H

#include <QDialog>

namespace Ui {
class dodaj_nt_do_sk;
}

class dodaj_nt_do_sk : public QDialog
{
    Q_OBJECT

public:
    explicit dodaj_nt_do_sk(QWidget *parent = 0);
    ~dodaj_nt_do_sk();

private slots:
    void on_skrzynka_activated(const QString &arg1);

    void on_dodaj_clicked();

    void on_narzedzie_trwale_activated(const QString &arg1);

private:
    Ui::dodaj_nt_do_sk *ui;
    QString skrzynka_qstring="Przybornik narzedziowy";
    QString nt_qstring="Mlotek";
};

#endif // DODAJ_NT_DO_SK_H
