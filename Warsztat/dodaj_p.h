#ifndef DODAJ_P_H
#define DODAJ_P_H

#include <QDialog>

namespace Ui {
class dodaj_p;
}

class dodaj_p : public QDialog
{
    Q_OBJECT

public:
    explicit dodaj_p(QWidget *parent = 0);
    ~dodaj_p();

private slots:
    void on_dodaj_clicked();

private:
    Ui::dodaj_p *ui;
};

#endif // DODAJ_P_H
