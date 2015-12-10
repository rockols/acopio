#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "agregarcliente.h"
#include "listadoclientes.h"
#include "compras.h"
#include "agregarcarga.h"
#include "filtrocargas.h"
#include "cargasdeposito.h"
#include "cargaspendientes.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Acopio Riback");
    this->setWindowState(Qt::WindowMaximized);


    connect (ui->actionOfrecidos , SIGNAL (triggered()), this, SLOT(showOfrecidos()));
    connect (ui->actionCompras , SIGNAL (triggered()), this, SLOT(showCompras()));
    connect (ui->actionVentas , SIGNAL (triggered()), this, SLOT(showVentas()));
    connect (ui->actionNuevoCliente , SIGNAL (triggered()), this, SLOT(nuevoCliente()));
    connect (ui->actionListado_clientes , SIGNAL (triggered()), this, SLOT(listadoClientes()));
    connect (ui->actionNuega_Carga , SIGNAL (triggered()), this, SLOT(nuevaCarga()));
    connect (ui->actionListado_Cargas , SIGNAL (triggered()), this, SLOT(listadoCargas()));
    connect (ui->actionEn_deposito , SIGNAL (triggered()), this, SLOT(listadoCargasDeposito()));
    connect (ui->actionPendientes , SIGNAL (triggered()), this, SLOT(listadoCargasPendientes()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showOfrecidos()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::showCompras()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::showVentas()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::nuevoCliente()
{
    AgregarCliente *nuevocliente = new AgregarCliente(0);
    nuevocliente->exec();

}

void MainWindow::listadoClientes()
{
    ListadoClientes *clientes = new ListadoClientes(0);
    clientes->show();

}

void MainWindow::nuevaCarga()
{
    AgregarCarga *carga = new AgregarCarga();
    carga->exec();
}

void MainWindow::listadoCargas(){

    filtroCargas *cargas = new filtroCargas();
    cargas->exec();

}

void MainWindow::listadoCargasDeposito()
{
    CargasDeposito *cargas = new CargasDeposito();
    cargas->exec();
}

void MainWindow::listadoCargasPendientes()
{
    CargasPendientes *cargas = new CargasPendientes();
    cargas->exec();
}
