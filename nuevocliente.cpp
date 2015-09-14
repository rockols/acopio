#include "nuevocliente.h"
#include "ui_nuevocliente.h"

NuevoCliente::NuevoCliente(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NuevoCliente)
{
    ui->setupUi(this);
}

NuevoCliente::~NuevoCliente()
{
    delete ui;
}
