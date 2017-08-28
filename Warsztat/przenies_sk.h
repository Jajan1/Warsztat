#ifndef PRZENIES_SK_H
#define PRZENIES_SK_H

#include <QDialog>

namespace Ui {
class przenies_sk;
}

class przenies_sk : public QDialog
{
    Q_OBJECT

public:
    explicit przenies_sk(QWidget *parent = 0);
    ~przenies_sk();

private slots:
    void on_skrzynka_activated(const QString &arg1);

    void on_dzial_activated(const QString &arg1);

    void on_przenies_clicked();

private:
    Ui::przenies_sk *ui;
    QString skrzynka_qstring="Przybornik narzedziowy";
    QString dzial_qstring="Magazyn";
};

#endif // PRZENIES_SK_H
