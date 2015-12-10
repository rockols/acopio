#include "helper.h"
#include <QSqlQueryModel>
#include <QDate>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

Helper::Helper(){}

void Helper::populateCerealField(QComboBox *box){
    QSqlQueryModel cereal;
    cereal.setQuery("SELECT cereal,id FROM cereales");
    for(int i=0; i < cereal.rowCount(); i++)
    {
        box->addItem( cereal.data(cereal.index(i,0)).toString(), QVariant( cereal.data(cereal.index(i,1)).toInt()));
    }
}


void Helper::populateClienteField(QComboBox *box){
    QSqlQueryModel cliente;
    cliente.setQuery ("SELECT nombre,cuit FROM cliente ORDER BY nombre");

    for(int i=0; i < cliente.rowCount(); i++)
    {
        box->addItem( cliente.data(cliente.index(i,0)).toString(), QVariant( cliente.data(cliente.index(i,1)).toDouble()));
    }
}


void Helper::populateCosechaField(QComboBox *box){
    int year = QDate::currentDate().year()%100;

    for(int i = year-3; i < year+3; i++){
        QString cosecha;
        cosecha.append(QString::number(i)).append("/").append(QString::number(i+1));
        box->addItem(cosecha,QVariant(cosecha));
    }
}


void Helper::populateLocalizacionField(QComboBox *box)
{
    box->clear();
    QSqlQuery query;
    query.prepare("SELECT id, lugar FROM localizacion");
    query.exec();
    QSqlQueryModel campos;
    campos.setQuery(query);

    for(int i=0; i < campos.rowCount(); i++)
    {
        box->addItem( campos.data(campos.index(i,1)).toString(), campos.data(campos.index(i,0)).toInt());
    }
}

