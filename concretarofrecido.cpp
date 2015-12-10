#include "concretarofrecido.h"
#include "ui_concretarofrecido.h"
#include "agregarcliente.h"
#include "compraventa.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include "helper.h"

ConcretarOfrecido::ConcretarOfrecido(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConcretarOfrecido)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);

    Helper::populateCerealField(ui->grano);
    Helper::populateClienteField(ui->cliente);


    ui->kilos_concretados->setValidator(new QIntValidator(0, 100000, this));
    ui->precio_concretado->setValidator(new QIntValidator(0, 100000, this));
    ui->fecha_conc_compra->setDate(QDate::currentDate());
    ui->fecha_pago->setDate(QDate::currentDate());
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->grano->setMinimumHeight(25);
}


int ConcretarOfrecido::concretar(int id){
    this->setWindowTitle("Concretar Compra");
    ui->cliente->setEnabled(false);
    ui->grano->setEnabled(false);
    ui->kilos->setEnabled(false);
    ui->tipo_negocio->setEnabled(false);
    ui->precio_base->setEnabled(false);
    ui->fecha_venta->setEnabled(false);
    ui->moneda->setEnabled(false);

    QSqlQuery query;
    query.prepare("SELECT * FROM compras WHERE _id = :id");
    query.bindValue(":id",id);
    query.exec();
    query.next();
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

    Helper::populateLocalizacionField(ui->localizacion);

    return (this->exec());
}

int ConcretarOfrecido::modificar(int id)
{
    this->setWindowTitle("Modificar Compra");

    ui->pushButton_3->show();
    ui->pushButton_4->hide();
    ui->pushButton->show();
    ui->kilos->hide();
    ui->precio_base->hide();
    ui->fecha_venta->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();

    QSqlQuery query;
    query.prepare("SELECT * FROM compras WHERE _id = :id");
    query.bindValue(":id",id);
    query.exec();
    query.next();

    ui->observaciones->setText(query.value(17).toString());
    ui->tipo_negocio->setCurrentIndex(query.value(6).toInt()-1);
    ui->precio_base->setText(query.value(8).toString());
    ui->fecha_venta->setDate(query.value(3).toDate());
    ui->id->setText(query.value(0).toString());
    ui->fecha_pago->setDate(query.value(5).toDate());
    ui->fecha_conc_compra->setDate(query.value(4).toDate());
    ui->precio_concretado->setText(query.value(9).toString());
    ui->kilos_concretados->setText(query.value(12).toString());

    int indexCliente = ui->cliente->findData(query.value(15));
    ui->cliente->setCurrentIndex(indexCliente);

    int indexGrano = ui->grano->findData(query.value(7));
    ui->grano->setCurrentIndex(indexGrano);

    Helper::populateLocalizacionField(ui->localizacion);
    int indexLocalizacion = ui->localizacion->findData(query.value(16));
    ui->localizacion->setCurrentIndex(indexLocalizacion);

    if(query.value(10).toString() == "Peso")
        ui->moneda->setCurrentIndex(0);
    else
        ui->moneda->setCurrentIndex(1);

    return (this->exec());
}

int ConcretarOfrecido::updateCompra()
{
    if(validarCompra())
    {
        QSqlQuery query;

        query.prepare("UPDATE compras SET "
                      "observaciones = :observaciones, kilosconcretados = :kilosconcretados, precioconcretado = :precioconcretado, "
                      "fechaconcretado = :fechaconcretado, fechapago = :fechapago, localizacion = :localizacion, concretado = :concretado,"
                      "tipocereal = :tipocereal, tiponegocio = :tiponegocio, cliente = :cliente , moneda = :moneda"
                      " WHERE _id = :id ");

        query.bindValue(":observaciones", ui->observaciones->toPlainText());
        query.bindValue(":kilosconcretados", ui->kilos_concretados->text().toDouble());
        query.bindValue(":precioconcretado", ui->precio_concretado->text().toDouble());
        query.bindValue(":fechaconcretado", ui->fecha_conc_compra->date());
        query.bindValue(":fechapago", ui->fecha_pago->date());
        query.bindValue(":localizacion", ui->localizacion->itemData(ui->localizacion->currentIndex()).toInt());
        query.bindValue(":tipocereal", ui->grano->itemData(ui->grano->currentIndex()).toInt());
        query.bindValue(":tiponegocio", ui->tipo_negocio->currentText().toInt());
        query.bindValue(":cliente", ui->cliente->itemData(ui->cliente->currentIndex()).toDouble());
        query.bindValue(":moneda", ui->moneda->currentText());
        query.bindValue(":concretado", 1);
        query.bindValue(":id", ui->id->text().toInt());

        int ret = query.exec();
        if(!ret)
            QMessageBox::warning(0, QObject::tr("Advertencia"),"Ha ocurrido un error, por favor inténtelo nuevamente");
        else
        {
            // CALZAR COMPRA
            QMessageBox msgBox;
            msgBox.setText("Vincular la compra con una venta?");
            msgBox.setWindowTitle("Calzar compra");
            msgBox.addButton("No vincular", QMessageBox::NoRole);
            msgBox.addButton("Aceptar", QMessageBox::YesRole);
            msgBox.setWindowFlags(Qt::WindowTitleHint);
            msgBox.setIcon(QMessageBox::Question);

            int ret = msgBox.exec();
            switch (ret) {
            case 0:
                this->accept();
                break;
            case 1:
            {

                CompraVenta *cv = new CompraVenta(ui->id->text().toInt());
                cv->exec();
                this->accept();
                break;
            }
            default:
                break;
            }
        }
    }
    return 0;
}

