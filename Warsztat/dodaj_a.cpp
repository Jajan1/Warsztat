#include "dodaj_a.h"
#include "ui_dodaj_a.h"
#include <QtSql>

dodaj_a::dodaj_a(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dodaj_a)
{
    ui->setupUi(this);

    QSqlQueryModel *model_da = new QSqlQueryModel;
    QSqlQuery *queryda = new QSqlQuery;
    queryda->exec("select producent from producent");
    model_da->setQuery(*queryda);
    ui->producent->setModel(model_da);

    QSqlQueryModel *model_dae = new QSqlQueryModel;
    QSqlQuery *querydae = new QSqlQuery;
    querydae->exec("select opis from elektronarzedzie");
    model_dae->setQuery(*querydae);
    ui->do_elek->setModel(model_dae);
}

dodaj_a::~dodaj_a()
{
    delete ui;
}

void dodaj_a::on_producent_activated(const QString &arg1)
{
    producent_qstring = arg1;
}

void dodaj_a::on_dodaj_clicked()
{
    QSqlQuery *query_dodaj = new QSqlQuery;

    if (producent_qstring=="Castorama"){
        query_dodaj->prepare("INSERT INTO `akcesorium` (`IDakcesoria`, `Data_dodania`, `opis`, `Producent_ID`, `Stan_ID`, `Elektronarzedzie_IDelektronarzedzie`, `Skrzynka_IDskrzynka`) VALUES ('', CURDATE(), ?, '1', '2', ?, NULL)");
    } else if (producent_qstring=="Leroy Merlin"){
        query_dodaj->prepare("INSERT INTO `akcesorium` (`IDakcesoria`, `Data_dodania`, `opis`, `Producent_ID`, `Stan_ID`, `Elektronarzedzie_IDelektronarzedzie`, `Skrzynka_IDskrzynka`) VALUES ('', CURDATE(), ?, '2', '2', ?, NULL)");
    }
    query_dodaj->addBindValue(ui->nazwa->text());
    if (do_elek_qstring=="Wiertarka"){
        query_dodaj->addBindValue(1);
    } else{
        query_dodaj->addBindValue(0);
    }
    query_dodaj->exec();

    this->close();
}

void dodaj_a::on_do_elek_activated(const QString &arg1)
{
    do_elek_qstring = arg1;
}
