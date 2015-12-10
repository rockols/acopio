#include "agregarcliente.h"
#include "ui_agregarcliente.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlQuery>

AgregarCliente::AgregarCliente(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AgregarCliente)
{
    ui->setupUi(this);
    this->setWindowTitle("Nuevo Cliente");
    ui->telefono->setValidator(new QDoubleValidator(0, 100,2, this));
    ui->cuit->setValidator(new QIntValidator(0, 100000000, this));
    ui->cuit0->setValidator(new QIntValidator(0, 100, this));
    ui->cuit1->setValidator(new QIntValidator(0, 10, this));
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
}

AgregarCliente::~AgregarCliente()
{
    delete ui;
}



void AgregarCliente::on_aceptar_clicked()
{
    if(validarFormulario() == 1)
    {
        QString nombre = ui->nombre->text();
        QString apellido = ui->apellido->text();
        QString cuit = ui->cuit0->text().append(ui->cuit->text()).append(ui->cuit1->text());
        QString email = ui->mail->text();
        QString direccion = ui->direccion->text();
        QString localidad = ui->localidad->text();
        QString provincia = ui->provincia->text();
        QString telefono = ui->telefono->text();
        //QString campos = ui->campos->text();

        QSqlQuery query;
        query.prepare("insert into cliente (cuit, nombre, direccion, localidad, telefono ,mail ,provincia) "
                      "values(:cuit,:nombre, :direccion, :localidad, :telefono, :mail, :provincia)");
        query.bindValue(":cuit", cuit.toDouble());
        query.bindValue(":nombre", ucfirst(nombre.append(" ").append(apellido)));
        query.bindValue(":direccion", ucfirst(direccion));
        query.bindValue(":localidad", ucfirst(localidad));
        query.bindValue(":telefono", telefono);
        query.bindValue(":mail", email);
        query.bindValue(":provincia", ucfirst(provincia));
        if(!query.exec())
        {
            QMessageBox::warning(0, QObject::tr("Error"),"Ha ocurrido un error, por favor verifique que el "
                                                         "CUIT ingresado no exista en la base de datos");
            return;
        }
        /*else if(campos.size()>0)
        {
            query.clear();
            QStringList c = campos.split(',');
            foreach (QString campo, c) {
                query.prepare("insert into localizacion (cliente,lugar) "
                              "values(:cliente,:lugar)");
                query.bindValue(":cliente", cuit.toDouble());
                query.bindValue(":lugar", ucfirst(campo));
                if(!query.exec())
                {
                    QMessageBox::warning(0, QObject::tr("Error"),"Ha ocurrido un error al ingresar los campos del clientes ");
                    return;
                }
            }
        }*/

    QMessageBox msgBox;
    msgBox.setText("La operación se ha realizado con éxito");
    msgBox.setWindowTitle("Info");
    int ret = msgBox.exec();
    if(ret > 0)
        this->close();
    }
}

int AgregarCliente::validarFormulario(){

    QString error = "";
    int ret = 1;

    QString nombre = ui->nombre->text();
    if(nombre.count()==0)
    {
        error.append("- Debe ingresar el nombre del cliente\n");
        ret = 0;
    }

    QString apellido = ui->apellido->text();
    if(apellido.count()==0)
    {
        error.append("- Debe ingresar el apellido del cliente\n");
        ret = 0;
    }

    QString cuit = ui->cuit0->text().append(ui->cuit->text()).append(ui->cuit1->text());

    if(cuit.toDouble() == 0)
    {
        error.append("- Debe ingresar el CUIT del cliente\n");
        ret = 0;

    }
    else if(cuit.size() < 11)
    {
        error.append("- Verifique que el CUIT ingresado sea correcto\n");
        ret = 0;
    }

    QString strPatt = "\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}\\b";
    QString email = ui->mail->text();
    QRegExp rx(strPatt);
    if(email.length() > 0 && !rx.exactMatch(email))
    {
        error.append("- Verifique que el correo electrónico ingresado sea correcto\n");
        ret = 0;
    }

    if(ret == 0)
        QMessageBox::warning(0, QObject::tr("Advertencia"),error);

    return ret;

}

void AgregarCliente::on_cancelar_clicked()
{
    this->close();
}

QString AgregarCliente::ucfirst(const QString str) {
    if (str.size() < 1) {
        return "";
    }

    QStringList tokens = str.split(" ");
    QList<QString>::iterator tokItr = tokens.begin();

    for (tokItr = tokens.begin(); tokItr != tokens.end(); ++tokItr) {
        (*tokItr) = (*tokItr).at(0).toUpper() + (*tokItr).mid(1);
    }

    return tokens.join(" ");
}
