#include "detallecompraventa.h"
#include "ui_detallecompraventa.h"
#include <QSqlQuery>
#include <QSqlQueryModel>

DetalleCompraVenta::DetalleCompraVenta(int idCompra, int idVenta, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DetalleCompraVenta)
{
    ui->setupUi(this);
    populateCerealField();
    populateClienteField();
    showDetalles(idCompra,idVenta);
}

DetalleCompraVenta::~DetalleCompraVenta()
{
    delete ui;
}

void DetalleCompraVenta::showDetalles(int idCompra,int idVenta)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM compras WHERE _id = :id");
    query.bindValue(":id",idCompra);
    query.exec();
    query.next();
    ui->fecha_venta->setDate(query.value(3).toDate());
    ui->id->setText(query.value(0).toString());
    ui->fecha_pago->setDate(query.value(5).toDate());
    ui->fecha_conc_compra->setDate(query.value(4).toDate());
    ui->precio_concretado->setText(query.value(9).toString());
    ui->kilos_concretados->setText(query.value(12).toString());

    int indexCliente = ui->cliente->findData(query.value(15));
    ui->cliente->setCurrentIndex(indexCliente);

    //int indexGrano = ui->grano->findData(query.value(7));
    //ui->grano->setCurrentIndex(indexGrano);

    populateLocalizacionField();
    int indexLocalizacion = ui->localizacion->findData(query.value(16));
    ui->localizacion->setCurrentIndex(indexLocalizacion);

    if(query.value(10).toString() == "Peso")
        ui->moneda->setCurrentIndex(0);
    else
        ui->moneda->setCurrentIndex(1);

}


void DetalleCompraVenta::populateCerealField()
{
    QSqlQueryModel cereal;
    cereal.setQuery("SELECT cereal,id FROM cereales");
    for(int i=0; i < cereal.rowCount(); i++)
    {
        //ui->grano->addItem( cereal.data(cereal.index(i,0)).toString(), QVariant( cereal.data(cereal.index(i,1)).toInt()));
    }
}

void DetalleCompraVenta::populateClienteField()
{
    QSqlQueryModel cliente;
    cliente.setQuery ("SELECT nombre,cuit FROM cliente ORDER BY nombre");

    for(int i=0; i < cliente.rowCount(); i++)
    {
        ui->cliente->addItem( cliente.data(cliente.index(i,0)).toString(), QVariant( cliente.data(cliente.index(i,1)).toDouble()));
    }
}

void DetalleCompraVenta::populateLocalizacionField()
{
    ui->localizacion->clear();
    QSqlQuery query;
    query.prepare("SELECT id, lugar FROM localizacion WHERE _id = 1 OR cliente = :cliente");
    query.bindValue(":cliente",ui->cliente->itemData(ui->cliente->currentIndex()).toLongLong());
    query.exec();

    QSqlQueryModel campos;
    campos.setQuery(query);

    for(int i=0; i < campos.rowCount(); i++)
    {
        ui->localizacion->addItem( campos.data(campos.index(i,1)).toString(), campos.data(campos.index(i,0)).toInt());
    }
}

