#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
static void createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("acopio.sqlite");
    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);

    }

    QSqlQuery query;
    //COMPRAS
 //   query.exec("create table compras (_id INTEGER PRIMARY KEY AUTOINCREMENT, "
   //            "fechaingreso date,fechacompra date, precio int, tipocereal int, tiponegocio int, concretado int DEFAULT 0,cliente int, fechaconcretado date, kilos int DEFAULT 0,observaciones varchar(255),moneda varchar(25), prioridad int, precioconcretado int, kilosconcretados int, localizacion int, fechapago date, kiloscalzados int DEFAULT 0, kilosentregados int DEFAULT 0 )");

    query.exec("CREATE TABLE compras ("
               "_id              INTEGER       PRIMARY KEY,"
               "prioridad        INT,"
               "fechaingreso     DATE,"
               "fechacompra      DATE,"
               "fechaconcretado  DATE,"
               "fechapago        DATE,"
               "tiponegocio      INT           NOT NULL,"
               "tipocereal       INT           NOT NULL,"
               "precio           INT,"
               "precioconcretado INT,"
               "moneda           VARCHAR (25),"
               "kilos            INT           DEFAULT 0 NOT NULL,"
               "kilosconcretados INT,"
               "kiloscalzados    INT           DEFAULT 0,"
               "kilosentregados  INT           DEFAULT 0,"
               "cliente          INT           NOT NULL,"
               "localizacion     INT,"
               "observaciones    VARCHAR (255),"
               "concretado       INT           DEFAULT 0)"
    );

    //VENTAS
    query.exec("CREATE TABLE ventas ("
               "'_id' INTEGER       PRIMARY KEY,"
               "'tiponegocio'         INT,"
               "'fechaventa'        DATE,"
               "'fechacobro'        DATE,"
               "'fechadesde'        DATE,"
               "'fechahasta'        DATE,"
               "'contrato'          INTEGER,"
               "'comprador'         INT,"
               "'kilos'             INT NOT NULL,"
               "'kiloscalzados'     INT,"
               "'kiloscumplidos'    INT DEFAULT ('0'),"
               "'tipocereal'        INTEGER,"
               "'precio'            INT NOT NULL,"
               "'moneda'            VARCHAR(25),"
               "'observaciones'     VARCHAR(255))"
     );


    //CALZADOS
    query.exec("CREATE TABLE calzados ("
    "_id       INTEGER PRIMARY KEY AUTOINCREMENT,"
    "id_compra INT     REFERENCES compras (_id),"
    "id_venta  INT     REFERENCES ventas (_id),"
    "kilos     INT     NOT NULL)");

    //CEREALES
    query.exec("create table cereales (id int primary key, "
               "cereal varchar(20))");
    query.exec("insert into cereales values(1, 'Soja')");
    query.exec("insert into cereales values(2, 'Trigo')");
    query.exec("insert into cereales values(3, 'Sorgo')");
    query.exec("insert into cereales values(4, 'Maiz')");

    //CLIENTE
    query.exec("create table cliente (cuit int primary key, "
               "nombre varchar(40), direccion varchar(40),localidad varchar(25),telefono varchar(30),mail varchar(30),provincia varchar(20))");
    query.exec("insert into cliente values(302012,'Trucone','Jonas Salk 1200','Pozo del Molle','0353-15640080','pepe@gmail.com','cba')");
    query.exec("insert into cliente values(12341,'Forlin','Peru 200','Laspiur','0351-15640121','rocko2@gmail.com','sta fe')");

    //COMPRADOR
    query.exec("create table comprador (cuit int primary key, "
               "nombre varchar(40), direccion varchar(40),localidad varchar(25),telefono varchar(30),mail varchar(30),provincia varchar(20))");
    query.exec("insert into cliente values(302012,'GyT','Jonas Salk 1200','Pozo del Molle','0353-15640080','pepe@gmail.com','cba')");

    //Localizaciones
    query.exec("create table localizacion (_id INTEGER PRIMARY KEY, "
               "cliente int, lugar varchar(255) )");
    query.exec("insert into localizacion values(0,0,'')");
    query.exec("insert into localizacion values(1,0,'Planta')");
}
#endif // CONNECTION_H

