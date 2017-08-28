#include "dodaj_p.h"
#include "ui_dodaj_p.h"
#include <QtSql>

dodaj_p::dodaj_p(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dodaj_p)
{
    ui->setupUi(this);
}

dodaj_p::~dodaj_p()
{
    delete ui;
}

void dodaj_p::on_dodaj_clicked()
{
    QSqlQuery *query_dodaj = new QSqlQuery;

    query_dodaj->prepare("INSERT INTO `pracownik` (`Id`, `PESEL`, `imie`, `nazwisko`) VALUES ('', ?, ?, ?)");
    query_dodaj->addBindValue(ui->pesel->text());
    query_dodaj->addBindValue(ui->imie->text());
    query_dodaj->addBindValue(ui->nazwisko->text());
    query_dodaj->exec();

    this->close();
}
