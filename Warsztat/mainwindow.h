#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    bool uszkodzone = false;
    bool sprawne = false;
    bool zgubione = false;
    bool zniszczone = false;

public slots:
    void update();
private slots:
    void on_czyUszkodzone_clicked(bool checked);
    void on_czySprawne_clicked(bool checked);
    void on_czyZgubione_clicked(bool checked);
    void on_czyZniszczone_clicked(bool checked);
    void on_zamow_maszyny_clicked();
    void on_zamow_skrzynki_clicked();
    void on_zamow_elektronarzedzie_clicked();
    void on_zamow_akcesorium_clicked();
    void on_zamow_narzedzie_clicked();
    void on_dzialy_list_doubleClicked(const QModelIndex &index);
    void on_wyloguj_clicked();
    void on_dodaj_skrzynke_clicked();
    void on_pokaz_zawartosc_clicked();
    void on_dodaj_maszyne_clicked();
    void on_dodaj_elektronarzedzie_clicked();
    void on_dodaj_akcesorium_clicked();
    void on_dodaj_akcesorium_doskrzynki_clicked();
    void on_dodaj_narzedzie_clicked();
    void on_dodaj_narzedzie_doskrzynki_clicked();
    void on_przenies_dozrealizowanych_clicked();
    void on_wyszukaj_opis_clicked();
    void on_wyszukaj_producent_clicked();
    void on_pokaz_zawartosc_2_clicked();
    void on_przenies_skrzynke_clicked();
    void on_dodaj_pracownika_clicked();
    void on_zwolnij_pracownika_clicked();
    void on_dodaj_zgloszenie_clicked();
};

#endif // MAINWINDOW_H
