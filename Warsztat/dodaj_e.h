#ifndef DODAJ_E_H
#define DODAJ_E_H

#include <QDialog>

namespace Ui {
class dodaj_e;
}

class dodaj_e : public QDialog
{
    Q_OBJECT

public:
    explicit dodaj_e(QWidget *parent = 0);
    ~dodaj_e();

private slots:
    void on_producent_activated(const QString &arg1);

    void on_dodaj_clicked();

    void on_skrzynka_activated(const QString &arg1);

private:
    Ui::dodaj_e *ui;
    QString producent_qstring="Castorama";
    QString skrzynka_qstring="Przybornik narzedziowy";
};

#endif // DODAJ_E_H
