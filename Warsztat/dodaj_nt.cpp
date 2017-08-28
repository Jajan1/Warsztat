#include "dodaj_nt.h"
#include "ui_dodaj_nt.h"
#include <QtSql>

dodaj_nt::dodaj_nt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dodaj_nt)
{
    ui->setupUi(this);

    QSqlQueryModel *model_dnt = new QSqlQueryModel;
    QSqlQuery *querydnt = new QSqlQuery;
    querydnt->exec("select producent from producent");
    model_dnt->setQuery(*querydnt);
    ui->producent->setModel(model_dnt);

    srand(time(0));
    id = rand() % ((10000 + 1) - 100) + 100;
}

dodaj_nt::~dodaj_nt()
{
    delete ui;
}

void dodaj_nt::on_producent_activated(const QString &arg1)
{
    producent_qstring = arg1;
}

void dodaj_nt::on_dodaj_clicked()
{
    QSqlQuery *query_dodaj_n = new QSqlQuery;
    QSqlQuery *query_dodaj_nt = new QSqlQuery;

    if (producent_qstring=="Castorama"){
        query_dodaj_n->prepare("INSERT INTO `narzedzie` (`id`, `opis`, `Producent_ID`, `Typ_ID`) VALUES (?, ?, '1', ?)");
        query_dodaj_nt->prepare("INSERT INTO `narzedzie_trwale` ( `Narzedzie_id`, `data_zakupu`, `Stan_ID`, `Nr_seryjny`, `Skrzynka_IDskrzynka`) VALUES (?, CURDATE(), '2', ?, NULL)");
    } else if (producent_qstring=="Leroy Merlin"){
        query_dodaj_n->prepare("INSERT INTO `narzedzie` (`id`, `opis`, `Producent_ID`, `Typ_ID`) VALUES (?, ?, '2', ?)");
        query_dodaj_nt->prepare("INSERT INTO `narzedzie_trwale` ( `Narzedzie_id`, `data_zakupu`, `Stan_ID`, `Nr_seryjny`, `Skrzynka_IDskrzynka`) VALUES (?, CURDATE(), '2', ?, NULL)");
    }
    query_dodaj_n->addBindValue(id);
    query_dodaj_n->addBindValue(ui->nazwa->text());
    query_dodaj_n->addBindValue(typ);
    query_dodaj_n->exec();
    query_dodaj_nt->addBindValue(id);
    query_dodaj_nt->addBindValue(ui->nr_seryjny->text());
    query_dodaj_nt->exec();

    this->close();
}

void dodaj_nt::on_Wierla_toggled(bool checked)
{
    if (checked){
        typ = 2;
    }
}

void dodaj_nt::on_Frezy_toggled(bool checked)
{
    if (checked){
        typ = 3;
    }
}

void dodaj_nt::on_Tarcze_toggled(bool checked)
{
    if (checked){
        typ = 4;
    }
}

void dodaj_nt::on_Klucze_toggled(bool checked)
{
    if (checked){
        typ = 5;
    }
}

void dodaj_nt::on_Mlotki_toggled(bool checked)
{
    if (checked){
        typ = 6;
    }
}

void dodaj_nt::on_Pilniki_toggled(bool checked)
{
    if (checked){
        typ = 7;
    }
}

void dodaj_nt::on_Inne_toggled(bool checked)
{
    if (checked){
        typ = 1;
    }
}
