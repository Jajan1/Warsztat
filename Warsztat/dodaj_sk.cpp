#include "dodaj_sk.h"
#include "ui_dodaj_sk.h"
#include <QtSql>

dodaj_sk::dodaj_sk(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dodaj_sk)
{
    ui->setupUi(this);

    QSqlQueryModel *model_dsk = new QSqlQueryModel;
    QSqlQuery *querydsk = new QSqlQuery;
    querydsk->exec("select producent from producent");
    model_dsk->setQuery(*querydsk);
    ui->producent->setModel(model_dsk);
}

dodaj_sk::~dodaj_sk()
{
    delete ui;
}

void dodaj_sk::on_producent_activated(const QString &arg1)
{
    producent_qstring = arg1;
}

void dodaj_sk::on_dodaj_clicked()
{
    QSqlQuery *query_dodaj = new QSqlQuery;

    if (producent_qstring=="Castorama"){
        query_dodaj->prepare("INSERT INTO `skrzynka` (`IDskrzynka`, `data_utworzenia`, `opis`, `Producent_ID`, `Stan_ID`) VALUES ('', CURDATE(), ?, '1', '2')");
    } else if (producent_qstring=="Leroy Merlin"){
        query_dodaj->prepare("INSERT INTO `skrzynka` (`IDskrzynka`, `data_utworzenia`, `opis`, `Producent_ID`, `Stan_ID`) VALUES ('', CURDATE(), ?, '2', '2')");
    }
    query_dodaj->addBindValue(ui->nazwa->text());
    query_dodaj->exec();

    this->close();
}
