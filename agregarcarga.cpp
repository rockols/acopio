#include "agregarcarga.h"
#include "ui_agregarcarga.h"
#include "helper.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQueryModel>
#include "calzarcarga.h"
#include "concretarofrecido.h"

AgregarCarga::AgregarCarga(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AgregarCarga)
{
    ui->setupUi(this);
    this->setWindowTitle("Nueva Carga");
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    Helper::populateCerealField(ui->grano);
    Helper::populateCosechaField(ui->cosecha);
    Helper::populateClienteField(ui->cliente);
    this->ui->fecha->setDate(QDate::currentDate());
    this->ui->kilos->setValidator(new QIntValidator(0, 100000, this));
    this->ui->cPorte->setValidator(new QIntValidator(0, 10000000000, this));
}

int AgregarCarga::guardar(){
    if(validarCarga())
    {
        QSqlQuery query;

        query.prepare("insert into cargas (fecha, grano, cosecha, kilos, lugar_carga, tipo, observaciones, en_deposito, cliente, carta_porte) "
                                 "values(:fecha,:grano,:cosecha, :kilos, :lugar_carga, :tipo, :observaciones, :deposito, :cliente, :carta_porte)");
        query.bindValue(":fecha", ui->fecha->date());
        query.bindValue(":grano", ui->grano->itemData(ui->grano->currentIndex()).toInt());
        query.bindValue(":cosecha", ui->cosecha->currentText());
        query.bindValue(":kilos", ui->kilos->text().toDouble());
        query.bindValue(":lugar_carga",  ui->origen->itemData(ui->origen->currentIndex()).toInt());
        query.bindValue(":tipo", ui->tipo->currentText().toInt());
        query.bindValue(":observaciones", ui->observaciones->toPlainText());
        query.bindValue(":deposito", 1);
        query.bindValue(":cliente", ui->cliente->itemData(ui->cliente->currentIndex()).toLongLong());
        query.bindValue(":carta_porte", ui->cPorte->text().toLongLong());
        if(!query.exec())
        {
            QMessageBox::warning(0, QObject::tr("Advertencia"),"Ha ocurrido un error, por favor inténtelo nuevamente");
            return -1;
        }
        else
        {
            this->accept();
            return query.lastInsertId().toInt();
        }
    }
    return -1;
}

/**
Chequea si existe un contrato de compra asociada al cliente para la carga realizada
**/
bool AgregarCarga::chequearCompra(qlonglong cliente, int grano)
{
    QSqlQueryModel compras;
    QString query = "SELECT * FROM compras WHERE cliente= " + QString::number(cliente) + " AND kilosconcretados-kilosentregados > 0 AND tipocereal = " + QString::number(grano);
    compras.setQuery(query);

    if(compras.rowCount() > 0)
        return true;
    else
        return false;
}

bool AgregarCarga::validarCarga()
{
    bool ret = true;
    QString error = "";
    if(ui->kilos->text().length() == 0){
        error.append("- Debe ingresar la cantidad de kilos");
        ret = false;
    }

    if(!ret)
        QMessageBox::warning(0, QObject::tr("Advertencia"),error);
    return ret;
}

AgregarCarga::~AgregarCarga()
{
    delete ui;
}

void AgregarCarga::on_aceptar_clicked()
{
    if(ui->deposito->isChecked())
        guardar();
    else
    {
        qlonglong cliente = ui->cliente->itemData(ui->cliente->currentIndex()).toLongLong();
        int grano = ui->grano->itemData(ui->grano->currentIndex()).toInt();

        if(!chequearCompra(cliente, grano) && validarCarga())
        {
            // PREGUNTAR SI SE QUIERE REALIZAR CONTRATO DE COMPRA
            QMessageBox msgBox;
            QString message = "No existe contrato de compra para ";
            message.append(ui->cliente->currentText());
            message.append(". Desea crear un nuevo contrato?");
            msgBox.setText(message);
            msgBox.setWindowTitle("Nueva Carga");
            msgBox.addButton("Aceptar", QMessageBox::YesRole);
            msgBox.addButton("Cancelar", QMessageBox::NoRole);
            msgBox.setIcon(QMessageBox::Question);

            int ret = msgBox.exec();
            int exits;
            ConcretarOfrecido *nuevacompra = new ConcretarOfrecido();

            switch(ret){
                case 0:
                    exits = nuevacompra->nuevaCompra(cliente,grano);
                    if(exits)
                        guardarYcalzar();
                    else
                        QMessageBox::warning(0, QObject::tr("Error"),"Ha ocurrido un error, por favor intentelo de nuevo.");
                    break;
                 case 1:
                    guardarYcalzar();
                break;
            }
        }
        else
           guardarYcalzar();

    }
}

void AgregarCarga::on_cancelar_clicked()
{
    this->close();
}

void AgregarCarga::on_cliente_currentIndexChanged()
{
    Helper::populateLocalizacionField(ui->origen);
}


void AgregarCarga::guardarYcalzar()
{
    int id = guardar();
    if(id != -1){
        CalzarCarga *carga = new CalzarCarga(id);
        carga->exec();
    }
}
