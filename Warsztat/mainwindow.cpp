#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>

#include "zamow_m.h"
#include "zamow_s.h"
#include "zamow_e.h"
#include "zamow_a.h"
#include "zamow_n.h"
#include "dodaj_a.h"
#include "dodaj_e.h"
#include "dodaj_m.h"
#include "dodaj_n.h"
#include "dodaj_p.h"
#include "dodaj_sk.h"
#include "dodaj_do_sk.h"
#include "dodaj_nt_do_sk.h"
#include "zawartosc_sk.h"
#include "zrealizuj.h"
#include "przenies_sk.h"
#include "zwolnij.h"
#include "zgloszenie.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("mydb");

    if(db.open()){
        qDebug() << "Connected to database";

        timer = new QTimer;
        connect(timer,SIGNAL(timeout()),this,SLOT(update()));
        timer->start(100);

    } else {
        qDebug() << "Connection error" << db.lastError().text();
    }


    QSqlQueryModel *model_list = new QSqlQueryModel;
    QSqlQuery *query_list = new QSqlQuery;
    query_list->exec("select nazwa from dzial");
    model_list->setQuery(*query_list);
    ui->dzialy_list->setModel(model_list);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update()
{
    //  ZAKŁADKA PRZEDMIOTY

    QSqlQuery *query = new QSqlQuery;
    QSqlQuery *query1 = new QSqlQuery;
    QSqlQuery *query2 = new QSqlQuery;
    QSqlQuery *query3 = new QSqlQuery;
    QSqlQuery *query4 = new QSqlQuery;

    //zapytania SQL w zależności od checkboxów
    if (sprawne && !uszkodzone && !zniszczone && !zgubione){
        query->prepare("select m.opis as Nazwa, p.producent as Producent, s.stan as Stan, m.data_zakupu as Zakupione from maszyna as m, producent as p, stan as s where m.Producent_ID=p.ID and m.Stan_ID=s.ID and s.stan='Sprawne'");
        query1->prepare("select  skrzynka.opis as Nazwa, p.producent as Producent, s.stan as Stan, skrzynka.data_utworzenia as Utworzone from skrzynka, stan as s, producent as p where skrzynka.Stan_ID=s.ID and skrzynka.Producent_ID=p.ID and s.stan='Sprawne'");
        query2->prepare("select e.opis as Nazwa, p.producent as Producent, s.stan as Stan, e.data_zakupu as Zakupione from elektronarzedzie as e, producent as p, stan as s where e.Producent_ID=p.ID and e.Stan_ID=s.ID and s.stan='Sprawne'");
        query3->prepare("select a.opis as Nazwa, p.producent as Producent, s.stan as Stan, a.Data_dodania as Dodane from akcesorium as a, producent as p, stan as s where a.Producent_ID=p.ID and a.Stan_ID=s.ID and s.stan='Sprawne'");
        query4->prepare("select n.opis as Nazwa, t.nazwa as Typ, p.producent as Producent, s.stan as Stan, me.liczba_szt as Ilosc, nt.Nr_seryjny as Nr_seryjny, nt.data_zakupu as Dodane from (((((narzedzie as n left join typ as t on n.Typ_ID=t.ID)left join producent as p on n.Producent_ID=p.ID)left join narzedzie_trwale as nt on n.id=nt.Narzedzie_ID)left join stan as s on nt.Stan_ID=s.ID)left join material_eksploatacyjny as me on n.id=me.Narzedzie_ID) where s.stan='Sprawne'");
    } else if (!sprawne && uszkodzone && !zniszczone && !zgubione){
        query->prepare("select m.opis as Nazwa, p.producent as Producent, s.stan as Stan, m.data_zakupu as Zakupione from maszyna as m, producent as p, stan as s where m.Producent_ID=p.ID and m.Stan_ID=s.ID and s.stan='Uszkodzone'");
        query1->prepare("select  skrzynka.opis as Nazwa, p.producent as Producent, s.stan as Stan, skrzynka.data_utworzenia as Utworzone from skrzynka, stan as s, producent as p where skrzynka.Stan_ID=s.ID and skrzynka.Producent_ID=p.ID and s.stan='Uszkodzone'");
        query2->prepare("select e.opis as Nazwa, p.producent as Producent, s.stan as Stan, e.data_zakupu as Zakupione from elektronarzedzie as e, producent as p, stan as s where e.Producent_ID=p.ID and e.Stan_ID=s.ID and s.stan='Uszkodzone'");
        query3->prepare("select a.opis as Nazwa, p.producent as Producent, s.stan as Stan, a.Data_dodania as Dodane from akcesorium as a, producent as p, stan as s where a.Producent_ID=p.ID and a.Stan_ID=s.ID and s.stan='Uszkodzone'");
        query4->prepare("select n.opis as Nazwa, t.nazwa as Typ, p.producent as Producent, s.stan as Stan, me.liczba_szt as Ilosc, nt.Nr_seryjny as Nr_seryjny, nt.data_zakupu as Dodane from (((((narzedzie as n left join typ as t on n.Typ_ID=t.ID)left join producent as p on n.Producent_ID=p.ID)left join narzedzie_trwale as nt on n.id=nt.Narzedzie_ID)left join stan as s on nt.Stan_ID=s.ID)left join material_eksploatacyjny as me on n.id=me.Narzedzie_ID) where s.stan='Uszkodzone'");
    } else if (!sprawne && !uszkodzone && zniszczone && !zgubione){
        query->prepare("select m.opis as Nazwa, p.producent as Producent, s.stan as Stan, m.data_zakupu as Zakupione from maszyna as m, producent as p, stan as s where m.Producent_ID=p.ID and m.Stan_ID=s.ID and s.stan='Zniszczone'");
        query1->prepare("select  skrzynka.opis as Nazwa, p.producent as Producent, s.stan as Stan, skrzynka.data_utworzenia as Utworzone from skrzynka, stan as s, producent as p where skrzynka.Stan_ID=s.ID and skrzynka.Producent_ID=p.ID and s.stan='Zniszczone'");
        query2->prepare("select e.opis as Nazwa, p.producent as Producent, s.stan as Stan, e.data_zakupu as Zakupione from elektronarzedzie as e, producent as p, stan as s where e.Producent_ID=p.ID and e.Stan_ID=s.ID and s.stan='Zniszczone'");
        query3->prepare("select a.opis as Nazwa, p.producent as Producent, s.stan as Stan, a.Data_dodania as Dodane from akcesorium as a, producent as p, stan as s where a.Producent_ID=p.ID and a.Stan_ID=s.ID and s.stan='Zniszczone'");
        query4->prepare("select n.opis as Nazwa, t.nazwa as Typ, p.producent as Producent, s.stan as Stan, me.liczba_szt as Ilosc, nt.Nr_seryjny as Nr_seryjny, nt.data_zakupu as Dodane from (((((narzedzie as n left join typ as t on n.Typ_ID=t.ID)left join producent as p on n.Producent_ID=p.ID)left join narzedzie_trwale as nt on n.id=nt.Narzedzie_ID)left join stan as s on nt.Stan_ID=s.ID)left join material_eksploatacyjny as me on n.id=me.Narzedzie_ID) where s.stan='Zniszczone'");
    } else if (!sprawne && !uszkodzone && !zniszczone && zgubione){
        query->prepare("select m.opis as Nazwa, p.producent as Producent, s.stan as Stan, m.data_zakupu as Zakupione from maszyna as m, producent as p, stan as s where m.Producent_ID=p.ID and m.Stan_ID=s.ID and s.stan='Zgubione'");
        query1->prepare("select  skrzynka.opis as Nazwa, p.producent as Producent, s.stan as Stan, skrzynka.data_utworzenia as Utworzone from skrzynka, stan as s, producent as p where skrzynka.Stan_ID=s.ID and skrzynka.Producent_ID=p.ID and s.stan='Zgubione'");
        query2->prepare("select e.opis as Nazwa, p.producent as Producent, s.stan as Stan, e.data_zakupu as Zakupione from elektronarzedzie as e, producent as p, stan as s where e.Producent_ID=p.ID and e.Stan_ID=s.ID and s.stan='Zgubione'");
        query3->prepare("select a.opis as Nazwa, p.producent as Producent, s.stan as Stan, a.Data_dodania as Dodane from akcesorium as a, producent as p, stan as s where a.Producent_ID=p.ID and a.Stan_ID=s.ID and s.stan='Zgubione'");
        query4->prepare("select n.opis as Nazwa, t.nazwa as Typ, p.producent as Producent, s.stan as Stan, me.liczba_szt as Ilosc, nt.Nr_seryjny as Nr_seryjny, nt.data_zakupu as Dodane from (((((narzedzie as n left join typ as t on n.Typ_ID=t.ID)left join producent as p on n.Producent_ID=p.ID)left join narzedzie_trwale as nt on n.id=nt.Narzedzie_ID)left join stan as s on nt.Stan_ID=s.ID)left join material_eksploatacyjny as me on n.id=me.Narzedzie_ID) where s.stan='Zgubione'");
    } else
    {
        query->prepare("select m.opis as Nazwa, p.producent as Producent, s.stan as Stan, m.data_zakupu as Zakupione from maszyna as m, producent as p, stan as s where m.Producent_ID=p.ID and m.Stan_ID=s.ID");
        query1->prepare("select skrzynka.opis as Nazwa, p.producent as Producent, s.stan as Stan, skrzynka.data_utworzenia as Utworzone from skrzynka, stan as s, producent as p where skrzynka.Stan_ID=s.ID and skrzynka.Producent_ID=p.ID");
        query2->prepare("select e.opis as Nazwa, p.producent as Producent, s.stan as Stan, e.data_zakupu as Zakupione from elektronarzedzie as e, producent as p, stan as s where e.Producent_ID=p.ID and e.Stan_ID=s.ID");
        query3->prepare("select a.opis as Nazwa, p.producent as Producent, s.stan as Stan, a.Data_dodania as Dodane from akcesorium as a, producent as p, stan as s where a.Producent_ID=p.ID and a.Stan_ID=s.ID");
        query4->prepare("select n.opis as Nazwa, t.nazwa as Typ, p.producent as Producent, s.stan as Stan, me.liczba_szt as Ilosc, nt.Nr_seryjny as Nr_seryjny, nt.data_zakupu as Dodane from (((((narzedzie as n left join typ as t on n.Typ_ID=t.ID)left join producent as p on n.Producent_ID=p.ID)left join narzedzie_trwale as nt on n.id=nt.Narzedzie_ID)left join stan as s on nt.Stan_ID=s.ID)left join material_eksploatacyjny as me on n.id=me.Narzedzie_ID)"); // where nt.data_zakupu between ':od' and '2018-01-01'
    }

    // uzupełnianie tabeli w zakładce maszyny
    QSqlQueryModel *model = new QSqlQueryModel;
    query->exec();
    model->setQuery(*query);
    ui->maszyny_table->setModel(model);

    // uzupełnianie tabeli w zakładce skrzynki
    QSqlQueryModel *model1 = new QSqlQueryModel;
    query1->exec();
    model1->setQuery(*query1);
    ui->skrzynki_table->setModel(model1);

    // uzupełnianie tabeli w zakładce elektronarzędzia
    QSqlQueryModel *model2 = new QSqlQueryModel;
    query2->exec();
    model2->setQuery(*query2);
    ui->elektronarzedzia_table->setModel(model2);

    // uzupełnianie tabeli w zakładce akcesoria
    QSqlQueryModel *model3 = new QSqlQueryModel;
    query3->exec();
    model3->setQuery(*query3);
    ui->akcesoria_table->setModel(model3);

    // uzupełnianie tabeli w zakładce narzędzia
    QSqlQueryModel *model4 = new QSqlQueryModel;
    query4->exec();
    model4->setQuery(*query4);
    ui->narzedzia_table->setModel(model4);

    //  ZAKŁADKA LISTA ZAKUPÓW

    QSqlQueryModel *model8 = new QSqlQueryModel;
    QSqlQuery *query8 = new QSqlQuery;
    query8->exec("select CONCAT(COALESCE(e.opis, ''), COALESCE(m.opis, ''), COALESCE(n.opis, ''), COALESCE(nn.opis, '')) as Opis, CONCAT(COALESCE(ep.producent, ''), COALESCE(mp.producent, ''), COALESCE(ntp.producent, ''), COALESCE(mep.producent, '')) as Producent, z_meksp.ilosc as Ilosc "
                 "from zamowienie as z, ((zamowienie_elektronarzedzie as z_e left join elektronarzedzie as e on e.IDelektronarzedzie=z_e.Elektronarzedzie_IDelektronarzedzie)left join producent as ep on e.Producent_ID=ep.ID), "
                 "((zamowienie_has_maszyna as z_m left join maszyna as m on m.IDmaszyna=z_m.Maszyna_IDmaszyna)left join producent as mp on m.Producent_ID=mp.ID), "
                 "(((zamowienie_has_narzedzie_trwale as z_nt left join narzedzie_trwale as nt on nt.Narzedzie_id=z_nt.Narzedzie_trwale_Narzedzie_id)left join narzedzie as n on nt.Narzedzie_id=n.id)left join producent as ntp on n.Producent_ID=ntp.ID), "
                 "(((zamowienie_meksp as z_meksp left join material_eksploatacyjny as meksp on meksp.Narzedzie_id=z_meksp.Material_eksploatacyjny_Narzedzie_id)left join narzedzie as nn on meksp.Narzedzie_id=nn.id)left join producent as mep on nn.Producent_ID=mep.ID) "
                 "where z.nr_zamowienia=z_e.Zamowienie_nr_zamowienia and z.nr_zamowienia=z_m.Zamowienie_nr_zamowienia and z.nr_zamowienia=z_nt.Zamowienie_nr_zamowienia and z.nr_zamowienia=z_meksp.Zamowienie_nr_zamowienia and z.status='Oczekujace'");
    model8->setQuery(*query8);
    ui->listazakupow_table->setModel(model8);

    //  ZAKŁADKA RAPORT 1

    QSqlQueryModel *model9 = new QSqlQueryModel;
    QSqlQuery *query9 = new QSqlQuery;
    query9->exec("select p.imie as Imie, p.nazwisko as Nazwisko, p.PESEL from pracownik as p, dzial_pracownik as d where d.Pracownik_Id=p.ID and d.Dzial_IDdzial=1");
    model9->setQuery(*query9);
    ui->raport1_table->setModel(model9);

    QSqlQuery *query10 = new QSqlQuery;
    query10->exec("select nazwa from dzial where IDdzial=1");
    QSqlQueryModel *model10 = new QSqlQueryModel;
    model10->setQuery(*query10);
    QString nazwadzialu = model10->data(model->index(0,0)).toString();
    ui->nazwa_dzialu_report1->setText(nazwadzialu);

    //  ZAKŁADKA RAPORT 2

    QSqlQueryModel *model11 = new QSqlQueryModel;
    QSqlQuery *query11 = new QSqlQuery;
    //query11->exec("");
    model11->setQuery(*query11);
    ui->raport2_table->setModel(model11);
}

