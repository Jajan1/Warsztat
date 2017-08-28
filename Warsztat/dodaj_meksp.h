#ifndef DODAJ_MEKSP_H
#define DODAJ_MEKSP_H

#include <QDialog>

namespace Ui {
class dodaj_meksp;
}

class dodaj_meksp : public QDialog
{
    Q_OBJECT

public:
    explicit dodaj_meksp(QWidget *parent = 0);
    ~dodaj_meksp();

private slots:
    void on_producent_activated(const QString &arg1);

    void on_dodaj_clicked();

    void on_Wierla_toggled(bool checked);

    void on_Frezy_toggled(bool checked);

    void on_Tarcze_toggled(bool checked);

    void on_Klucze_toggled(bool checked);

    void on_Mlotki_toggled(bool checked);

    void on_Pilniki_toggled(bool checked);

    void on_Inne_toggled(bool checked);

private:
    Ui::dodaj_meksp *ui;
    int typ=1;
    int id=10;
    QString producent_qstring="Castorama";
};

#endif // DODAJ_MEKSP_H
