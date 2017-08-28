#include "zamow_a.h"
#include "ui_zamow_a.h"
#include <qtsql>

zamow_a::zamow_a(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::zamow_a)
{
    ui->setupUi(this);

    QSqlQueryModel *model_za = new QSqlQueryModel;
    QSqlQuery *queryza = new QSqlQuery;
    queryza->exec("select opis from akcesorium");
    model_za->setQuery(*queryza);
    ui->akcesorium->setModel(model_za);

    srand(time(0));
    id = rand() % ((10000 + 1) - 100) + 100;
    id1 = rand() % ((100 + 1) - 11) + 11;
}

zamow_a::~zamow_a()
{
    delete ui;
}

void zamow_a::on_zamow_clicked()
{
    QSqlQuery *query_z = new QSqlQuery;
    QSqlQuery *query_za = new QSqlQuery;

    query_z->prepare("INSERT INTO `zamowienie` (`nr_zamowienia`, `status`) VALUES (?, 'Oczekujace')");
    query_z->addBindValue(id);
    query_z->exec();

    if (akcesorium_qstring == "Zasilacz"){
        query_za->prepare("INSERT INTO `akcesorium_zamowienie` (`ID`, `Akcesorium_IDakcesoria`, `Zamowienie_nr_zamowienia`) VALUES (?, '1', ?)");
    } else {
        query_za->prepare("INSERT INTO `akcesorium_zamowienie` (`ID`, `Akcesorium_IDakcesoria`, `Zamowienie_nr_zamowienia`) VALUES (?, '0', ?)");
    }
    query_za->addBindValue(id1);
    query_za->addBindValue(id);
    query_za->exec();


    this->close();
}

void zamow_a::on_cofnij_clicked()
{
    this->close();
}

void zamow_a::on_akcesorium_activated(const QString &arg1)
{
    akcesorium_qstring = arg1;
}

