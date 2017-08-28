#include "zgloszenie.h"
#include "ui_zgloszenie.h"
#include <QtSql>

zgloszenie::zgloszenie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::zgloszenie)
{
    ui->setupUi(this);

    QSqlQueryModel *model_zg = new QSqlQueryModel;
    QSqlQuery *queryzg = new QSqlQuery;
    queryzg->exec(""
                  "select n.opis from narzedzie as n "
                  "union "
                  "select a.opis "
                  "from akcesorium as a "
                  "union "
                  "select e.opis "
                  "from elektronarzedzie as e "
                  "union "
                  "select m.opis "
                  "from maszyna as m");
    model_zg->setQuery(*queryzg);
    ui->przedmiot->setModel(model_zg);
}

zgloszenie::~zgloszenie()
{
    delete ui;
}

void zgloszenie::on_przedmiot_activated(const QString &arg1)
{
    przedmiot_qstring = arg1;
}

void zgloszenie::on_zglos_clicked()
{
    QSqlQuery *query_zglos = new QSqlQuery;

    if (przedmiot_qstring=="Zasilacz"){
        query_zglos->prepare("UPDATE akcesorium SET Stan_ID=? WHERE IDakcesoria=1");
    } else if (przedmiot_qstring=="Mlotek"){
        query_zglos->prepare("UPDATE narzedzie_trwale SET Stan_ID=? WHERE Narzedzie_id=1");
    } else if (przedmiot_qstring=="Klucz nasadowy"){
        query_zglos->prepare("UPDATE narzedzie_trwale SET Stan_ID=? WHERE Narzedzie_id=3");
    } else if (przedmiot_qstring=="Srubokret"){
        query_zglos->prepare("UPDATE narzedzie_trwale SET Stan_ID=? WHERE Narzedzie_id=4");
    } else if (przedmiot_qstring=="Imadlo"){
        query_zglos->prepare("UPDATE maszyna SET Stan_ID=? WHERE IDmaszyna=1");
    } else if (przedmiot_qstring=="Wiertarka"){
        query_zglos->prepare("UPDATE elektronarzedzie SET Stan_ID=? WHERE IDelektronarzedzie=1");
    }

    if (uszk){
        query_zglos->addBindValue(3);
    } else if (zgub){
        query_zglos->addBindValue(4);
    } else if (znisz){
        query_zglos->addBindValue(5);
    }

    query_zglos->exec();

    this->close();
}

void zgloszenie::on_uszkodzone_toggled(bool checked)
{
    uszk = checked;
}

void zgloszenie::on_zgubione_toggled(bool checked)
{
    zgub = checked;
}

void zgloszenie::on_zniszczone_toggled(bool checked)
{
    znisz = checked;
}
