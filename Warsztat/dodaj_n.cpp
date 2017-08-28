#include "dodaj_n.h"
#include "ui_dodaj_n.h"
#include <QtSql>

#include "dodaj_nt.h"
#include "dodaj_meksp.h"

dodaj_n::dodaj_n(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dodaj_n)
{
    ui->setupUi(this);
}

dodaj_n::~dodaj_n()
{
    delete ui;
}


void dodaj_n::on_narzedzie_trwale_toggled(bool checked)
{
    nt_selected = checked;
}

void dodaj_n::on_meksp_toggled(bool checked)
{
    meksp_selected = checked;
}

void dodaj_n::on_dodaj_clicked()
{
    if (nt_selected != meksp_selected){
        // otwórz odpowiednie okna
        if(nt_selected){
            dodaj_nt dodaj_nt_window;
            dodaj_nt_window.setModal(true);
            dodaj_nt_window.exec();
        }else {
            dodaj_meksp dodaj_meksp_window;
            dodaj_meksp_window.setModal(true);
            dodaj_meksp_window.exec();
        }

        this->close();
    }
}
