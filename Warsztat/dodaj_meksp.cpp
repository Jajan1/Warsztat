#include "dodaj_meksp.h"
#include "ui_dodaj_meksp.h"
#include <QtSql>

dodaj_meksp::dodaj_meksp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dodaj_meksp)
{
    ui->setupUi(this);

    QSqlQueryModel *model_dmeksp = new QSqlQueryModel;
    QSqlQuery *querydmeksp = new QSqlQuery;
    querydmeksp->exec("select producent from producent");
    model_dmeksp->setQuery(*querydmeksp);
    ui->producent->setModel(model_dmeksp);

    srand(time(0));
    id = rand() % ((10000 + 1) - 100) + 100;
}

dodaj_meksp::~dodaj_meksp()
{
    delete ui;
}


void dodaj_meksp::on_producent_activated(const QString &arg1)
{
    producent_qstring = arg1;
}

void dodaj_meksp::on_dodaj_clicked()
{
    QSqlQuery *query_dodaj_n = new QSqlQuery;
    QSqlQuery *query_dodaj_meksp = new QSqlQuery;

    if (producent_qstring=="Castorama"){
        query_dodaj_n->prepare("INSERT INTO `narzedzie` (`id`, `opis`, `Producent_ID`, `Typ_ID`) VALUES (?, ?, '1', ?)");
        query_dodaj_meksp->prepare("INSERT INTO `material_eksploatacyjny` ( `Narzedzie_id`, `liczba_szt`) VALUES (?, ?)");
    } else if (producent_qstring=="Leroy Merlin"){
        query_dodaj_n->prepare("INSERT INTO `narzedzie` (`id`, `opis`, `Producent_ID`, `Typ_ID`) VALUES (?, ?, '2', ?)");
        query_dodaj_meksp->prepare("INSERT INTO `material_eksploatacyjny` ( `Narzedzie_id`, `liczba_szt`) VALUES (?, ?)");
    }
    query_dodaj_n->addBindValue(id);
    query_dodaj_n->addBindValue(ui->nazwa->text());
    query_dodaj_n->addBindValue(typ);
    query_dodaj_n->exec();
    query_dodaj_meksp->addBindValue(id);
    query_dodaj_meksp->addBindValue(ui->ilosc->text());
    query_dodaj_meksp->exec();

    this->close();
}

void dodaj_meksp::on_Wierla_toggled(bool checked)
{
    if (checked){
        typ = 2;
    }
}

void dodaj_meksp::on_Frezy_toggled(bool checked)
{
    if (checked){
        typ = 3;
    }
}

void dodaj_meksp::on_Tarcze_toggled(bool checked)
{
    if (checked){
        typ = 4;
    }
}

void dodaj_meksp::on_Klucze_toggled(bool checked)
{
    if (checked){
        typ = 5;
    }
}

void dodaj_meksp::on_Mlotki_toggled(bool checked)
{
    if (checked){
        typ = 6;
    }
}

void dodaj_meksp::on_Pilniki_toggled(bool checked)
{
    if (checked){
        typ = 7;
    }
}

void dodaj_meksp::on_Inne_toggled(bool checked)
{
    if (checked){
        typ = 1;
    }
}
