#include "dodaj_e.h"
#include "ui_dodaj_e.h"
#include <QtSql>

dodaj_e::dodaj_e(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dodaj_e)
{
    ui->setupUi(this);

    QSqlQueryModel *model_de = new QSqlQueryModel;
    QSqlQuery *queryde = new QSqlQuery;
    queryde->exec("select producent from producent");
    model_de->setQuery(*queryde);
    ui->producent->setModel(model_de);

    QSqlQueryModel *model_des = new QSqlQueryModel;
    QSqlQuery *querydes = new QSqlQuery;
    querydes->exec("select opis from skrzynka");
    model_des->setQuery(*querydes);
    ui->skrzynka->setModel(model_des);
}

dodaj_e::~dodaj_e()
{
    delete ui;
}


void dodaj_e::on_producent_activated(const QString &arg1)
{
    producent_qstring = arg1;
}

void dodaj_e::on_dodaj_clicked()
{
    QSqlQuery *query_dodaj = new QSqlQuery;

    if (producent_qstring=="Castorama"){
        query_dodaj->prepare("INSERT INTO `elektronarzedzie` (`IDelektronarzedzie`, `data_zakupu`, `opis`, `Producent_ID`, `Stan_ID`, `Skrzynka_IDskrzynka`) VALUES ('', CURDATE(), ?, '1', '2', ?)");
    } else if (producent_qstring=="Leroy Merlin"){
        query_dodaj->prepare("INSERT INTO `elektronarzedzie` (`IDelektronarzedzie`, `data_zakupu`, `opis`, `Producent_ID`, `Stan_ID`, `Skrzynka_IDskrzynka`) VALUES ('', CURDATE(), ?, '2', '2', ?)");
    }
    query_dodaj->addBindValue(ui->nazwa->text());
    if (skrzynka_qstring=="Przybornik narzedziowy"){
        query_dodaj->addBindValue(1);
    } else if (skrzynka_qstring=="Zestaw malego mechanika"){
        query_dodaj->addBindValue(2);
    } else{
        query_dodaj->addBindValue(0);
    }
    query_dodaj->exec();

    this->close();
}

void dodaj_e::on_skrzynka_activated(const QString &arg1)
{
    skrzynka_qstring = arg1;
}
