#include "zawartosc_sk.h"
#include "ui_zawartosc_sk.h"
#include <QtSql>

zawartosc_sk::zawartosc_sk(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::zawartosc_sk)
{
    ui->setupUi(this);

    QSqlQueryModel *model_zaw = new QSqlQueryModel;
    QSqlQuery *queryzaw = new QSqlQuery;
    queryzaw->exec("select opis from skrzynka");
    model_zaw->setQuery(*queryzaw);
    ui->comboBox->setModel(model_zaw);
}

zawartosc_sk::~zawartosc_sk()
{
    delete ui;
}

void zawartosc_sk::on_comboBox_activated(const QString &arg1)
{
    QSqlQueryModel *model_tab = new QSqlQueryModel;
    QSqlQuery *query_tab = new QSqlQuery;
    query_tab->prepare(""
                 "select n.opis as Opis, p.producent as Producent, s_meksp.ilosc as Ilosc "
                 "from skrzynka as s, (((skrzynka_meksp as s_meksp left join narzedzie as n on n.id=s_meksp.Material_eksploatacyjny_Narzedzie_id)left join material_eksploatacyjny as meksp on meksp.Narzedzie_id=n.id)left join producent as p on p.ID=n.Producent_ID) "
                 "where s.IDskrzynka=s_meksp.Skrzynka_IDskrzynka and s.opis=? "
                 "union "
                 "select a.opis as Opis, p.producent as Producent, '1' "
                 "from (skrzynka as s left join akcesorium as a on s.IDskrzynka=a.Skrzynka_IDskrzynka)left join producent as p on p.ID=a.Producent_ID "
                 "where s.opis=? "
                 "union "
                 "select n.opis as Opis, p.producent as Producent, '1' "
                 "from ((skrzynka as s left join narzedzie_trwale as nt on nt.Skrzynka_IDskrzynka=s.IDskrzynka)left join narzedzie as n on n.id=nt.Narzedzie_id)left join producent as p on p.ID=n.Producent_ID "
                 "where s.opis=? "
                 "union "
                 "select e.opis as Opis, p.producent as Producent, '1' "
                 "from (skrzynka as s left join elektronarzedzie as e on s.IDskrzynka=e.Skrzynka_IDskrzynka)left join producent as p on p.ID=e.Producent_ID "
                 "where s.opis=?");
    query_tab->addBindValue(arg1);
    query_tab->addBindValue(arg1);
    query_tab->addBindValue(arg1);
    query_tab->addBindValue(arg1);
    query_tab->exec();
    model_tab->setQuery(*query_tab);
    ui->zawartosc->setModel(model_tab);
}
