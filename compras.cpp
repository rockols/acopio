#include "compras.h"
#include "ui_compras.h"
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include "concretarofrecido.h"
#include "compraventa.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>


Compras::Compras(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Compras)
{
    ui->setupUi(this);

    ui->comprasList->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->comprasList->setSelectionBehavior(QTableView::SelectRows);
    ui->comprasList->setEditTriggers(QAbstractItemView::NoEditTriggers);

    showCompras();

}

void Compras::showCompras()
{
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
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Precio concretado (por ton.)"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Moneda"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("Kilos"));
    model->setHeaderData(12, Qt::Horizontal, QObject::tr("Kilos concretados"));
    model->setHeaderData(13, Qt::Horizontal, QObject::tr("Kilos calzados"));
    model->setHeaderData(14, Qt::Horizontal, QObject::tr("Kilos entregados"));
    model->setHeaderData(15, Qt::Horizontal, QObject::tr("Cliente"));
    model->setHeaderData(16, Qt::Horizontal, QObject::tr("Lugar de carga"));
    model->setHeaderData(17, Qt::Horizontal, QObject::tr("Observaciones"));

    model->setFilter("concretado = 1");

    model->select();

    ui->comprasList->setModel(model);
    ui->comprasList->setItemDelegate(new QSqlRelationalDelegate(ui->comprasList));
    ui->comprasList->setSortingEnabled(true);

    // OCULTAR COLUMNAS COMPRAS
    ui->comprasList->setColumnHidden(0,true);
    ui->comprasList->setColumnHidden(1,true);
    ui->comprasList->setColumnHidden(3,true);
    ui->comprasList->setColumnHidden(8,true);
    ui->comprasList->setColumnHidden(11,true);
    ui->comprasList->setColumnHidden(18,true);
    ui->comprasList->setColumnHidden(19,true);

    for (int c = 0; c < ui->comprasList->horizontalHeader()->count() -2; ++c)
    {
        ui->comprasList->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::ResizeToContents);
    }
    ui->comprasList->horizontalHeader()->setSectionResizeMode(
        ui->comprasList->horizontalHeader()->count() - 2, QHeaderView::Stretch);

}

void Compras::nuevaCompra()
{
    ConcretarOfrecido *nuevaCompra = new ConcretarOfrecido();

    int ret = nuevaCompra->nuevaCompra();
    if(ret)
        showCompras();
}

void Compras::enableButtons()
{
    ui->eliminarCompra->setEnabled(true);
    ui->modificarCompra->setEnabled(true);
    ui->vincularCompra->setEnabled(true);
    ui->anadir_carga->setEnabled(true);
}

void Compras::disableButtons()
{
    ui->eliminarCompra->setEnabled(false);
    ui->modificarCompra->setEnabled(false);
    ui->vincularCompra->setEnabled(false);
    ui->anadir_carga->setEnabled(false);
}

void Compras::deleteCompra()
{
    disableButtons();

    QModelIndex index = ui->comprasList->currentIndex();
    int row = index.row();
    int id = index.sibling(row, 0).data().toInt();

    QMessageBox msgBox;
    msgBox.setText("¿Está seguro que desea eliminar la compra seleccionada?");
    msgBox.setWindowTitle("Eliminar compra");
    msgBox.addButton("Aceptar", QMessageBox::YesRole);
    msgBox.addButton("Cancelar", QMessageBox::NoRole);
    msgBox.setIcon(QMessageBox::Question);

    int ret = msgBox.exec();

    switch(ret){
        case 0:
            {
                QSqlQuery query;
                query.prepare("DELETE FROM compras WHERE _id = :id");
                query.bindValue(":id",id);
                query.exec();
                showCompras();
                break;
            }
        default:
            break;
    }
}

void Compras::modifyCompra()
{
    disableButtons();

    ConcretarOfrecido *nuevaCompra = new ConcretarOfrecido();

    // GET COMPRA id
    int rowIndex =  ui->comprasList->currentIndex().row();
    int id = ui->comprasList->currentIndex().sibling(rowIndex,0).data().toInt();

    int ret = nuevaCompra->modificar(id);
    if(ret)
        showCompras();
}

void Compras::vincCompra()
{
    disableButtons();

    //PASAR TIPO DE GRANO & ID DE LA VENTA
    int rowIndex =  ui->comprasList->currentIndex().row();
    int idCompra = ui->comprasList->currentIndex().sibling(rowIndex,0).data().toInt();

    CompraVenta *cv = new CompraVenta(idCompra);
    cv->exec();
}

void Compras::on_nuevaCompra_clicked()
{
    nuevaCompra();
}

void Compras::on_comprasList_clicked()
{
    enableButtons();
}

void Compras::on_eliminarCompra_clicked()
{
    deleteCompra();
}

void Compras::on_modificarCompra_clicked()
{
    modifyCompra();
}

void Compras::on_vincularCompra_clicked()
{
    vincCompra();
}

void Compras::on_comprasList_doubleClicked()
{
    vincCompra();
}

void Compras::on_pushButton_clicked()
{
    showCompras();
    disableButtons();
}
