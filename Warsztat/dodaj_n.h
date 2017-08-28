#ifndef DODAJ_N_H
#define DODAJ_N_H

#include <QDialog>

namespace Ui {
class dodaj_n;
}

class dodaj_n : public QDialog
{
    Q_OBJECT

public:
    explicit dodaj_n(QWidget *parent = 0);
    ~dodaj_n();

private slots:
    void on_narzedzie_trwale_toggled(bool checked);

    void on_meksp_toggled(bool checked);

    void on_dodaj_clicked();

private:
    Ui::dodaj_n *ui;
    bool nt_selected=false;
    bool meksp_selected=false;
};

#endif // DODAJ_N_H
