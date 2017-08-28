#include "dodaj_do_sk.h"
#include "ui_dodaj_do_sk.h"
#include <QtSql>

//     DODAWANIE AKCESORIUM DO SKRZYNKI

dodaj_do_sk::dodaj_do_sk(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dodaj_do_sk)
{
    ui->setupUi(this);

    QSqlQueryModel *model_sk = new QSqlQueryModel;
    QSqlQuery *querysk = new QSqlQuery;
    querysk->exec("select opis from skrzynka");
    model_sk->setQuery(*querysk);
    ui->skrzynka->setModel(model_sk);

    QSqlQueryModel *model_ak = new QSqlQueryModel;
    QSqlQuery *queryak = new QSqlQuery;
    queryak->exec("select opis from akcesorium");
    model_ak->setQuery(*queryak);
    ui->akcesorium->setModel(model_ak);
}

dodaj_do_sk::~dodaj_do_sk()
{
    delete ui;
}

void dodaj_do_sk::on_skrzynka_activated(const QString &arg1)
{
    skrzynka_qstring = arg1;
}

void dodaj_do_sk::on_akcesorium_activated(const QString &arg1)
{
    akcesorium_qstring = arg1;
}

void dodaj_do_sk::on_dodaj_clicked()
{
    QSqlQuery *query_dodaj = new QSqlQuery;

    if (skrzynka_qstring=="Przybornik narzedziowy"){
        query_dodaj->prepare("UPDATE `akcesorium` SET Skrzynka_IDskrzynka=1 WHERE IDakcesoria=?");
    } else if (skrzynka_qstring=="Zestaw malego mechanika"){
        query_dodaj->prepare("UPDATE `akcesorium` SET Skrzynka_IDskrzynka=2 WHERE IDakcesoria=?");
    } else {
        query_dodaj->prepare("UPDATE `akcesorium` SET Skrzynka_IDskrzynka=0 WHERE IDakcesoria=?");
    }
    if (akcesorium_qstring=="Wiertla"){
        query_dodaj->addBindValue(1);
    } else {
        query_dodaj->addBindValue(0);
    }
    query_dodaj->exec();

    this->close();
}