int ConcretarOfrecido::validarCompra()
{
    QString error = "";
    int ret = 1;
    QString precio = ui->precio_concretado->text();
    if(precio.length() == 0)
    {
        error.append("- Debe ingresar el precio concretado\n");
        ret = 0;
    }
    QString kilos = ui->kilos_concretados->text();
    if(kilos.length() == 0)
    {
        error.append("- Debe ingresar la cantidad de kilos concretados\n");
        ret = 0;
    }
    if(ret == 0)
        QMessageBox::warning(0, QObject::tr("Advertencia"),error);
    return ret;
}

int ConcretarOfrecido::nuevaCompra(){

    ui->pushButton_3->show();
    ui->pushButton_4->show();
    ui->pushButton->hide();
    ui->kilos->hide();
    ui->precio_base->hide();
    ui->fecha_venta->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();


    Helper::populateLocalizacionField(ui->localizacion);

    return this->exec();
}

int ConcretarOfrecido::nuevaCompra(qlonglong cliente, int grano)
{
    ui->cliente->setEnabled(false);
    ui->grano->setEnabled(false);
    ui->pushButton_3->hide();

    int indexCliente = ui->cliente->findData(cliente);
    ui->cliente->setCurrentIndex(indexCliente);

    int indexGrano = ui->grano->findData(grano);
    ui->grano->setCurrentIndex(indexGrano);

    return nuevaCompra();


}

int ConcretarOfrecido::insertCompra()
{
    if(validarCompra())
    {
        QSqlQuery query;
        query.prepare("insert into compras (fechaingreso, tipocereal , tiponegocio , concretado ,cliente ,observaciones, moneda, "
                      "kilosconcretados, precioconcretado, precio, fechaconcretado, fechacompra, fechapago, localizacion) "
                                 "values(:fechaingreso,:tipocereal, :tiponegocio, :concretado, :cliente, :observaciones, :moneda,"
                      ":kilosconcretados,:precioconcretado, :precio, :fechaconcretado, :fechacompra, :fechapago, :localizacion)");

        query.bindValue(":fechaingreso", QDate::currentDate());
        query.bindValue(":tipocereal", ui->grano->itemData(ui->grano->currentIndex()).toInt());
        query.bindValue(":tiponegocio", ui->tipo_negocio->currentText().toInt());
        query.bindValue(":cliente", ui->cliente->itemData(ui->cliente->currentIndex()).toDouble());
        query.bindValue(":observaciones", ui->observaciones->toPlainText());
        query.bindValue(":moneda", ui->moneda->currentText());
        query.bindValue(":observaciones", ui->observaciones->toPlainText());
        query.bindValue(":kilosconcretados", ui->kilos_concretados->text().toDouble());
        query.bindValue(":precioconcretado", ui->precio_concretado->text().toDouble());
        query.bindValue(":precio", ui->precio_concretado->text().toDouble());
        query.bindValue(":fechaconcretado", ui->fecha_conc_compra->date());
        query.bindValue(":fechacompra", ui->fecha_conc_compra->date());
        query.bindValue(":fechapago", ui->fecha_pago->date());
        query.bindValue(":localizacion", ui->localizacion->itemData(ui->localizacion->currentIndex()).toInt());
        query.bindValue(":concretado", 1);

        int ret = query.exec();
        qDebug() << query.lastError();
        if(!ret)
            QMessageBox::warning(0, QObject::tr("Advertencia"),"Ha ocurrido un error, por favor inténtelo nuevamente");
        else
        {
            // CALZAR COMPRA
            QMessageBox msgBox;
            msgBox.setText("Vincular la compra con una venta?");
            msgBox.setWindowTitle("Calzar compra");
            msgBox.addButton("No vincular", QMessageBox::NoRole);
            msgBox.addButton("Aceptar", QMessageBox::YesRole);
            msgBox.setWindowFlags(Qt::WindowTitleHint);
            msgBox.setIcon(QMessageBox::Question);

            int ret = msgBox.exec();

            switch (ret) {
            case 0:
                this->accept();
                break;
            case 1:
            {
                CompraVenta *cv = new CompraVenta(query.lastInsertId().toInt());
                cv->exec();
                this->accept();
                break;
            }
            default:
                break;
            }

        }
        return ret;
    }
    return 0;
}

void ConcretarOfrecido::nuevoCliente()
{
    AgregarCliente *nuevocliente = new AgregarCliente(0);
    int ret = nuevocliente->exec();
    if(ret == 0)
    {
        ui->cliente->clear();
        Helper::populateClienteField(ui->cliente);
    }
}

void ConcretarOfrecido::on_pushButton_3_clicked()
{
    nuevoCliente();
}

int ConcretarOfrecido::on_pushButton_4_clicked()
{
    return insertCompra();
}

void ConcretarOfrecido::on_pushButton_2_clicked()
{
    this->close();
}

int ConcretarOfrecido::on_pushButton_clicked()
{
    return updateCompra();
}
