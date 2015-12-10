#include "cargasdeposito.h"
#include "ui_cargasdeposito.h"
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include "calzarcarga.h"

CargasDeposito::CargasDeposito(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CargasDeposito)
{
    ui->setupUi(this);
    loadData();
}


void CargasDeposito::loadData()
{
    ui->deposito->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->deposito->setSelectionBehavior(QTableView::SelectRows);
    ui->deposito->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->deposito->resizeColumnsToContents();

    QSqlRelationalTableModel *model = new QSqlRelationalTableModel(0, QSqlDatabase::database());

    model->setTable("cargas");
    model->setRelation(8, QSqlRelation("cliente", "cuit", "nombre"));
    model->setRelation(2, QSqlRelation("cereales", "id", "cereal"));

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Fecha"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Grano"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Cosecha"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Kilos"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Origen"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("N° C porte"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Tipo"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Cliente"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Tarifa a cobrar"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Tarifa a pagar"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("Se cobra"));
    model->setHeaderData(12, Qt::Horizontal, QObject::tr("Se paga"));
    model->setHeaderData(13, Qt::Horizontal, QObject::tr("Pagado"));
    model->setHeaderData(14, Qt::Horizontal, QObject::tr("Cobrado"));
    model->setHeaderData(15, Qt::Horizontal, QObject::tr("Transportista"));
    model->setHeaderData(16, Qt::Horizontal, QObject::tr("Observaciones"));


    QString filter = "en_deposito = 1";

    model->setFilter(filter);

    model->select();

    ui->deposito->setModel(model);
    ui->deposito->setItemDelegate(new QSqlRelationalDelegate(ui->deposito));
    ui->deposito->setSortingEnabled(true);


    // OCULTAR COLUMNAS deposito
    ui->deposito->setColumnHidden(0,true);
    ui->deposito->setColumnHidden(5,true);
    ui->deposito->setColumnHidden(6,true);
    ui->deposito->setColumnHidden(9,true);
    ui->deposito->setColumnHidden(10,true);
    ui->deposito->setColumnHidden(11,true);
    ui->deposito->setColumnHidden(12,true);
    ui->deposito->setColumnHidden(13,true);
    ui->deposito->setColumnHidden(14,true);
    ui->deposito->setColumnHidden(15,true);
    ui->deposito->setColumnHidden(17,true);
    ui->deposito->setColumnHidden(18,true);
    ui->deposito->setColumnHidden(19,true);

    ui->deposito->resizeColumnsToContents();
}

CargasDeposito::~CargasDeposito()
{
    delete ui;
}

void CargasDeposito::on_deposito_clicked()
{
    ui->asociar->setEnabled(true);
}

void CargasDeposito::on_salir_clicked()
{
    this->close();
}

void CargasDeposito::on_asociar_clicked()
{
    QModelIndex index = ui->deposito->currentIndex();
    int row = index.row();
    int id_carga = index.sibling(row, 0).data().toInt();

    CalzarCarga *calzar = new CalzarCarga(id_carga);
    this->close();
    calzar->exec();
}