void MainWindow::on_czyUszkodzone_clicked(bool checked)
{
    if (checked){
        uszkodzone = true;
    }else{
        uszkodzone = false;
    }
}

void MainWindow::on_czySprawne_clicked(bool checked)
{
    if (checked){
        sprawne = true;
    }else{
        sprawne = false;
    }
}

void MainWindow::on_czyZgubione_clicked(bool checked)
{
    if (checked){
        zgubione = true;
    }else{
        zgubione = false;
    }
}

void MainWindow::on_czyZniszczone_clicked(bool checked)
{
    if (checked){
        zniszczone = true;
    }else{
        zniszczone = false;
    }
}

void MainWindow::on_zamow_maszyny_clicked()
{
    zamow_m zamow_m_window;
    zamow_m_window.setModal(true);
    zamow_m_window.exec();
}

void MainWindow::on_zamow_skrzynki_clicked()
{
    zamow_s zamow_s_window;
    zamow_s_window.setModal(true);
    zamow_s_window.exec();
}

void MainWindow::on_zamow_elektronarzedzie_clicked()
{
    zamow_e zamow_e_window;
    zamow_e_window.setModal(true);
    zamow_e_window.exec();
}

void MainWindow::on_zamow_akcesorium_clicked()
{
    zamow_a zamow_a_window;
    zamow_a_window.setModal(true);
    zamow_a_window.exec();
}

