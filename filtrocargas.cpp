#include "filtrocargas.h"
#include "ui_filtrocargas.h"
#include "carga.h"

filtroCargas::filtroCargas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::filtroCargas)
{
    ui->setupUi(this);
    ui->fecha_desde->setDate(QDate::currentDate());
    ui->fecha_hasta->setDate(QDate::currentDate());
    this->setWindowTitle("Filtrar Cargas");
}

filtroCargas::~filtroCargas()
{
    delete ui;
}

void filtroCargas::on_pushButton_2_clicked()
{
    this->close();
}

void filtroCargas::on_aceptar_clicked()
{
    this->close();

    Carga *cargas = new Carga(ui->fecha_desde->date(),ui->fecha_hasta->date());
    cargas->exec();
}
