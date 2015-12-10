#include "compraventa.h"
#include "ui_compraventa.h"
#include "detallecompraventa.h"
#include "agregarventa.h"
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>

CompraVenta::CompraVenta(int id_compra, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CompraVenta)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    ui->ventasList->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->ventasList->setSelectionBehavior(QTableView::SelectRows);
    ui->ventasList->setEditTriggers(QAbstractItemView::NoEditTriggers);

    idCompra = id_compra;

    showVentas();

}

CompraVenta::~CompraVenta()
{
    delete ui;
}

void CompraVenta::showVentas(){

    QSqlRelationalTableModel *model = new QSqlRelationalTableModel(0, QSqlDatabase::database());

    QSqlQueryModel compra;
    QString where;
    QString filtroCereal;
    QString filtroNegocio;
    QString filtroMoneda;
    QString tipoCereal;
    QString tipoNegocio;
    QString moneda;

    QString query = "SELECT * FROM compras WHERE _id=";
    query.append(QString::number(idCompra));
    compra.setQuery(query);

    tipoCereal = compra.data(compra.index(0,7)).toString();
    tipoNegocio = compra.data(compra.index(0,6)).toString();
    moneda = compra.data(compra.index(0,10)).toString();


    filtroCereal = "tipocereal = " + tipoCereal;
    filtroNegocio = "tiponegocio = " + tipoNegocio;
    filtroMoneda = "moneda = '" + moneda + "'";

    where = filtroCereal + " AND " + filtroNegocio + " AND " + filtroMoneda + " AND kilos > kiloscalzados";

    model->setTable("ventas");
    model->setRelation(7, QSqlRelation("comprador", "cuit", "nombre"));
    model->setRelation(11, QSqlRelation("cereales", "id", "cereal"));
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->setFilter(where);
    qDebug() << idCompra;
    qDebug() << moneda;
    qDebug() << model->filter();

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

void CompraVenta::on_ventasList_clicked()
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

void CompraVenta::on_pushButton_clicked()
{
    this->close();
}
