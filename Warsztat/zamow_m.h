#ifndef ZAMOW_M_H
#define ZAMOW_M_H

#include <QDialog>

namespace Ui {
class zamow_m;
}

class zamow_m : public QDialog
{
    Q_OBJECT

public:
    explicit zamow_m(QWidget *parent = 0);
    ~zamow_m();

private slots:
    void on_zamow_clicked();

    void on_cofnij_clicked();

    void on_maszyna_activated(const QString &arg1);

private:
    Ui::zamow_m *ui;
    QString maszyna_qstring="Imadlo";
    int id, id1;
};

#endif // ZAMOW_M_H
