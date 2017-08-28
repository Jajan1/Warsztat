#ifndef ZGLOSZENIE_H
#define ZGLOSZENIE_H

#include <QDialog>

namespace Ui {
class zgloszenie;
}

class zgloszenie : public QDialog
{
    Q_OBJECT

public:
    explicit zgloszenie(QWidget *parent = 0);
    ~zgloszenie();

private slots:
    void on_przedmiot_activated(const QString &arg1);

    void on_zglos_clicked();

    void on_uszkodzone_toggled(bool checked);

    void on_zgubione_toggled(bool checked);

    void on_zniszczone_toggled(bool checked);

private:
    Ui::zgloszenie *ui;
    QString przedmiot_qstring="Mlotek";
    bool uszk=false;
    bool zgub=false;
    bool znisz=false;
};

#endif // ZGLOSZENIE_H
