#include "zamow_n.h"
#include "ui_zamow_n.h"
#include <qtsql>

zamow_n::zamow_n(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::zamow_n)
{
    ui->setupUi(this);

    QSqlQueryModel *model_zn = new QSqlQueryModel;
    QSqlQuery *queryzn = new QSqlQuery;
    queryzn->exec("select n.opis from narzedzie as n, narzedzie_trwale as nt where nt.Narzedzie_id=n.id");
    model_zn->setQuery(*queryzn);
    ui->narzedzie->setModel(model_zn);

    srand(time(0));
    id = rand() % ((10000 + 1) - 100) + 100;
    id1 = rand() % ((100 + 1) - 11) + 11;
}

zamow_n::~zamow_n()
{
    delete ui;
}

void zamow_n::on_zamow_clicked()
{
    QSqlQuery *query_z = new QSqlQuery;
    QSqlQuery *query_zn = new QSqlQuery;

    query_z->prepare("INSERT INTO `zamowienie` (`nr_zamowienia`, `status`) VALUES (?, 'Oczekujace')");
    query_z->addBindValue(id);
    query_z->exec();

    if (narzedzie_qstring == "Mlotek"){
        query_zn->prepare("INSERT INTO `zamowienie_has_narzedzie_trwale` (`ID`,`Zamowienie_nr_zamowienia`, `Narzedzie_trwale_Narzedzie_id`) VALUES (?, ?, '1')");
    } else if (narzedzie_qstring == "Klucz nasadowy"){
        query_zn->prepare("INSERT INTO `zamowienie_has_narzedzie_trwale` (`ID`,`Zamowienie_nr_zamowienia`, `Narzedzie_trwale_Narzedzie_id`) VALUES (?, ?, '3')");
    } else if (narzedzie_qstring == "Srubokret"){
        query_zn->prepare("INSERT INTO `zamowienie_has_narzedzie_trwale` (`ID`,`Zamowienie_nr_zamowienia`, `Narzedzie_trwale_Narzedzie_id`) VALUES (?, ?, '4')");
    }else {
        query_zn->prepare("INSERT INTO `zamowienie_has_narzedzie_trwale` (`ID`,`Zamowienie_nr_zamowienia`, `Narzedzie_trwale_Narzedzie_id`) VALUES (?, ?, '0')");
    }
    query_zn->addBindValue(id1);
    query_zn->addBindValue(id);
    query_zn->exec();


    this->close();
}

void zamow_n::on_cofnij_clicked()
{
    this->close();
}

void zamow_n::on_narzedzie_activated(const QString &arg1)
{
    narzedzie_qstring = arg1;
}
