#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void showOfrecidos();
    void showCompras();
    void showVentas();
    void nuevoCliente();
    void listadoClientes();
    void nuevaCarga();
    void listadoCargas();
    void listadoCargasDeposito();
    void listadoCargasPendientes();



private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
