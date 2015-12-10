#include "listadoclientes.h"
#include "ui_listadoclientes.h"
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include "agregarcliente.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

ListadoClientes::ListadoClientes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListadoClientes)
{
    ui->setupUi(this);
    mostrarClientes();
    this->setWindowTitle("Listado Clientes");

}

ListadoClientes::~ListadoClientes()
{
    delete ui;
}

void ListadoClientes::mostrarClientes()
{

    QSqlRelationalTableModel *model = new QSqlRelationalTableModel(0, QSqlDatabase::database());

    model->setTable("cliente");

    model->setHeaderData(1, Qt::Horizontal, QObject::tr("CUIT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nombre y Apellido"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Dirección"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Localidad"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Provincia"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Teléfono"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Mail"));


    model->select();

    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    ui->tableView->setSortingEnabled(true);
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->resizeColumnsToContents();


}

void ListadoClientes::eliminarCliente(){
    disableButtons();

    QModelIndex index = ui->tableView->currentIndex();
    int row = index.row();
    int id = index.sibling(row, 0).data().toInt();
    qDebug() << id;

    QMessageBox msgBox;
    msgBox.setText("¿Está seguro que desea eliminar el cliente seleccionado?");
    msgBox.setWindowTitle("Eliminar cliente");
    msgBox.addButton("Aceptar", QMessageBox::YesRole);
    msgBox.addButton("Cancelar", QMessageBox::NoRole);
    msgBox.setIcon(QMessageBox::Question);

    int ret = msgBox.exec();
    QSqlQuery query;
    switch(ret){
        case 0:
            query.prepare("DELETE FROM cliente WHERE id = :id");
            query.bindValue(":id",id);
            query.exec();
            //qDebug() << query.lastError();
            mostrarClientes();
            break;
        default:
            break;
    }
}


void ListadoClientes::disableButtons(){
    ui->eliminar->setDisabled(true);
}

void ListadoClientes::enableButtons(){
    ui->eliminar->setDisabled(false);
}

void ListadoClientes::on_nuevocliente_clicked()
{
    AgregarCliente *cliente = new AgregarCliente();
    int ret = cliente->exec();
    qDebug() << ret;
    if(ret){
        qDebug() << "ok";
        mostrarClientes();
    }
}

void ListadoClientes::on_eliminar_clicked()
{
    eliminarCliente();
}

void ListadoClientes::on_tableView_clicked()
{
    enableButtons();
}