void MainWindow::on_zamow_narzedzie_clicked()
{
    zamow_n zamow_n_window;
    zamow_n_window.setModal(true);
    zamow_n_window.exec();
}

void MainWindow::on_dzialy_list_doubleClicked(const QModelIndex &index)
{
    QSqlQueryModel *model5 = new QSqlQueryModel;
    QSqlQueryModel *model6 = new QSqlQueryModel;
    QSqlQueryModel *model7 = new QSqlQueryModel;

    QSqlQuery *query5 = new QSqlQuery;
    QSqlQuery *query6 = new QSqlQuery;
    QSqlQuery *query7 = new QSqlQuery;

    QVariant d = index.data();
    if (d.toString() == "Magazyn"){
        query5->exec("select p.imie as Imie, p.nazwisko as Nazwisko, p.PESEL, d.data_rozpoczecia as Pracuje_od from pracownik as p, dzial_pracownik as d where p.Id=d.Pracownik_ID and d.Dzial_IDdzial=1");

        query6->exec("select skrzynka.opis as Nazwa, p.producent as Producent, s.stan as Stan, skrzynka.data_utworzenia as Posiada_od from (skrzynka left join dzial_wypozycz as d on d.Skrzynka_IDskrzynka=skrzynka.IDskrzynka), stan as s, producent as p where skrzynka.Stan_ID=s.ID and skrzynka.Producent_ID=p.ID and d.Dzial_IDdzial=1");

        query7->exec("select m.opis as Nazwa, p.producent as Producent, s.stan as Stan, m.data_zakupu as Posiada_od from maszyna as m, producent as p, stan as s where m.Producent_ID=p.ID and m.Stan_ID=s.ID and m.Dzial_IDdzial=1");

    } else if (d.toString() == "Hala produkcyjna"){
        query5->exec("select p.imie as Imie, p.nazwisko as Nazwisko, p.PESEL, d.data_rozpoczecia as Pracuje_od from pracownik as p, dzial_pracownik as d where p.Id=d.Pracownik_ID and d.Dzial_IDdzial=2");

        query6->exec("select skrzynka.opis as Nazwa, p.producent as Producent, s.stan as Stan, skrzynka.data_utworzenia as Posiada_od from (skrzynka left join dzial_wypozycz as d on d.Skrzynka_IDskrzynka=skrzynka.IDskrzynka), stan as s, producent as p where skrzynka.Stan_ID=s.ID and skrzynka.Producent_ID=p.ID and d.Dzial_IDdzial=2");

        query7->exec("select m.opis as Nazwa, p.producent as Producent, s.stan as Stan, m.data_zakupu as Posiada_od from maszyna as m, producent as p, stan as s where m.Producent_ID=p.ID and m.Stan_ID=s.ID and m.Dzial_IDdzial=2");

    } else if (d.toString() == "Grupa montazowa"){
        query5->exec("select p.imie as Imie, p.nazwisko as Nazwisko, p.PESEL, d.data_rozpoczecia as Pracuje_od from pracownik as p, dzial_pracownik as d where p.Id=d.Pracownik_ID and d.Dzial_IDdzial=3");

        query6->exec("select skrzynka.opis as Nazwa, p.producent as Producent, s.stan as Stan, skrzynka.data_utworzenia as Posiada_od from (skrzynka left join dzial_wypozycz as d on d.Skrzynka_IDskrzynka=skrzynka.IDskrzynka), stan as s, producent as p where skrzynka.Stan_ID=s.ID and skrzynka.Producent_ID=p.ID and d.Dzial_IDdzial=3");

        query7->exec("select m.opis as Nazwa, p.producent as Producent, s.stan as Stan, m.data_zakupu as Posiada_od from maszyna as m, producent as p, stan as s where m.Producent_ID=p.ID and m.Stan_ID=s.ID and m.Dzial_IDdzial=3");

    }

    model5->setQuery(*query5);
    ui->tableView->setModel(model5);

    model6->setQuery(*query6);
    ui->tableView_2->setModel(model6);

    model7->setQuery(*query7);
    ui->tableView_3->setModel(model7);
}

