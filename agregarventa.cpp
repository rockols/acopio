#include "agregarventa.h"
#include "ui_agregarventa.h"
#include "nuevocomprador.h"
#include "detallecompraventa.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>

AgregarVenta::AgregarVenta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AgregarVenta)
{
    ui->setupUi(this);

    ui->fecha_venta->setDate(QDate::currentDate());
    ui->fecha_cobro->setDate(QDate::currentDate());
    ui->fecha_venta->setDate(QDate::currentDate());
    ui->fecha_cobro->setDate(QDate::currentDate());

    ui->kilos->setValidator(new QIntValidator(0, 100000, this));
    ui->precio->setValidator(new QIntValidator(0, 100000, this));
    ui->grano->setMinimumHeight(25);
    ui->actualizar->setHidden(true);
    ui->id->setHidden(true);
    populateCompradorField();
    populateCerealField();
}

AgregarVenta::~AgregarVenta()
{
    delete ui;
}

void AgregarVenta::agregarventa(){

    // validar venta
    if(validarVenta())
    {
        QSqlQuery query;

        query.prepare("insert into ventas (fechaventa,fechacobro,contrato ,comprador , kilos ,kiloscalzados,kiloscumplidos, tipocereal ,precio ,moneda ,observaciones, fechadesde, fechahasta,tiponegocio) "
                                 "values(:fechaventa,:fechacobro, :contrato, :comprador, :kilos,:kiloscalzados ,:kiloscumplidos , :tipocereal, :precio, :moneda, :observaciones,:fechadesde,:fechahasta,:tiponegocio)");
        query.bindValue(":fechaventa", ui->fecha_venta->date());
        query.bindValue(":fechacobro", ui->fecha_cobro->date());
        query.bindValue(":fechadesde", ui->fecha_desde->date());
        query.bindValue(":fechahasta", ui->fecha_hasta->date());
        query.bindValue(":contrato", ui->num_contrato->text().toDouble());
        query.bindValue(":comprador", ui->comprador->itemData(ui->comprador->currentIndex()).toDouble());
        query.bindValue(":kilos", ui->kilos->text().toDouble());
        query.bindValue(":kiloscalzados", 0);
        query.bindValue(":kiloscumplidos", 0);
        query.bindValue(":kilos", ui->kilos->text().toDouble());
        query.bindValue(":tipocereal", ui->grano->itemData(ui->grano->currentIndex()).toInt());
        query.bindValue(":precio", ui->precio->text().toDouble());
        query.bindValue(":moneda", ui->moneda->currentText());
        query.bindValue(":observaciones", ui->observaciones->toPlainText());
        query.bindValue(":tiponegocio", ui->tipo_negocio->currentText().toInt());

        if(!query.exec())
        {
            QMessageBox::warning(0, QObject::tr("Advertencia"),"Ha ocurrido un error, por favor inténtelo nuevamente");

        }
        else
            this->accept();
    }
}

int AgregarVenta::agregarventa(int tipograno, int tiponegocio, QString moneda ){

    ui->tipo_negocio->setCurrentIndex(tiponegocio-1);
    ui->grano->setCurrentIndex(tipograno-1);
    ui->moneda->setCurrentText(moneda);

    ui->tipo_negocio->setEnabled(false);
    ui->grano->setEnabled(false);
    ui->moneda->setEnabled(false);

    return this->exec();
}

int AgregarVenta::fillVentasFields(int id){

    this->setWindowTitle("Editar Venta");
    ui->aceptar->hide();
    ui->actualizar->show();

    QSqlQuery query;
    query.prepare("SELECT * FROM ventas WHERE _id = :id");
    query.bindValue(":id",id);
    query.exec();
    query.next();

    ui->num_contrato->setText(query.value(6).toString());
    ui->kilos->setText(query.value(8).toString());
    ui->fecha_venta->setDate(query.value(2).toDate());
    ui->fecha_cobro->setDate(query.value(3).toDate());
    ui->fecha_desde->setDate(query.value(4).toDate());
    ui->fecha_hasta->setDate(query.value(5).toDate());
    ui->tipo_negocio->setCurrentIndex(query.value(1).toInt()-1);
    ui->observaciones->setText(query.value(14).toString());
    ui->precio->setText(query.value(12).toString());

    ui->id->setText(query.value(0).toString());

    int indexCliente = ui->comprador->findData(query.value(7));
    ui->comprador->setCurrentIndex(indexCliente);

    int indexGrano = ui->grano->findData(query.value(11));
    ui->grano->setCurrentIndex(indexGrano);

    if(query.value(13).toString() == "Peso")
        ui->moneda->setCurrentIndex(0);
    else
        ui->moneda->setCurrentIndex(1);

    return (this->exec());
}

