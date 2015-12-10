#include "calzarcarga.h"
#include "ui_calzarcarga.h"
#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

CalzarCarga::CalzarCarga(int id_carga,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalzarCarga)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    prevCompra = 0;
    prevVenta = 0;
    idCarga = id_carga;
    loadData(id_carga);

    ui->comprador_id->setVisible(false);
    ui->id_cliente->setVisible(false);

}

CalzarCarga::~CalzarCarga()
{
    delete ui;
}


void CalzarCarga::loadData(int id_carga){
    //OBTENER INFO DE CARGA
    QSqlQueryModel carga;
    QString query = "SELECT * FROM cargas WHERE _id=";
    query.append(QString::number(id_carga));
    carga.setQuery(query);

    QString tipoCereal = carga.data(carga.index(0,2)).toString();
    int kilos = carga.data(carga.index(0,4)).toInt();
    kilosCarga = kilos;
    clienteCarga = carga.data(carga.index(0,8)).toLongLong();
    int id_compra = carga.data(carga.index(0,17)).toInt();
    int id_venta = carga.data(carga.index(0,18)).toInt();

    loadCompras(tipoCereal, kilos);
    loadVentas(tipoCereal, kilos);

    if(id_compra == 0)
    {
        ui->stackedCompras->setCurrentIndex(0);
    }
    else
    {
        loadCompraData(id_compra);
        ui->stackedCompras->setCurrentIndex(1);
    }
    if(id_venta == 0)
    {
        ui->stackedVentas->setCurrentIndex(0);
    }
    else
    {
        loadVentaData(id_venta);
        ui->stackedVentas->setCurrentIndex(1);
    }
}

void CalzarCarga::loadCompras(QString cereal, int kilos){

    ui->compras->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->compras->setSelectionBehavior(QTableView::SelectRows);
    ui->compras->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->compras->resizeColumnsToContents();

    //OBTENER INFO DE COMPRA Y CARGAR DATOS EN TABLA
    QSqlRelationalTableModel *model = new QSqlRelationalTableModel(0, QSqlDatabase::database());

    model->setTable("compras");
    model->setRelation(7, QSqlRelation("cereales", "id", "cereal"));
    model->setRelation(15, QSqlRelation("cliente", "cuit", "nombre"));
    model->setRelation(16, QSqlRelation("localizacion", "id", "lugar"));
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Fecha Ingreso"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Fecha estimada de Compra"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Fecha concretado"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Fecha de pago"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Tipo"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Grano"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Precio base (por ton.)"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Precio"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Moneda"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("Kilos"));
    model->setHeaderData(12, Qt::Horizontal, QObject::tr("Kilos concretados"));
    model->setHeaderData(13, Qt::Horizontal, QObject::tr("Kilos calzados"));
    model->setHeaderData(14, Qt::Horizontal, QObject::tr("Kilos entregados"));
    model->setHeaderData(15, Qt::Horizontal, QObject::tr("Cliente"));
    model->setHeaderData(16, Qt::Horizontal, QObject::tr("Lugar de carga"));
    model->setHeaderData(17, Qt::Horizontal, QObject::tr("Observaciones"));

    QString filter = "concretado == 1 AND tipocereal == " + cereal + " AND kilosconcretados-kilosentregados >= " + QString::number(kilos);

    model->setFilter(filter);
    model->select();

    ui->compras->setModel(model);
    ui->compras->setItemDelegate(new QSqlRelationalDelegate(ui->compras));
    ui->compras->setSortingEnabled(true);

    // OCULTAR COLUMNAS COMPRAS
    //ui->compras->setColumnHidden(0,true);
    ui->compras->setColumnHidden(1,true);
    ui->compras->setColumnHidden(3,true);
    ui->compras->setColumnHidden(8,true);
    ui->compras->setColumnHidden(11,true);
    ui->compras->setColumnHidden(18,true);

}

void CalzarCarga::loadVentas(QString cereal, int kilos){

    ui->ventas->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->ventas->setSelectionBehavior(QTableView::SelectRows);
    ui->ventas->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->ventas->resizeColumnsToContents();

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
    model->setHeaderData(12, Qt::Horizontal, QObject::tr("Precio"));
    model->setHeaderData(13, Qt::Horizontal, QObject::tr("Moneda"));
    model->setHeaderData(14, Qt::Horizontal, QObject::tr("Observaciones"));


    QString filter = "tipocereal == " + cereal + " AND kilos-kiloscumplidos >= " + QString::number(kilos);

    model->setFilter(filter);

    model->select();

    ui->ventas->setModel(model);
    ui->ventas->setItemDelegate(new QSqlRelationalDelegate(ui->ventas));
    ui->ventas->setSortingEnabled(true);

    // OCULTAR COLUMNAS VENTAS
    //ui->ventas->setColumnHidden(0,true);
    ui->ventas->setColumnHidden(1,true);
}

void CalzarCarga::loadCompraData(int id_compra)
{

    //OBTENER INFO DE COMPRA
    QSqlQueryModel compra;
    QString query = "SELECT * FROM compras WHERE _id=";
    query.append(QString::number(id_compra));
    compra.setQuery(query);

    qlonglong id_cliente = compra.data(compra.index(0,15)).toLongLong();
    int id = compra.data(compra.index(0,0)).toLongLong();
    QString kilos = compra.data(compra.index(0,12)).toString();
    QString tipo = compra.data(compra.index(0,6)).toString();
    QString moneda = compra.data(compra.index(0,10)).toString();
    QString precio = compra.data(compra.index(0,9)).toString();

    query = "SELECT * FROM cliente WHERE cuit=";
    query.append(QString::number(id_cliente));
    compra.setQuery(query);

    QString cliente = compra.data(compra.index(0,2)).toString();

    ui->cliente->setText(cliente);
    ui->tipo->setText(tipo);
    ui->moneda->setText(moneda);
    ui->precio->setText(precio);
    ui->kilos->setText(kilos);
    ui->id_cliente->setText(QString::number(id));

}