void MainWindow::on_wyloguj_clicked()
{
    this->close();
}

void MainWindow::on_dodaj_skrzynke_clicked()
{
    dodaj_sk dodaj_sk_window;
    dodaj_sk_window.setModal(true);
    dodaj_sk_window.exec();
}

void MainWindow::on_pokaz_zawartosc_clicked()
{
    zawartosc_sk zawartosc_sk_window;
    zawartosc_sk_window.setModal(true);
    zawartosc_sk_window.exec();
}

void MainWindow::on_dodaj_maszyne_clicked()
{
    dodaj_m dodaj_m_window;
    dodaj_m_window.setModal(true);
    dodaj_m_window.exec();
}

void MainWindow::on_dodaj_elektronarzedzie_clicked()
{
    dodaj_e dodaj_e_window;
    dodaj_e_window.setModal(true);
    dodaj_e_window.exec();
}

void MainWindow::on_dodaj_akcesorium_clicked()
{
    dodaj_a dodaj_a_window;
    dodaj_a_window.setModal(true);
    dodaj_a_window.exec();
}

void MainWindow::on_dodaj_akcesorium_doskrzynki_clicked()
{
    dodaj_do_sk dodaj_do_sk_window;
    dodaj_do_sk_window.setModal(true);
    dodaj_do_sk_window.exec();
}

