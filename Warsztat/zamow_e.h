#ifndef ZAMOW_E_H
#define ZAMOW_E_H

#include <QDialog>

namespace Ui {
class zamow_e;
}

class zamow_e : public QDialog
{
    Q_OBJECT

public:
    explicit zamow_e(QWidget *parent = 0);
    ~zamow_e();

private slots:
    void on_zamow_clicked();

    void on_cofnij_clicked();

    void on_elektronarzedzie_activated(const QString &arg1);

private:
    Ui::zamow_e *ui;
    QString elektronarzedzie_qstring="Wiertarka";
    int id, id1;
};

#endif // ZAMOW_E_H
