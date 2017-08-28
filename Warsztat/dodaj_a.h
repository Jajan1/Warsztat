#ifndef DODAJ_A_H
#define DODAJ_A_H

#include <QDialog>

namespace Ui {
class dodaj_a;
}

class dodaj_a : public QDialog
{
    Q_OBJECT

public:
    explicit dodaj_a(QWidget *parent = 0);
    ~dodaj_a();

private slots:
    void on_producent_activated(const QString &arg1);

    void on_dodaj_clicked();

    void on_do_elek_activated(const QString &arg1);

private:
    Ui::dodaj_a *ui;
    QString producent_qstring="Castorama";
    QString do_elek_qstring="Wiertarka";
};

#endif // DODAJ_A_H
