#ifndef ZAMOW_A_H
#define ZAMOW_A_H

#include <QDialog>

namespace Ui {
class zamow_a;
}

class zamow_a : public QDialog
{
    Q_OBJECT

public:
    explicit zamow_a(QWidget *parent = 0);
    ~zamow_a();

private slots:
    void on_zamow_clicked();

    void on_cofnij_clicked();

    void on_akcesorium_activated(const QString &arg1);

private:
    Ui::zamow_a *ui;
    QString akcesorium_qstring="Zasilacz";
    int id, id1;
};

#endif // ZAMOW_A_H
