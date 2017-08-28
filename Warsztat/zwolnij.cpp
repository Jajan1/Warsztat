#include "zwolnij.h"
#include "ui_zwolnij.h"
#include <QtSql>

zwolnij::zwolnij(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::zwolnij)
{
    ui->setupUi(this);

    QSqlQueryModel *model_zwp = new QSqlQueryModel;
    QSqlQuery *queryzwp = new QSqlQuery;
    queryzwp->exec("select CONCAT(imie, ' ', nazwisko) from pracownik");
    model_zwp->setQuery(*queryzwp);
    ui->pracownik->setModel(model_zwp);
}

zwolnij::~zwolnij()
{
    delete ui;
}

void zwolnij::on_pracownik_activated(const QString &arg1)
{
    pracownik_qstring = arg1;
}

void zwolnij::on_zwolnij_2_clicked()
{
    QSqlQuery *query_zw = new QSqlQuery;
    QSqlQuery *query_usd = new QSqlQuery;

    if (pracownik_qstring == "Jan Daron"){
        query_usd->prepare("DELETE FROM dzial_pracownik WHERE Pracownik_Id=1");
        query_zw->prepare("DELETE FROM pracownik WHERE Id=1");
    } else if (pracownik_qstring == "Jan Janowski"){
        query_usd->prepare("DELETE FROM dzial_pracownik WHERE Pracownik_Id=2");
        query_zw->prepare("DELETE FROM pracownik WHERE imie='Jan' and nazwisko='Janowski'");
    } else if (pracownik_qstring == "Natalia Hornowska"){
        query_usd->prepare("DELETE FROM dzial_pracownik WHERE Pracownik_Id=3");
        query_zw->prepare("DELETE FROM pracownik WHERE Id=3");
    } else {
        query_zw->prepare("DELETE FROM pracownik WHERE Id=0");
    }
    query_usd->exec();
    query_zw->exec();

    this->close();
}
