#ifndef ZWOLNIJ_H
#define ZWOLNIJ_H

#include <QDialog>

namespace Ui {
class zwolnij;
}

class zwolnij : public QDialog
{
    Q_OBJECT

public:
    explicit zwolnij(QWidget *parent = 0);
    ~zwolnij();

private slots:
    void on_pracownik_activated(const QString &arg1);

    void on_zwolnij_2_clicked();

private:
    Ui::zwolnij *ui;
    QString pracownik_qstring="Jan Daron";
};

#endif // ZWOLNIJ_H
