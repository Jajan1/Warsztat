#include "przenies_sk.h"
#include "ui_przenies_sk.h"
#include <QtSql>

przenies_sk::przenies_sk(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::przenies_sk)
{
    ui->setupUi(this);

    QSqlQueryModel *model_psk = new QSqlQueryModel;
    QSqlQuery *querypsk = new QSqlQuery;
    querypsk->exec("select opis from skrzynka");
    model_psk->setQuery(*querypsk);
    ui->skrzynka->setModel(model_psk);

    QSqlQueryModel *model_pd = new QSqlQueryModel;
    QSqlQuery *querypd = new QSqlQuery;
    querypd->exec("select nazwa from dzial");
    model_pd->setQuery(*querypd);
    ui->dzial->setModel(model_pd);
}

przenies_sk::~przenies_sk()
{
    delete ui;
}

void przenies_sk::on_skrzynka_activated(const QString &arg1)
{
    skrzynka_qstring = arg1;
}

void przenies_sk::on_dzial_activated(const QString &arg1)
{
    dzial_qstring = arg1;
}

void przenies_sk::on_przenies_clicked()
{
    QSqlQuery *query_ps = new QSqlQuery;

    if (skrzynka_qstring == "Przybornik narzedziowy"){
        query_ps->prepare("UPDATE `dzial_wypozycz` SET data_wypozyczenia=CURDATE(), data_zwrotu=CURDATE(), Dzial_IDdzial=? WHERE Skrzynka_IDskrzynka=1");
    } else if (skrzynka_qstring == "Zestaw malego mechanika"){
        query_ps->prepare("UPDATE `dzial_wypozycz` SET data_wypozyczenia=CURDATE(), data_zwrotu=CURDATE(), Dzial_IDdzial=? WHERE Skrzynka_IDskrzynka=2");
    } else {
        query_ps->prepare("UPDATE `dzial_wypozycz` SET data_wypozyczenia=CURDATE(), data_zwrotu=CURDATE(), Dzial_IDdzial=? WHERE Skrzynka_IDskrzynka=0");
    }
    if (dzial_qstring == "Magazyn"){
        query_ps->addBindValue(1);
    } else if (dzial_qstring == "Hala produkcyjna"){
        query_ps->addBindValue(2);
    } else if (dzial_qstring == "Grupa montazowa"){
        query_ps->addBindValue(3);
    } else {
        query_ps->addBindValue(0);
    }

    query_ps->exec();


    this->close();
}
