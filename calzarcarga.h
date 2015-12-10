#ifndef CALZARCARGA_H
#define CALZARCARGA_H

#include <QDialog>
#include <QModelIndex>
namespace Ui {
class CalzarCarga;
}

class CalzarCarga : public QDialog
{
    Q_OBJECT

public:
    explicit CalzarCarga(int id_carga, QWidget *parent = 0);
    ~CalzarCarga();

private slots:


    void on_compras_clicked(const QModelIndex &index);

    void on_ventas_clicked(const QModelIndex &index);

    void on_cancelar_clicked();

    void on_aceptar_clicked();

    void on_modificar_compra_clicked();

    void on_modificar_compra_2_clicked();

private:
    Ui::CalzarCarga *ui;
    void loadData(int id_carga);
    void loadCompras(QString cereal, int kilos);
    void loadVentas(QString cereal, int kilos);
    void loadCompraData(int id_compra);
    void loadVentaData(int id_venta);
    qlonglong clienteCarga;
    qlonglong clienteCompra;
    int prevCompra;
    int prevVenta;
    int idCarga;
    int kilosCarga;

};

#endif // CALZARCARGA_H