void MainWindow::on_dodaj_narzedzie_clicked()
{
    dodaj_n dodaj_n_window;
    dodaj_n_window.setModal(true);
    dodaj_n_window.exec();
}

void MainWindow::on_dodaj_narzedzie_doskrzynki_clicked()
{
    dodaj_nt_do_sk dodaj_nt_do_sk_window;
    dodaj_nt_do_sk_window.setModal(true);
    dodaj_nt_do_sk_window.exec();
}

void MainWindow::on_przenies_dozrealizowanych_clicked()
{
    zrealizuj zrealizuj_window;
    zrealizuj_window.setModal(true);
    zrealizuj_window.exec();
}

void MainWindow::on_wyszukaj_opis_clicked()
{
    if (ui->nazwa->text() != ""){
        timer->stop();

        //maszyny
        QSqlQueryModel *model_wysz_om = new QSqlQueryModel;
        QSqlQuery *query_wysz_om = new QSqlQuery;
        query_wysz_om->prepare("select m.opis as Nazwa, p.producent as Producent, s.stan as Stan, m.data_zakupu as Zakupione from maszyna as m, producent as p, stan as s where m.Producent_ID=p.ID and m.Stan_ID=s.ID and m.opis=?");
        query_wysz_om->addBindValue(ui->nazwa->text());
        query_wysz_om->exec();
        model_wysz_om->setQuery(*query_wysz_om);
        ui->maszyny_table->setModel(model_wysz_om);

        //skrzynki
        QSqlQueryModel *model_wysz_os = new QSqlQueryModel;
        QSqlQuery *query_wysz_os = new QSqlQuery;
        query_wysz_os->prepare("select skrzynka.opis as Nazwa, p.producent as Producent, s.stan as Stan, skrzynka.data_utworzenia as Utworzone from skrzynka, stan as s, producent as p where skrzynka.Stan_ID=s.ID and skrzynka.Producent_ID=p.ID and skrzynka.opis=?");
        query_wysz_os->addBindValue(ui->nazwa->text());
        query_wysz_os->exec();
        model_wysz_os->setQuery(*query_wysz_os);
        ui->skrzynki_table->setModel(model_wysz_os);

        //elektronarzedzia
        QSqlQueryModel *model_wysz_oe = new QSqlQueryModel;
        QSqlQuery *query_wysz_oe = new QSqlQuery;
        query_wysz_oe->prepare("select e.opis as Nazwa, p.producent as Producent, s.stan as Stan, e.data_zakupu as Zakupione from elektronarzedzie as e, producent as p, stan as s where e.Producent_ID=p.ID and e.Stan_ID=s.ID and e.opis=?");
        query_wysz_oe->addBindValue(ui->nazwa->text());
        query_wysz_oe->exec();
        model_wysz_oe->setQuery(*query_wysz_oe);
        ui->elektronarzedzia_table->setModel(model_wysz_oe);

        //akcesoria
        QSqlQueryModel *model_wysz_oa = new QSqlQueryModel;
        QSqlQuery *query_wysz_oa = new QSqlQuery;
        query_wysz_oa->prepare("select a.opis as Nazwa, p.producent as Producent, s.stan as Stan, a.Data_dodania as Dodane from akcesorium as a, producent as p, stan as s where a.Producent_ID=p.ID and a.Stan_ID=s.ID and a.opis=?");
        query_wysz_oa->addBindValue(ui->nazwa->text());
        query_wysz_oa->exec();
        model_wysz_oa->setQuery(*query_wysz_oa);
        ui->akcesoria_table->setModel(model_wysz_oa);

        //narzedzia
        QSqlQueryModel *model_wysz_on = new QSqlQueryModel;
        QSqlQuery *query_wysz_on = new QSqlQuery;
        query_wysz_on->prepare("select n.opis as Nazwa, t.nazwa as Typ, p.producent as Producent, s.stan as Stan, me.liczba_szt as Ilosc, nt.Nr_seryjny as Nr_seryjny, nt.data_zakupu as Dodane from (((((narzedzie as n left join typ as t on n.Typ_ID=t.ID)left join producent as p on n.Producent_ID=p.ID)left join narzedzie_trwale as nt on n.id=nt.Narzedzie_ID)left join stan as s on nt.Stan_ID=s.ID)left join material_eksploatacyjny as me on n.id=me.Narzedzie_ID) where n.opis=?");
        query_wysz_on->addBindValue(ui->nazwa->text());
        query_wysz_on->exec();
        model_wysz_on->setQuery(*query_wysz_on);
        ui->narzedzia_table->setModel(model_wysz_on);

    } else {
        timer->start(100);
    }
}

