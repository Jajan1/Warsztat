#include "zrealizuj.h"
#include "ui_zrealizuj.h"
#include <QtSql>

zrealizuj::zrealizuj(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::zrealizuj)
{
    ui->setupUi(this);

    QSqlQueryModel *model_rea = new QSqlQueryModel;
    QSqlQuery *queryrea = new QSqlQuery;
    queryrea->exec("select e.opis from (zamowienie_elektronarzedzie as z_e left join elektronarzedzie as e on e.IDelektronarzedzie=z_e.Elektronarzedzie_IDelektronarzedzie) "
                   "union "
                   "select m.opis from (zamowienie_has_maszyna as z_m left join maszyna as m on m.IDmaszyna=z_m.Maszyna_IDmaszyna) "
                   "union "
                   "select n.opis from ((zamowienie_has_narzedzie_trwale as z_nt left join narzedzie_trwale as nt on nt.Narzedzie_id=z_nt.Narzedzie_trwale_Narzedzie_id)left join narzedzie as n on nt.Narzedzie_id=n.id) "
                   "union "
                   "select nn.opis from ((zamowienie_meksp as z_meksp left join material_eksploatacyjny as meksp on meksp.Narzedzie_id=z_meksp.Material_eksploatacyjny_Narzedzie_id)left join narzedzie as nn on meksp.Narzedzie_id=nn.id)");
    model_rea->setQuery(*queryrea);
    ui->zamowienia->setModel(model_rea);
}

/*
                 "select CONCAT(COALESCE(e.opis, ''), COALESCE(m.opis, ''), COALESCE(n.opis, ''), COALESCE(nn.opis, '')) as Opis, CONCAT(COALESCE(ep.producent, ''), COALESCE(mp.producent, ''), COALESCE(ntp.producent, ''), COALESCE(mep.producent, '')) as Producent, z_meksp.ilosc as Ilosc "
                 "from zamowienie as z, ((zamowienie_elektronarzedzie as z_e left join elektronarzedzie as e on e.IDelektronarzedzie=z_e.Elektronarzedzie_IDelektronarzedzie)left join producent as ep on e.Producent_ID=ep.ID), "
                 "((zamowienie_has_maszyna as z_m left join maszyna as m on m.IDmaszyna=z_m.Maszyna_IDmaszyna)left join producent as mp on m.Producent_ID=mp.ID), "
                 "(((zamowienie_has_narzedzie_trwale as z_nt left join narzedzie_trwale as nt on nt.Narzedzie_id=z_nt.Narzedzie_trwale_Narzedzie_id)left join narzedzie as n on nt.Narzedzie_id=n.id)left join producent as ntp on n.Producent_ID=ntp.ID), "
                 "(((zamowienie_meksp as z_meksp left join material_eksploatacyjny as meksp on meksp.Narzedzie_id=z_meksp.Material_eksploatacyjny_Narzedzie_id)left join narzedzie as nn on meksp.Narzedzie_id=nn.id)left join producent as mep on nn.Producent_ID=mep.ID) "
                 "where z.nr_zamowienia=z_e.Zamowienie_nr_zamowienia and z.nr_zamowienia=z_m.Zamowienie_nr_zamowienia and z.nr_zamowienia=z_nt.Zamowienie_nr_zamowienia and z.nr_zamowienia=z_meksp.Zamowienie_nr_zamowienia and z.status='Oczekujace'");

*/

zrealizuj::~zrealizuj()
{
    delete ui;
}

void zrealizuj::on_zamowienia_activated(const QString &arg1)
{
    zamowienie_qstring = arg1;
}


void zrealizuj::on_zrealizuj_2_clicked()
{
    QSqlQuery *query_dodaj = new QSqlQuery;

    if (zamowienie_qstring == "Wiertarka"){
        query_dodaj->prepare("UPDATE `zamowienie` SET status='Zrealizowane' WHERE nr_zamowienia=1");
    } else if (zamowienie_qstring == "Imadlo"){
        query_dodaj->prepare("UPDATE `zamowienie` SET status='Zrealizowane' WHERE nr_zamowienia=2");
    } else if (zamowienie_qstring == "Mlotek"){
        query_dodaj->prepare("UPDATE `zamowienie` SET status='Zrealizowane' WHERE nr_zamowienia=3");
    } else if (zamowienie_qstring == "Klucz nasadowy"){
        query_dodaj->prepare("UPDATE `zamowienie` SET status='Zrealizowane' WHERE nr_zamowienia=4");
    } else if (zamowienie_qstring == "Gwozdzie"){
        query_dodaj->prepare("UPDATE `zamowienie` SET status='Zrealizowane' WHERE nr_zamowienia=5");
    } else {
        query_dodaj->prepare("UPDATE `zamowienie` SET status='Zrealizowane' WHERE nr_zamowienia=0");
    }

    query_dodaj->exec();

    this->close();
}
