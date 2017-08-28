#include "zamow_e.h"
#include "ui_zamow_e.h"
#include <qtsql>

zamow_e::zamow_e(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::zamow_e)
{
    ui->setupUi(this);

    QSqlQueryModel *model_ze = new QSqlQueryModel;
    QSqlQuery *queryze = new QSqlQuery;
    queryze->exec("select opis from elektronarzedzie");
    model_ze->setQuery(*queryze);
    ui->elektronarzedzie->setModel(model_ze);

    srand(time(0));
    id = rand() % ((10000 + 1) - 100) + 100;
    id1 = rand() % ((100 + 1) - 11) + 11;
}

zamow_e::~zamow_e()
{
    delete ui;
}

void zamow_e::on_zamow_clicked()
{
    QSqlQuery *query_z = new QSqlQuery;
    QSqlQuery *query_ze = new QSqlQuery;

    query_z->prepare("INSERT INTO `zamowienie` (`nr_zamowienia`, `status`) VALUES (?, 'Oczekujace')");
    query_z->addBindValue(id);
    query_z->exec();

    if (elektronarzedzie_qstring == "Wiertarka"){
        query_ze->prepare("INSERT INTO `zamowienie_elektronarzedzie` (`ID`, `Zamowienie_nr_zamowienia`, `Elektronarzedzie_IDelektronarzedzie`) VALUES (?, ?, '1')");
    } else {
        query_ze->prepare("INSERT INTO `zamowienie_elektronarzedzie` (`ID`, `Zamowienie_nr_zamowienia`, `Elektronarzedzie_IDelektronarzedzie`) VALUES (?, ?, '0')");
    }
    query_ze->addBindValue(id1);
    query_ze->addBindValue(id);
    query_ze->exec();


    this->close();
}

void zamow_e::on_cofnij_clicked()
{
    this->close();
}

void zamow_e::on_elektronarzedzie_activated(const QString &arg1)
{
    elektronarzedzie_qstring = arg1;
}