void MainWindow::on_wyszukaj_producent_clicked()
{
    if (ui->producent->text() != ""){
        timer->stop();

        //maszyny
        QSqlQueryModel *model_wysz_pm = new QSqlQueryModel;
        QSqlQuery *query_wysz_pm = new QSqlQuery;
        query_wysz_pm->prepare("select m.opis as Nazwa, p.producent as Producent, s.stan as Stan, m.data_zakupu as Zakupione from maszyna as m, producent as p, stan as s where m.Producent_ID=p.ID and m.Stan_ID=s.ID and p.producent=?");
        query_wysz_pm->addBindValue(ui->producent->text());
        query_wysz_pm->exec();
        model_wysz_pm->setQuery(*query_wysz_pm);
        ui->maszyny_table->setModel(model_wysz_pm);

        //skrzynki
        QSqlQueryModel *model_wysz_ps = new QSqlQueryModel;
        QSqlQuery *query_wysz_ps = new QSqlQuery;
        query_wysz_ps->prepare("select skrzynka.opis as Nazwa, p.producent as Producent, s.stan as Stan, skrzynka.data_utworzenia as Utworzone from skrzynka, stan as s, producent as p where skrzynka.Stan_ID=s.ID and skrzynka.Producent_ID=p.ID and p.producent=?");
        query_wysz_ps->addBindValue(ui->producent->text());
        query_wysz_ps->exec();
        model_wysz_ps->setQuery(*query_wysz_ps);
        ui->skrzynki_table->setModel(model_wysz_ps);

        //elektronarzedzia
        QSqlQueryModel *model_wysz_pe = new QSqlQueryModel;
        QSqlQuery *query_wysz_pe = new QSqlQuery;
        query_wysz_pe->prepare("select e.opis as Nazwa, p.producent as Producent, s.stan as Stan, e.data_zakupu as Zakupione from elektronarzedzie as e, producent as p, stan as s where e.Producent_ID=p.ID and e.Stan_ID=s.ID and p.producent=?");
        query_wysz_pe->addBindValue(ui->producent->text());
        query_wysz_pe->exec();
        model_wysz_pe->setQuery(*query_wysz_pe);
        ui->elektronarzedzia_table->setModel(model_wysz_pe);

        //akcesoria
        QSqlQueryModel *model_wysz_pa = new QSqlQueryModel;
        QSqlQuery *query_wysz_pa = new QSqlQuery;
        query_wysz_pa->prepare("select a.opis as Nazwa, p.producent as Producent, s.stan as Stan, a.Data_dodania as Dodane from akcesorium as a, producent as p, stan as s where a.Producent_ID=p.ID and a.Stan_ID=s.ID and p.producent=?");
        query_wysz_pa->addBindValue(ui->producent->text());
        query_wysz_pa->exec();
        model_wysz_pa->setQuery(*query_wysz_pa);
        ui->akcesoria_table->setModel(model_wysz_pa);

        //narzedzia
        QSqlQueryModel *model_wysz_pn = new QSqlQueryModel;
        QSqlQuery *query_wysz_pn = new QSqlQuery;
        query_wysz_pn->prepare("select n.opis as Nazwa, t.nazwa as Typ, p.producent as Producent, s.stan as Stan, me.liczba_szt as Ilosc, nt.Nr_seryjny as Nr_seryjny, nt.data_zakupu as Dodane from (((((narzedzie as n left join typ as t on n.Typ_ID=t.ID)left join producent as p on n.Producent_ID=p.ID)left join narzedzie_trwale as nt on n.id=nt.Narzedzie_ID)left join stan as s on nt.Stan_ID=s.ID)left join material_eksploatacyjny as me on n.id=me.Narzedzie_ID) where p.producent=?");
        query_wysz_pn->addBindValue(ui->producent->text());
        query_wysz_pn->exec();
        model_wysz_pn->setQuery(*query_wysz_pn);
        ui->narzedzia_table->setModel(model_wysz_pn);

    } else {
        timer->start(100);
    }
}

void MainWindow::on_pokaz_zawartosc_2_clicked()
{
    zawartosc_sk zawartosc_sk1_window;
    zawartosc_sk1_window.setModal(true);
    zawartosc_sk1_window.exec();
}

void MainWindow::on_przenies_skrzynke_clicked()
{
    przenies_sk przenies_sk_window;
    przenies_sk_window.setModal(true);
    przenies_sk_window.exec();
}

void MainWindow::on_dodaj_pracownika_clicked()
{
    dodaj_p dodaj_p_window;
    dodaj_p_window.setModal(true);
    dodaj_p_window.exec();
}

void MainWindow::on_zwolnij_pracownika_clicked()
{
    zwolnij zwolnij_window;
    zwolnij_window.setModal(true);
    zwolnij_window.exec();
}

void MainWindow::on_dodaj_zgloszenie_clicked()
{
    zgloszenie zgloszenie_window;
    zgloszenie_window.setModal(true);
    zgloszenie_window.exec();
}
