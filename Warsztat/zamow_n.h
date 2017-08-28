#ifndef ZAMOW_N_H
#define ZAMOW_N_H

#include <QDialog>

namespace Ui {
class zamow_n;
}

class zamow_n : public QDialog
{
    Q_OBJECT

public:
    explicit zamow_n(QWidget *parent = 0);
    ~zamow_n();

private slots:
    void on_zamow_clicked();

    void on_cofnij_clicked();

    void on_narzedzie_activated(const QString &arg1);

private:
    Ui::zamow_n *ui;
    QString narzedzie_qstring="Mlotek";
    int id, id1;
};

#endif // ZAMOW_N_H
