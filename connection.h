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
               "concretado       INT           DEFAULT 0,"
               "kilosprestados   INT           DEFAULT 0)"
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

    //CEREALES
    query.exec("create table cereales (id int primary key, "
               "cereal varchar(20))");
    query.exec("insert into cereales values(1, 'Soja')");
    query.exec("insert into cereales values(2, 'Trigo')");
    query.exec("insert into cereales values(3, 'Sorgo')");
    query.exec("insert into cereales values(4, 'Maiz')");

    //CLIENTE
    query.exec("CREATE TABLE cliente (id INTEGER PRIMARY KEY AUTOINCREMENT, cuit int UNIQUE, nombre varchar (40), direccion varchar (40), localidad varchar (25), provincia varchar (20), telefono varchar (30), mail varchar (30))");
    query.exec("insert into cliente values(302012,'Trucone','Jonas Salk 1200','Pozo del Molle','0353-15640080','pepe@gmail.com','cba')");
    query.exec("insert into cliente values(12341,'Forlin','Peru 200','Laspiur','0351-15640121','rocko2@gmail.com','sta fe')");

    //COMPRADOR
    query.exec("create table comprador (cuit int primary key, "
               "nombre varchar(40), direccion varchar(40),localidad varchar(25),telefono varchar(30),mail varchar(30),provincia varchar(20))");
    query.exec("insert into cliente values(302012,'GyT','Jonas Salk 1200','Pozo del Molle','0353-15640080','pepe@gmail.com','cba')");

    //Localizaciones
    query.exec("CREATE TABLE localizacion (id INTEGER PRIMARY KEY, lugar varchar (255));");
    query.exec("insert into localizacion values(1,'Planta')");
    query.exec("insert into localizacion values(2,'Campo')");

    //CARGAS
    query.exec("CREATE TABLE cargas (_id INTEGER PRIMARY KEY NOT NULL, "
               "fecha DATE, "
               "grano INTEGER, "
               "cosecha INTEGER, "
               "kilos INTEGER, "
               "lugar_carga VARCHAR, "
               "carta_porte INTEGER, "
               "tipo INTEGER, "
               "cliente INT DEFAULT (NULL), "
               "tarifa_cobrar INTEGER, "
               "tarifa_pagar INTEGER, "
               "se_paga INTEGER DEFAULT (0), "
               "se_cobra INTEGER DEFAULT (0), "
               "pagado INTEGER DEFAULT (0), "
               "cobrado INTEGER DEFAULT (0), "
               "transportista INTEGER DEFAULT (0), "
               "observaciones TEXT, "
               "origen INTEGER REFERENCES compras (_id) ON DELETE SET DEFAULT DEFAULT (0), "
               "destino INTEGER REFERENCES ventas (_id) ON DELETE SET DEFAULT DEFAULT (0), "
               "en_deposito INTEGER DEFAULT (0))");

    // FLETES
    query.exec("CREATE TABLE flete (_id INTEGER PRIMARY KEY  NOT NULL ,"
               "fecha DATE,"
               "c_porte INTEGER,"
               "pagado INTEGER,"
               "tarifa INTEGER,"
               "kilos INTEGER,"
               "transportista INTEGER DEFAULT (null) ,"
               "observaciones TEXT)");


    //REL COMPRA-VENTA
    query.exec("CREATE TABLE rel_compra_venta ("
    "_id       INTEGER PRIMARY KEY AUTOINCREMENT,"
    "id_compra INT     REFERENCES compras (_id),"
    "id_venta  INT     REFERENCES ventas (_id),"
    "kilos     INT     NOT NULL)");

    // TRANSPORTISTA
    query.exec("CREATE TABLE transportista (cuit INTEGER PRIMARY KEY  NOT NULL ,"
               "nombre VARCHAR,"
               "direccion VARCHAR,"
               "localidad VARCHAR,"
               "provincia VARCHAR,"
               "telefono INTEGER,"
               "transporte VARCHAR)");

    //BOOLEAN
    query.exec("CREATE TABLE boolean (id PRIMARY KEY, name)");
    query.exec("insert into boolean values(0, 'No')");
    query.exec("insert into boolean values(1, 'Si')");

    //TIPO OPERACION
    query.exec("CREATE TABLE tipo_operacion (id  INTEGER PRIMARY KEY, name INTEGER)");
    query.exec("insert into tipo_operacion values(1, 1)");
    query.exec("insert into tipo_operacion values(2, 2)");

    // CARGAS PENDIENTES
    query.exec("CREATE VIEW cargasPendientes AS SELECT cliente, nombre, cereal, grano, SUM(kilos) AS kilos FROM (SELECT * FROM cargasTotales UNION SELECT * FROM pendientesCompra) AS C JOIN cliente AS Cli ON C.cliente = Cli.cuit JOIN cereales AS Ce ON C.grano = Ce.id GROUP BY C.cliente, C.grano ORDER BY C.cliente, C.grano");

    query.exec("CREATE VIEW cargasTotales AS SELECT cliente,grano,-1*SUM(kilos) AS kilos FROM cargas WHERE en_deposito=0 GROUP BY cliente,grano");
    query.exec("CREATE VIEW pendientesCompra AS SELECT cliente,tipocereal,SUM(kilosconcretados) AS kilos FROM compras GROUP BY cliente, tipocereal");
    query.exec("CREATE VIEW pendientesVenta AS SELECT C.cuit,C.nombre,Ce.cereal,SUM(kilos - kiloscumplidos) AS kilos FROM ventas AS V JOIN comprador AS C ON V.comprador = C.cuit JOIN cereales AS Ce ON V.tipocereal = Ce.id GROUP BY V.comprador, V.tipocereal ORDER BY V.comprador, V.tipocereal");

}
#endif // CONNECTION_H

