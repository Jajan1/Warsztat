#ifndef DODAJ_M_H
#define DODAJ_M_H

#include <QDialog>

namespace Ui {
class dodaj_m;
}

class dodaj_m : public QDialog
{
    Q_OBJECT

public:
    explicit dodaj_m(QWidget *parent = 0);
    ~dodaj_m();

private slots:
    void on_producent_activated(const QString &arg1);

    void on_dodaj_clicked();

    void on_dzial_activated(const QString &arg1);

private:
    Ui::dodaj_m *ui;
    QString producent_qstring="Castorama";
    QString dzial_qstring="Magazyn";
};

#endif // DODAJ_M_H
