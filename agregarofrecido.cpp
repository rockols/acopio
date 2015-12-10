#include "agregarofrecido.h"
#include "ui_agregarofrecido.h"
#include "connection.h"
#include <QSqlRelationalTableModel>
#include <QDataWidgetMapper>
#include "agregarcliente.h"
#include "ofrecidos.h"
#include <QDebug>
#include "helper.h"

AgregarOfrecido::AgregarOfrecido(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AgregarOfrecido)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);

    ui->fecha_venta->setDate(QDate::currentDate());

    ui->kilos->setValidator(new QIntValidator(0, 100000, this));
    ui->precio_base->setValidator(new QIntValidator(0, 100000, this));

    ui->pushButton->show();
    ui->pushButton_8->hide();
    ui->id->hide();
    ui->grano->setMinimumHeight(25);
    Helper::populateClienteField(ui->cliente);
    Helper::populateCerealField(ui->grano);

}

AgregarOfrecido::~AgregarOfrecido()
{
    delete ui;
}

void AgregarOfrecido::on_pushButton_clicked()
{
    if(validarOfrecido())
    {
        QSqlQuery query;

        query.prepare("insert into compras (fechaingreso,fechacompra,precio , tipocereal , tiponegocio , concretado ,cliente ,kilos ,observaciones, moneda, prioridad) "
                                 "values(:fechaingreso,:fechacompra, :precio, :tipocereal, :tiponegocio, :concretado, :cliente, :kilos, :observaciones,:moneda,:prioridad)");
        query.bindValue(":fechaingreso", QDate::currentDate());
        query.bindValue(":fechacompra", ui->fecha_venta->date());
        query.bindValue(":precio", ui->precio_base->text().toDouble());
        query.bindValue(":tipocereal", ui->grano->itemData(ui->grano->currentIndex()).toInt());
        query.bindValue(":tiponegocio", ui->tipo_negocio->currentText().toInt());
        query.bindValue(":concretado", 0);
        query.bindValue(":cliente", ui->cliente->itemData(ui->cliente->currentIndex()).toDouble());
        query.bindValue(":kilos", ui->kilos->text().toDouble());
        query.bindValue(":observaciones", ui->observaciones->toPlainText());
        query.bindValue(":moneda", ui->moneda->currentText());
        query.bindValue(":prioridad", ui->prioridad->currentText().toInt());

        if(!query.exec())
        {
            QMessageBox::warning(0, QObject::tr("Advertencia"),"Ha ocurrido un error, por favor inténtelo nuevamente");

        }
        else
            this->accept();
    }
}

int AgregarOfrecido::validarOfrecido()
{
    QString error = "";
    int ret = 1;
    QString precio = ui->precio_base->text();
    if(precio.length() == 0)
    {
        error.append("- Debe ingresar el precio base\n");
        ret = 0;
    }
    QString kilos = ui->kilos->text();
    if(kilos.length() == 0)
    {
        error.append("- Debe ingresar la cantidad de kilos \n");
        ret = 0;
    }
    if(ret == 0)
        QMessageBox::warning(0, QObject::tr("Advertencia"),error);
    return ret;
}



void AgregarOfrecido::on_pushButton_3_clicked()
{
    AgregarCliente *nuevocliente = new AgregarCliente(0);
    int ret = nuevocliente->exec();
    if(ret == 0)
    {
        ui->cliente->clear();
        Helper::populateClienteField(ui->cliente);
    }
}

int AgregarOfrecido::editarOfrecido(int id)
{
    this->setWindowTitle("Editar Ofrecido");
    ui->pushButton_3->hide();
    QSqlQuery query;
    query.prepare("SELECT * FROM compras WHERE _id = :id");
    query.bindValue(":id",id);
    query.exec();
    query.next();
    ui->prioridad->setCurrentIndex(query.value(1).toInt()-1);
    ui->observaciones->setText(query.value(17).toString());
    ui->kilos->setText(query.value(11).toString());
    ui->tipo_negocio->setCurrentIndex(query.value(6).toInt()-1);
    ui->precio_base->setText(query.value(8).toString());
    ui->fecha_venta->setDate(query.value(3).toDate());
    ui->id->setText(query.value(0).toString());

    int indexCliente = ui->cliente->findData(query.value(15));
    ui->cliente->setCurrentIndex(indexCliente);

    int indexGrano = ui->grano->findData(query.value(7));
    ui->grano->setCurrentIndex(indexGrano);

    if(query.value(10).toString() == "Peso")
        ui->moneda->setCurrentIndex(0);
    else
        ui->moneda->setCurrentIndex(1);

    ui->pushButton->hide();
    ui->pushButton_8->show();
    return (this->exec());
}

int AgregarOfrecido::on_pushButton_8_clicked()
{
    if(validarOfrecido())
    {
        QSqlQuery query;

        query.prepare("UPDATE compras SET "
                      "fechacompra = :fechacompra,precio = :precio, tipocereal = :tipocereal, tiponegocio = :tiponegocio, cliente = :cliente ,kilos = :kilos ,observaciones = :observaciones, moneda = :moneda, prioridad = :prioridad"
                      " WHERE _id = :id ");

        query.bindValue(":fechacompra", ui->fecha_venta->date());
        query.bindValue(":precio", ui->precio_base->text().toDouble());
        query.bindValue(":tipocereal", ui->grano->itemData(ui->grano->currentIndex()).toInt());
        query.bindValue(":tiponegocio", ui->tipo_negocio->currentText().toInt());
        query.bindValue(":cliente", ui->cliente->itemData(ui->cliente->currentIndex()).toDouble());
        query.bindValue(":kilos", ui->kilos->text().toDouble());
        query.bindValue(":observaciones", ui->observaciones->toPlainText());
        query.bindValue(":moneda", ui->moneda->currentText());
        query.bindValue(":prioridad", ui->prioridad->currentText().toInt());
        query.bindValue(":id", ui->id->text().toInt());
        int ret = query.exec();

        if(!ret)
            QMessageBox::warning(0, QObject::tr("Advertencia"),"Ha ocurrido un error, por favor inténtelo nuevamente");
        else
            this->accept();
        return ret;
    }
    return 0;
}
