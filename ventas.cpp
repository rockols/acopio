#include "ventas.h"
#include "ui_ventas.h"
#include "agregarventa.h"
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QSqlQuery>
#include <QMessageBox>
#include <QLocale>
#include <QDebug>
Ventas::Ventas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ventas)
{

    ui->setupUi(this);
    QLocale::setDefault(QLocale(QLocale::Spanish, QLocale::Argentina));

    ui->ventasList->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->ventasList->setSelectionBehavior(QTableView::SelectRows);
    ui->ventasList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    showVentas();
}

Ventas::~Ventas()
{
    delete ui;
}

void Ventas::showVentas(){

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


    model->select();

    ui->ventasList->setModel(model);
    ui->ventasList->setItemDelegate(new QSqlRelationalDelegate(ui->ventasList));
    ui->ventasList->setSortingEnabled(true);


    // OCULTAR COLUMNAS VENTAS
    ui->ventasList->setColumnHidden(0,true);


    for (int c = 0; c < ui->ventasList->horizontalHeader()->count(); ++c)
    {
        ui->ventasList->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::ResizeToContents);
    }
    //ui->ofrecidosList->horizontalHeader()->setSectionResizeMode(
    //ui->ofrecidosList->horizontalHeader()->count() - 2, QHeaderView::Stretch);
}

void Ventas::agregarVenta(){

    AgregarVenta *agregarventa = new AgregarVenta();
    int ret = agregarventa->exec();
    if(ret)
        showVentas();
}

void Ventas::eliminarVenta(){
    disableButtons();

    QModelIndex index = ui->ventasList->currentIndex();
    int row = index.row();
    int id = index.sibling(row, 0).data().toInt();

    QMessageBox msgBox;
    msgBox.setText("¿Está seguro que desea eliminar la venta seleccionada?");
    msgBox.setWindowTitle("Eliminar venta");
    msgBox.addButton("Aceptar", QMessageBox::YesRole);
    msgBox.addButton("Cancelar", QMessageBox::NoRole);
    msgBox.setIcon(QMessageBox::Question);

    int ret = msgBox.exec();
    QSqlQuery query;
    switch(ret){
        case 0:
            query.prepare("DELETE FROM ventas WHERE _id = :id");
            query.bindValue(":id",id);
            query.exec();
            showVentas();
            break;
        default:
            break;
    }
}

void Ventas::modificarVenta(){

    enableButtons();

    //PASAR ID DEL OFRECIDO
    int rowIndex =  ui->ventasList->currentIndex().row();
    int id = ui->ventasList->currentIndex().sibling(rowIndex,0).data().toInt();

    AgregarVenta *agregarventa = new AgregarVenta(0);
    if(agregarventa->fillVentasFields(id)){
        showVentas();
        disableButtons();
    }
}

void Ventas::vincularVenta(){
    disableButtons();
}

void Ventas::disableButtons(){
    ui->eliminarVenta->setEnabled(false);
    ui->modificarVenta->setEnabled(false);
    ui->vincularVenta->setEnabled(false);
}

void Ventas::enableButtons(){
    ui->eliminarVenta->setEnabled(true);
    ui->modificarVenta->setEnabled(true);
    ui->vincularVenta->setEnabled(true);
}


void Ventas::on_nuevaVenta_clicked()
{
    Ventas::agregarVenta();
}

void Ventas::on_ventasList_clicked()
{
    Ventas::enableButtons();
}

void Ventas::on_eliminarVenta_clicked()
{
    eliminarVenta();
}

void Ventas::on_modificarVenta_clicked()
{
    modificarVenta();
}

void Ventas::on_vincularVenta_clicked()
{
    vincularVenta();
}
