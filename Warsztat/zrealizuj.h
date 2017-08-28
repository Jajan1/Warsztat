#ifndef ZREALIZUJ_H
#define ZREALIZUJ_H

#include <QDialog>

namespace Ui {
class zrealizuj;
}

class zrealizuj : public QDialog
{
    Q_OBJECT

public:
    explicit zrealizuj(QWidget *parent = 0);
    ~zrealizuj();

private slots:
    void on_zamowienia_activated(const QString &arg1);

    void on_zrealizuj_2_clicked();

private:
    Ui::zrealizuj *ui;
    QString zamowienie_qstring=" ";
};

#endif // ZREALIZUJ_H
