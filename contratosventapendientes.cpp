#include "contratosventapendientes.h"
#include "ui_contratosventapendientes.h"
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QDebug>
#include <QSqlQuery>

contratosVentaPendientes::contratosVentaPendientes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::contratosVentaPendientes)
{
    ui->setupUi(this);

    loadData();
    ui->contratosVenta->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->contratosVenta->setSelectionBehavior(QTableView::SelectRows);
    ui->contratosVenta->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setWindowTitle("Contratos pendientes de carga");
    this->setWindowState(Qt::WindowMaximized);
}

contratosVentaPendientes::~contratosVentaPendientes()
{
    delete ui;
}

void contratosVentaPendientes::loadData()
{

    QSqlRelationalTableModel *model = new QSqlRelationalTableModel(0, QSqlDatabase::database());

    model->setTable("ventas");
    model->setRelation(7, QSqlRelation("comprador", "cuit", "nombre"));
    model->setRelation(11, QSqlRelation("cereales", "id", "cereal"));

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Tipo"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Fecha Venta"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Fecha Cobro"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Fecha desde"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Fecha hasta"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Num Contrato"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Comprador"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Kilos"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Kilos Calzados"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Kilos Cumplidos"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("Grano"));
    model->setHeaderData(12, Qt::Horizontal, QObject::tr("Precio (por ton.)"));
    model->setHeaderData(13, Qt::Horizontal, QObject::tr("Moneda"));
    model->setHeaderData(14, Qt::Horizontal, QObject::tr("Observaciones"));

    model->setFilter("kilos - kiloscumplidos > 0");
    model->select();

    ui->contratosVenta->setModel(model);
    ui->contratosVenta->setItemDelegate(new QSqlRelationalDelegate(ui->contratosVenta));
    ui->contratosVenta->setSortingEnabled(true);


    // OCULTAR COLUMNAS VENTAS
    ui->contratosVenta->setColumnHidden(0,true);


    for (int c = 0; c < ui->contratosVenta->horizontalHeader()->count(); ++c)
    {
        ui->contratosVenta->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::ResizeToContents);
    }
}