void CalzarCarga::loadVentaData(int id_venta)
{
    //OBTENER INFO DE COMPRA
    QSqlQueryModel venta;
    QString query = "SELECT * FROM ventas WHERE _id=";
    query.append(QString::number(id_venta));
    venta.setQuery(query);

    qlonglong id_comprador = venta.data(venta.index(0,7)).toLongLong();
    int id = venta.data(venta.index(0,0)).toLongLong();
    QString kilos = venta.data(venta.index(0,8)).toString();
    QString tipo = venta.data(venta.index(0,13)).toString();
    QString moneda = venta.data(venta.index(0,13)).toString();
    QString precio = venta.data(venta.index(0,12)).toString();
    QString contrato = venta.data(venta.index(0,6)).toString();


    query = "SELECT * FROM comprador WHERE cuit=";
    query.append(QString::number(id_comprador));
    venta.setQuery(query);

    QString comprador = venta.data(venta.index(0,1)).toString();

    ui->comprador->setText(comprador);
    ui->tipo1->setText(tipo);
    ui->moneda_2->setText(moneda);
    ui->precio_2->setText(precio);
    ui->kilos_2->setText(kilos);
    ui->contrato->setText(contrato);
    ui->comprador_id->setText(QString::number(id));
}

void CalzarCarga::on_compras_clicked(const QModelIndex &index)
{
    //AL MOMENTO DE ASIGNAR CARGA A COMPRA PRIMERO CHEQUEAR prevCompra, si es -1, entonces no se
    // asigna ninguna a COMPRA
    int row = index.row();
    int id = index.sibling(row, 0).data().toInt();
    if(prevCompra == id)
    {
        ui->compras->clearSelection();
        prevCompra = 0;
        clienteCompra = 0;
        if(prevVenta == 0) ui->aceptar->setEnabled(false);
    }
    else
    {
        prevCompra = id;
        QString sql = "SELECT cliente FROM compras WHERE _id = ";
        sql.append(QString::number(prevCompra));
        QSqlQuery query(sql);
        query.exec();
        query.next();
        clienteCompra = query.value(0).toLongLong();
        ui->aceptar->setEnabled(true);
    }
}

void CalzarCarga::on_ventas_clicked(const QModelIndex &index)
{
    //AL MOMENTO DE ASIGNAR CARGA A VENTA PRIMERO CHEQUEAR prevVenta, si es -1, entonces no se
    // asigna ninguna a VENTA
    int row = index.row();
    int id = index.sibling(row, 0).data().toInt();
    if(prevVenta == id)
    {
        ui->ventas->clearSelection();
        prevVenta = 0;
        if(prevCompra == 0) ui->aceptar->setEnabled(false);

    }
    else
    {
        prevVenta = id;
        ui->aceptar->setEnabled(true);
    }
}

void CalzarCarga::on_cancelar_clicked()
{
    this->close();
}

void CalzarCarga::on_aceptar_clicked()
{
    if(ui->stackedCompras->currentIndex() == 1 && ui->stackedVentas->currentIndex() == 1)
        this->close();
    else
    {
        if(ui->stackedCompras->currentIndex() == 1)
        {
            prevCompra = ui->id_cliente->text().toInt();
        }
        if(ui->stackedVentas->currentIndex() == 1)
        {
            prevVenta = ui->comprador_id->text().toInt();
        }

        //ACTUALIZAR CARGA
        QSqlQuery query;
        QString sql = "UPDATE cargas SET en_deposito = 0, origen = :origen,destino = :destino WHERE _id = :id";
        query.prepare(sql);

        query.bindValue(":origen", prevCompra);
        query.bindValue(":destino",prevVenta);
        query.bindValue(":id",idCarga);

        if(query.exec())
        {
            QSqlQuery queryCompra;
            //ACTUALIZAR COMPRA
            // PRIMERO CHEQUEO CLIENTE
            if(prevCompra != 0)
            {
                if(clienteCarga == clienteCompra)
                {
                    queryCompra.prepare("UPDATE compras SET "
                                  "kilosentregados = kilosentregados + :kilosentregados"
                                  " WHERE _id = :id ");
                    queryCompra.bindValue(":kilosentregados",kilosCarga);
                    queryCompra.bindValue(":id",prevCompra);
                }
                else
                {
                    queryCompra.prepare("UPDATE compras SET "
                                  "kilosentregados = :kilos + kilosentregados, kilosprestados = :kilos + kilosprestados"
                                  " WHERE _id = :id ");
                    queryCompra.bindValue(":kilos",kilosCarga);
                    queryCompra.bindValue(":id",prevCompra);
                }
                queryCompra.exec();
            }
            if(prevVenta != 0)
            {
                QSqlQuery queryVenta;
                queryVenta.prepare("UPDATE ventas SET "
                              "kiloscumplidos = :kiloscumplidos + kiloscumplidos"
                              " WHERE _id = :id ");
                queryVenta.bindValue(":kiloscumplidos",kilosCarga);
                queryVenta.bindValue(":id",prevVenta);
                queryVenta.exec();
            }
        }
        this->close();
    }
}

void CalzarCarga::on_modificar_compra_clicked()
{
    ui->stackedCompras->setCurrentIndex(0);
}

void CalzarCarga::on_modificar_compra_2_clicked()
{
    ui->stackedVentas->setCurrentIndex(0);
}
