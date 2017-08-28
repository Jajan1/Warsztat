#ifndef ZAMOW_S_H
#define ZAMOW_S_H

#include <QDialog>

namespace Ui {
class zamow_s;
}

class zamow_s : public QDialog
{
    Q_OBJECT

public:
    explicit zamow_s(QWidget *parent = 0);
    ~zamow_s();

private slots:
    void on_zamow_clicked();

    void on_cofnij_clicked();

    void on_skrzynka_activated(const QString &arg1);

private:
    Ui::zamow_s *ui;
    QString skrzynka_qstring="Przybornik narzedziowy";
    int id, id1;
};

#endif // ZAMOW_S_H