int AgregarVenta::actualizarVenta(){
    // validar venta
    if(validarVenta())
    {
        QSqlQuery query;

        query.prepare("UPDATE ventas SET "
                      "fechaventa = :fechaventa,fechacobro =:fechacobro, contrato=:contrato, comprador=:comprador,"
                      " kilos=:kilos, tipocereal=:tipocereal, precio=:precio, moneda=:moneda, observaciones=:observaciones,"
                      "fechadesde=:fechadesde,fechahasta=:fechahasta,tiponegocio=:tiponegocio"
                      " WHERE _id = :id ");

        query.bindValue(":fechaventa", ui->fecha_venta->date());
        query.bindValue(":fechacobro", ui->fecha_cobro->date());
        query.bindValue(":fechadesde", ui->fecha_desde->date());
        query.bindValue(":fechahasta", ui->fecha_hasta->date());
        query.bindValue(":contrato", ui->num_contrato->text().toDouble());
        query.bindValue(":comprador", ui->comprador->itemData(ui->comprador->currentIndex()).toDouble());
        query.bindValue(":kilos", ui->kilos->text().toDouble());
        query.bindValue(":tipocereal", ui->grano->itemData(ui->grano->currentIndex()).toInt());
        query.bindValue(":precio", ui->precio->text().toDouble());
        query.bindValue(":moneda", ui->moneda->currentText());
        query.bindValue(":observaciones", ui->observaciones->toPlainText());
        query.bindValue(":tiponegocio", ui->tipo_negocio->currentText().toInt());
        query.bindValue(":id", ui->id->text().toInt());

        int ret = query.exec();
        qDebug() << query.lastError();
        if(!ret)
            QMessageBox::warning(0, QObject::tr("Advertencia"),"Ha ocurrido un error, por favor inténtelo nuevamente");
        else
            this->accept();
        return ret;
    }
    return 0;

}

void AgregarVenta::nuevoComprador(){
    NuevoComprador *nuevocomprador = new NuevoComprador();
    int ret = nuevocomprador->exec();
    if(ret == 0)
    {
        ui->comprador->clear();
        populateCompradorField();
    }
}

void AgregarVenta::populateCompradorField(){
    QSqlQueryModel cliente;
    cliente.setQuery ("SELECT nombre,cuit FROM comprador ORDER BY nombre");

    for(int i=0; i < cliente.rowCount(); i++)
    {
        ui->comprador->addItem( cliente.data(cliente.index(i,0)).toString(), QVariant( cliente.data(cliente.index(i,1)).toDouble()));
    }
}

void AgregarVenta::populateCerealField(){
    QSqlQueryModel cereal;
    cereal.setQuery("SELECT cereal,id FROM cereales");
    for(int i=0; i < cereal.rowCount(); i++)
    {
        ui->grano->addItem( cereal.data(cereal.index(i,0)).toString(), QVariant( cereal.data(cereal.index(i,1)).toInt()));
    }
}

int AgregarVenta::validarVenta()
{
    QString error = "";
    int ret = 1;
    QString contrato = ui->num_contrato->text();
    if(contrato.length() == 0)
    {
        error.append("- Debe ingresar el numero de contrato\n");
        ret = 0;
    }
    QString precio = ui->precio->text();
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

    QDate fechaventa = ui->fecha_venta->date();
    QDate fechacobro = ui->fecha_cobro->date();

    if(fechaventa > fechacobro)
    {
        error.append("- Fecha venta debe ser menor a Fecha cobro \n");
        ret = 0;
    }

    QDate fechadesde = ui->fecha_desde->date();
    QDate fechahasta = ui->fecha_hasta->date();

    if(fechadesde >= fechahasta)
    {
        error.append("- Fecha desde debe ser menor a Fecha hasta \n");
        ret = 0;
    }

    if(fechadesde > fechaventa)
    {
        error.append("- Cheque que todas las fechas ingresadas sean correctas \n");
        ret = 0;
    }

    if(ret == 0)
        QMessageBox::warning(0, QObject::tr("Advertencia"),error);
    return ret;
}

void AgregarVenta::on_nuevo_comprador_clicked()
{
    nuevoComprador();
}

void AgregarVenta::on_cancelar_clicked()
{
    this->close();
}

void AgregarVenta::on_aceptar_clicked()
{
    agregarventa();
}

void AgregarVenta::on_actualizar_clicked()
{
    actualizarVenta();
}
