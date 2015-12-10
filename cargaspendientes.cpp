#include "cargaspendientes.h"
#include "ui_cargaspendientes.h"
#include <QSqlRelationalDelegate>
#include <QSqlRelationalTableModel>
#include <QSqlQuery>
#include <QPrinter>
#include <QTextDocument>
#include <QPrintDialog>
#include "contratosventapendientes.h"
#include <QDebug>

CargasPendientes::CargasPendientes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CargasPendientes)
{
    ui->setupUi(this);
    loadPendientes();
    ui->pendientesOrigen->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->pendientesOrigen->setSelectionBehavior(QTableView::SelectRows);
    ui->pendientesOrigen->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->pedientesDestino->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->pedientesDestino->setSelectionBehavior(QTableView::SelectRows);
    ui->pedientesDestino->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setWindowTitle("Cargas Pendientes");

}

CargasPendientes::~CargasPendientes()
{
    delete ui;
}

void CargasPendientes::loadPendientes()
{

    // PENDIENTES COMPRAS
    QSqlTableModel *model1 = new QSqlTableModel(0, QSqlDatabase::database());

    model1->setTable("cargasPendientes");
    model1->setHeaderData(1, Qt::Horizontal, QObject::tr("Cliente"));
    model1->setHeaderData(2, Qt::Horizontal, QObject::tr("Grano"));
    model1->setHeaderData(4, Qt::Horizontal, QObject::tr("Kilos"));

    model1->select();


    ui->pendientesOrigen->setModel(model1);
    ui->pendientesOrigen->setItemDelegate(new QSqlRelationalDelegate(ui->pendientesOrigen));
    ui->pendientesOrigen->setSortingEnabled(true);

    ui->pendientesOrigen->setVisible(false);
    ui->pendientesOrigen->resizeColumnsToContents();
    ui->pendientesOrigen->setVisible(true);

    ui->pendientesOrigen->setColumnHidden(0,true);
    ui->pendientesOrigen->setColumnHidden(3,true);


    // PENDIENTES VENTAS
    QSqlTableModel *modelVentas = new QSqlTableModel(0, QSqlDatabase::database());

    modelVentas->setTable("pendientesVenta");
    modelVentas->setHeaderData(0, Qt::Horizontal, QObject::tr("Comprador"));
    modelVentas->setHeaderData(1, Qt::Horizontal, QObject::tr("Grano"));
    modelVentas->setHeaderData(2, Qt::Horizontal, QObject::tr("Kilos"));

    modelVentas->select();


    ui->pedientesDestino->setModel(modelVentas);
    ui->pedientesDestino->setItemDelegate(new QSqlRelationalDelegate(ui->pedientesDestino));
    ui->pedientesDestino->setSortingEnabled(true);

    ui->pedientesDestino->setVisible(false);
    ui->pedientesDestino->resizeColumnsToContents();
    ui->pedientesDestino->setVisible(true);

}


void CargasPendientes::Imprimir()
{
    QString html;
    html = "<html><body> <h3>Cargas pendientes ORIGEN</h3><table border='1' cellpadding='0' cellspacing='0'>";
    for(int column = 0; column < ui->pendientesOrigen->model()->columnCount(); column++)
    {
        if (!ui->pendientesOrigen->isColumnHidden(column))
        {
            html  += "<th>" + ui->pendientesOrigen->model()->headerData(column, Qt::Horizontal).toString() + "</th>";
        }
    }
    for(int row = 0; row < ui->pendientesOrigen->model()->rowCount(); row++)
    {
      html += "</tr><tr>";
      for(int column = 0; column < ui->pendientesOrigen->model()->columnCount(); column++)
      {
         if (!ui->pendientesOrigen->isColumnHidden(column))
         {
            QString data = ui->pendientesOrigen->model()->data(ui->pendientesOrigen->model()->index(row, column), Qt::DisplayRole).toString();
            html += "<td>" + data + "</td>";
         }
      }
      html += "</tr>";
    }

    html += "</table> <h3>Cargas pendientes ORIGEN</h3><table border='1' cellpadding='0' cellspacing='0'>";

    for(int column = 0; column < ui->pedientesDestino->model()->columnCount(); column++)
    {
        if (!ui->pedientesDestino->isColumnHidden(column))
        {
            html  += "<th>" + ui->pedientesDestino->model()->headerData(column, Qt::Horizontal).toString() + "</th>";
        }
    }
    for(int row = 0; row < ui->pedientesDestino->model()->rowCount(); row++)
    {
      html += "</tr><tr>";
      for(int column = 0; column < ui->pedientesDestino->model()->columnCount(); column++)
      {
         if (!ui->pedientesDestino->isColumnHidden(column))
         {
            QString data = ui->pedientesDestino->model()->data(ui->pedientesDestino->model()->index(row, column), Qt::DisplayRole).toString();
            html += "<td>" + data + "</td>";
         }
      }
      html += "</tr>";
    }

    html += "</table></body></html>";
    qDebug() << html;
    QPrinter printer;
    QPrintDialog *dialog = new QPrintDialog(&printer);
    if(dialog->exec() == QDialog::Accepted)
    {
      QTextDocument document;
      document.setHtml(html);
      document.print(&printer);
    }
}

void CargasPendientes::on_pushButton_clicked()
{
    Imprimir();
}

void CargasPendientes::on_contratosVenta_clicked()
{
    contratosVentaPendientes *Cpendientes = new contratosVentaPendientes();
    Cpendientes->exec();
}
