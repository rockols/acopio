#include "listadoclientes.h"
#include "ui_listadoclientes.h"
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>

ListadoClientes::ListadoClientes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListadoClientes)
{
    ui->setupUi(this);
    mostrarClientes();
}

ListadoClientes::~ListadoClientes()
{
    delete ui;
}

void ListadoClientes::mostrarClientes()
{

    QSqlRelationalTableModel *model = new QSqlRelationalTableModel(0, QSqlDatabase::database());

    model->setTable("cliente");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->select();

    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    ui->tableView->setSortingEnabled(true);

}
