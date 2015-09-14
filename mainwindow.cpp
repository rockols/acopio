#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "agregarcliente.h"
#include "listadoclientes.h"
#include "compras.h"
#include <QMessageBox>

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
