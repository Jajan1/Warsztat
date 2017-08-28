#include "dodaj_nt_do_sk.h"
#include "ui_dodaj_nt_do_sk.h"
#include <QtSql>

//      DODAWANIE NARZĘDZIA TRWAŁEGO DO SKRZYNKI

dodaj_nt_do_sk::dodaj_nt_do_sk(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dodaj_nt_do_sk)
{
    ui->setupUi(this);

    QSqlQueryModel *model_sk = new QSqlQueryModel;
    QSqlQuery *querysk = new QSqlQuery;
    querysk->exec("select opis from skrzynka");
    model_sk->setQuery(*querysk);
    ui->skrzynka->setModel(model_sk);

    QSqlQueryModel *model_nt = new QSqlQueryModel;
    QSqlQuery *querynt = new QSqlQuery;
    querynt->exec("select n.opis from narzedzie_trwale as nt left join narzedzie as n on n.id=nt.Narzedzie_id");
    model_nt->setQuery(*querynt);
    ui->narzedzie_trwale->setModel(model_nt);
}

dodaj_nt_do_sk::~dodaj_nt_do_sk()
{
    delete ui;
}


void dodaj_nt_do_sk::on_skrzynka_activated(const QString &arg1)
{
    skrzynka_qstring = arg1;
}

void dodaj_nt_do_sk::on_narzedzie_trwale_activated(const QString &arg1)
{
    nt_qstring = arg1;
}

void dodaj_nt_do_sk::on_dodaj_clicked()
{
    QSqlQuery *query_dodaj = new QSqlQuery;

    if (skrzynka_qstring=="Przybornik narzedziowy"){
        query_dodaj->prepare("UPDATE `narzedzie_trwale` SET Skrzynka_IDskrzynka=1 WHERE Narzedzie_ID=?");
    } else if (skrzynka_qstring=="Zestaw malego mechanika"){
        query_dodaj->prepare("UPDATE `narzedzie_trwale` SET Skrzynka_IDskrzynka=2 WHERE Narzedzie_ID=?");
    } else {
        query_dodaj->prepare("UPDATE `narzedzie_trwale` SET Skrzynka_IDskrzynka=0 WHERE Narzedzie_ID=?");
    }
    if (nt_qstring=="Mlotek"){
        query_dodaj->addBindValue(1);
    } else if (nt_qstring=="Klucz nasadowy"){
        query_dodaj->addBindValue(3);
    } else if (nt_qstring=="Srubokret"){
        query_dodaj->addBindValue(4);
    } else {
        query_dodaj->addBindValue(0);
    }
    query_dodaj->exec();

    this->close();
}
