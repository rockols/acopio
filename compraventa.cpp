#include "compraventa.h"
#include "ui_compraventa.h"
#include "detallecompraventa.h"
#include "agregarventa.h"
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>

CompraVenta::CompraVenta(int id_compra, QString grano, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CompraVenta)
{
    ui->setupUi(this);

    ui->ventasList->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->ventasList->setSelectionBehavior(QTableView::SelectRows);
    ui->ventasList->setEditTriggers(QAbstractItemView::NoEditTriggers);

    idCompra = id_compra;

    showVentas(grano);

}

CompraVenta::~CompraVenta()
{
    delete ui;
}

void CompraVenta::showVentas(QString grano){

    QSqlRelationalTableModel *model = new QSqlRelationalTableModel(0, QSqlDatabase::database());

    QSqlQueryModel cereal;
    cereal.setQuery("SELECT id FROM cereales WHERE cereal='"+grano+"'");
    QString tipoCereal = cereal.data(cereal.index(0,0)).toString();

    model->setTable("ventas");
    // CAMBIAR TABLA A COMPRADOR PARA QUE QUEDE DIFERENCIADO COMPRADOR DE CLIENTE
    model->setRelation(7, QSqlRelation("comprador", "cuit", "nombre"));
    model->setRelation(11, QSqlRelation("cereales", "id", "cereal"));
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->setFilter("kilos > kiloscalzados");
    QString filtroGrano = "tipocereal = " + tipoCereal;

    model->setFilter(filtroGrano);
    model->select();


    ui->ventasList->setModel(model);
    ui->ventasList->setItemDelegate(new QSqlRelationalDelegate(ui->ventasList));
    ui->ventasList->setSortingEnabled(true);
}


void CompraVenta::vincularCompraVenta()
{
    int rowIndex =  ui->ventasList->currentIndex().row();
    int idVenta = ui->ventasList->currentIndex().sibling(rowIndex,0).data().toInt();
    DetalleCompraVenta *detalle = new DetalleCompraVenta(idCompra, idVenta);
    detalle->exec();
}

void CompraVenta::on_ventasList_clicked(const QModelIndex &index)
{
    ui->vincular->setEnabled(true);
}

void CompraVenta::on_vincular_clicked()
{
    vincularCompraVenta();
}

void CompraVenta::on_ventasList_doubleClicked()
{
    vincularCompraVenta();
}

void CompraVenta::on_nueva_venta_clicked()
{
    this->close();
    QSqlQuery query;
    query.prepare("SELECT * FROM compras WHERE _id = :id");
    query.bindValue(":id",idCompra);
    query.exec();
    query.next();
    int grano = query.value(7).toInt();
    int tiponegocio = query.value(6).toInt();
    QString moneda = query.value(10).toString();

    AgregarVenta *venta = new AgregarVenta();
    int ret = venta->agregarventa(grano,tiponegocio,moneda);

    QSqlQueryModel UltimaVenta;
    UltimaVenta.setQuery("SELECT last_insert_rowid()");
    int idUltimaVenta = UltimaVenta.data(UltimaVenta.index(0,0)).toInt();

    if(ret){
        DetalleCompraVenta *detalle = new DetalleCompraVenta(idCompra,idUltimaVenta);
        detalle->exec();
    }

}
