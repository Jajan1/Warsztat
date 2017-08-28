#include "zamow_m.h"
#include "ui_zamow_m.h"
#include <qtsql>

zamow_m::zamow_m(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::zamow_m)
{
    ui->setupUi(this);

    QSqlQueryModel *model_zm = new QSqlQueryModel;
    QSqlQuery *queryzm = new QSqlQuery;
    queryzm->exec("select opis from maszyna");
    model_zm->setQuery(*queryzm);
    ui->maszyna->setModel(model_zm);

    srand(time(0));
    id = rand() % ((10000 + 1) - 100) + 100;
    id1 = rand() % ((100 + 1) - 11) + 11;
}

zamow_m::~zamow_m()
{
    delete ui;
}

void zamow_m::on_zamow_clicked()
{
    QSqlQuery *query_z = new QSqlQuery;
    QSqlQuery *query_zm = new QSqlQuery;

    query_z->prepare("INSERT INTO `zamowienie` (`nr_zamowienia`, `status`) VALUES (?, 'Oczekujace')");
    query_z->addBindValue(id);
    query_z->exec();

    if (maszyna_qstring == "Imadlo"){
        query_zm->prepare("INSERT INTO `zamowienie_has_maszyna` (`ID`,`Zamowienie_nr_zamowienia`, `Maszyna_IDmaszyna`) VALUES (?, ?, '1')");
    } else {
        query_zm->prepare("INSERT INTO `zamowienie_has_maszyna` (`ID`,`Zamowienie_nr_zamowienia`, `Maszyna_IDmaszyna`) VALUES (?, ?, '0')");
    }
    query_zm->addBindValue(id1);
    query_zm->addBindValue(id);
    query_zm->exec();


    this->close();
}

void zamow_m::on_cofnij_clicked()
{
    this->close();
}

void zamow_m::on_maszyna_activated(const QString &arg1)
{
    maszyna_qstring = arg1;
}
