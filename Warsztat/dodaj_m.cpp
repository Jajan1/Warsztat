#include "dodaj_m.h"
#include "ui_dodaj_m.h"
#include <QtSql>

dodaj_m::dodaj_m(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dodaj_m)
{
    ui->setupUi(this);

    QSqlQueryModel *model_dm = new QSqlQueryModel;
    QSqlQuery *querydm = new QSqlQuery;
    querydm->exec("select producent from producent");
    model_dm->setQuery(*querydm);
    ui->producent->setModel(model_dm);

    QSqlQueryModel *model_dmp = new QSqlQueryModel;
    QSqlQuery *querydmp = new QSqlQuery;
    querydmp->exec("select nazwa from dzial");
    model_dmp->setQuery(*querydmp);
    ui->dzial->setModel(model_dmp);
}

dodaj_m::~dodaj_m()
{
    delete ui;
}


void dodaj_m::on_producent_activated(const QString &arg1)
{
    producent_qstring = arg1;
}

void dodaj_m::on_dodaj_clicked()
{
    QSqlQuery *query_dodaj = new QSqlQuery;

    if (producent_qstring=="Castorama"){
        query_dodaj->prepare("INSERT INTO `maszyna` (`IDmaszyna`, `data_zakupu`, `opis`, `Producent_ID`, Dzial_IDdzial, `Stan_ID`) VALUES ('', CURDATE(), ?, '1', ?, '2')");
    } else if (producent_qstring=="Leroy Merlin"){
        query_dodaj->prepare("INSERT INTO `maszyna` (`IDmaszyna`, `data_zakupu`, `opis`, `Producent_ID`, Dzial_IDdzial, `Stan_ID`) VALUES ('', CURDATE(), ?, '2', ?, '2')");
    }
    query_dodaj->addBindValue(ui->nazwa->text());
    if (dzial_qstring=="Magazyn"){
        query_dodaj->addBindValue(1);
    } else if (dzial_qstring=="Hala produkcyjna"){
        query_dodaj->addBindValue(2);
    } else if (dzial_qstring=="Grupa montazowa"){
        query_dodaj->addBindValue(3);
    }
    query_dodaj->exec();

    this->close();
}

void dodaj_m::on_dzial_activated(const QString &arg1)
{
    dzial_qstring = arg1;
}
