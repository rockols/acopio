#include "ofrecidos.h"
#include "ui_ofrecidos.h"
#include "agregarofrecido.h"
#include "concretarofrecido.h"
#include <QSqlQuery>
#include <QSqlRelationalTableModel>
#include <QMessageBox>
#include <QMenu>


Ofrecidos::Ofrecidos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ofrecidos)
{
    ui->setupUi(this);

    ui->ofrecidosList->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->ofrecidosList->setSelectionBehavior(QTableView::SelectRows);
    ui->ofrecidosList->setEditTriggers(QAbstractItemView::NoEditTriggers);

    showOfrecidos();
}

void Ofrecidos::showOfrecidos(){

    QSqlRelationalTableModel *model = new QSqlRelationalTableModel(0, QSqlDatabase::database());

    model->setTable("compras");
    model->setRelation(7, QSqlRelation("cereales", "id", "cereal"));
    model->setRelation(15, QSqlRelation("cliente", "cuit", "nombre"));
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prioridad"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Fecha Ingreso"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Fecha estimada de Compra"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Tipo"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Grano"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Precio base (por ton.)"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Moneda"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("Kilos"));
    model->setHeaderData(15, Qt::Horizontal, QObject::tr("Cliente"));
    model->setHeaderData(17, Qt::Horizontal, QObject::tr("Observaciones"));

    model->setFilter("concretado = 0");
    model->select();

    ui->ofrecidosList->setModel(model);
    ui->ofrecidosList->setItemDelegate(new QSqlRelationalDelegate(ui->ofrecidosList));
    ui->ofrecidosList->setSortingEnabled(true);


    // OCULTAR COLUMNAS COMPRAS
    ui->ofrecidosList->setColumnHidden(0,true);
    ui->ofrecidosList->setColumnHidden(4,true);
    ui->ofrecidosList->setColumnHidden(5,true);
    ui->ofrecidosList->setColumnHidden(9,true);
    ui->ofrecidosList->setColumnHidden(12,true);
    ui->ofrecidosList->setColumnHidden(13,true);
    ui->ofrecidosList->setColumnHidden(14,true);
    ui->ofrecidosList->setColumnHidden(16,true);
    ui->ofrecidosList->setColumnHidden(18,true);
    ui->ofrecidosList->setColumnHidden(19,true);

    for (int c = 0; c < ui->ofrecidosList->horizontalHeader()->count() -2; ++c)
    {
        ui->ofrecidosList->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::ResizeToContents);
    }
    ui->ofrecidosList->horizontalHeader()->setSectionResizeMode(
        ui->ofrecidosList->horizontalHeader()->count() - 2, QHeaderView::Stretch);

}

void Ofrecidos::newOfrecido()
{
    AgregarOfrecido *agregarofrecido = new AgregarOfrecido(0);
    int ret = agregarofrecido->exec();
    if(ret)
        showOfrecidos();
}

void Ofrecidos::eliminarOfrecido()
{
    disableButtons();

    QModelIndex index = ui->ofrecidosList->currentIndex();
    int row = index.row();
    int id = index.sibling(row, 0).data().toInt();

    QMessageBox msgBox;
    msgBox.setText("¿Está seguro que desea eliminar el ofrecido seleccionado?");
    msgBox.setWindowTitle("Eliminar ofrecido");
    msgBox.addButton("Aceptar", QMessageBox::YesRole);
    msgBox.addButton("Cancelar", QMessageBox::NoRole);
    msgBox.setIcon(QMessageBox::Question);

    int ret = msgBox.exec();
    QSqlQuery query;
    switch(ret){
        case 0:
            query.prepare("DELETE FROM compras WHERE _id = :id");
            query.bindValue(":id",id);
            query.exec();
            showOfrecidos();
            break;
        default:
            break;
    }
}

void Ofrecidos::modifyOfrecido()
{
    ui->concretarOfrecido->setEnabled(false);
    ui->modificarOfrecido->setEnabled(false);
    ui->eliminarOfrecido->setEnabled(false);

    //PASAR ID DEL OFRECIDO
    int rowIndex =  ui->ofrecidosList->currentIndex().row();
    int id = ui->ofrecidosList->currentIndex().sibling(rowIndex,0).data().toInt();

    AgregarOfrecido *agregarofrecido = new AgregarOfrecido(0);
    if(agregarofrecido->editarOfrecido(id))
        showOfrecidos();

}

void Ofrecidos::ConcOfrecido()
{
    ui->concretarOfrecido->setEnabled(false);
    ui->modificarOfrecido->setEnabled(false);
    ui->eliminarOfrecido->setEnabled(false);

    //PASAR ID DEL OFRECIDO
    int rowIndex =  ui->ofrecidosList->currentIndex().row();
    int id = ui->ofrecidosList->currentIndex().sibling(rowIndex,0).data().toInt();

    ConcretarOfrecido *ofrecido =  new ConcretarOfrecido();
    int ret = ofrecido->concretar(id);
    if(ret)
        showOfrecidos();
}

void Ofrecidos::disableButtons()
{
    ui->concretarOfrecido->setEnabled(false);
    ui->modificarOfrecido->setEnabled(false);
    ui->eliminarOfrecido->setEnabled(false);
}

void Ofrecidos::enableButtons()
{
    ui->concretarOfrecido->setEnabled(true);
    ui->modificarOfrecido->setEnabled(true);
    ui->eliminarOfrecido->setEnabled(true);
}

void Ofrecidos::on_nuevoOfrecido_clicked()
{
    newOfrecido();
}

void Ofrecidos::on_eliminarOfrecido_clicked()
{
    eliminarOfrecido();
}

void Ofrecidos::on_ofrecidosList_clicked()
{
    enableButtons();
}

void Ofrecidos::on_modificarOfrecido_clicked()
{
    modifyOfrecido();
}

void Ofrecidos::on_ofrecidosList_doubleClicked()
{
    ConcOfrecido();
}

void Ofrecidos::on_concretarOfrecido_clicked()
{
    ConcOfrecido();
}
