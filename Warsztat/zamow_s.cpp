#include "zamow_s.h"
#include "ui_zamow_s.h"
#include <qtsql>

zamow_s::zamow_s(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::zamow_s)
{
    ui->setupUi(this);

    QSqlQueryModel *model_zs = new QSqlQueryModel;
    QSqlQuery *queryzs = new QSqlQuery;
    queryzs->exec("select opis from skrzynka");
    model_zs->setQuery(*queryzs);
    ui->skrzynka->setModel(model_zs);

    srand(time(0));
    id = rand() % ((10000 + 1) - 100) + 100;
    id1 = rand() % ((100 + 1) - 11) + 11;
}

zamow_s::~zamow_s()
{
    delete ui;
}

void zamow_s::on_zamow_clicked()
{
    QSqlQuery *query_z = new QSqlQuery;
    QSqlQuery *query_zs = new QSqlQuery;

    query_z->prepare("INSERT INTO `zamowienie` (`nr_zamowienia`, `status`) VALUES (?, 'Oczekujace')");
    query_z->addBindValue(id);
    query_z->exec();

    if (skrzynka_qstring == "Przybornik narzedziowy"){
        query_zs->prepare("INSERT INTO `skrzynka_zamowienie` (`ID`,`Skrzynka_IDskrzynka`, `Zamowienie_nr_zamowienia`) VALUES (?, '1', ?)");
    } else if (skrzynka_qstring == "Zestaw malego mechanika"){
        query_zs->prepare("INSERT INTO `skrzynka_zamowienie` (`ID`,`Skrzynka_IDskrzynka`, `Zamowienie_nr_zamowienia`) VALUES (?, '2', ?)");
    }else {
        query_zs->prepare("INSERT INTO `skrzynka_zamowienie` (`ID`,`Skrzynka_IDskrzynka`, `Zamowienie_nr_zamowienia`) VALUES (?, '0', ?)");
    }
    query_zs->addBindValue(id1);
    query_zs->addBindValue(id);
    query_zs->exec();


    this->close();
}

void zamow_s::on_cofnij_clicked()
{
    this->close();
}

void zamow_s::on_skrzynka_activated(const QString &arg1)
{
    skrzynka_qstring = arg1;
}
