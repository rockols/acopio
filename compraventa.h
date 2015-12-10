#ifndef COMPRAVENTA_H
#define COMPRAVENTA_H

#include <QDialog>

namespace Ui {
class CompraVenta;
}

class CompraVenta : public QDialog
{
    Q_OBJECT

public:
    explicit CompraVenta(int id_compra, QWidget *parent = 0);
    ~CompraVenta();

private slots:
    void on_vincular_clicked();

    void on_ventasList_doubleClicked();

    void on_ventasList_clicked();

    void on_nueva_venta_clicked();

    void on_pushButton_clicked();

private:
    Ui::CompraVenta *ui;
    void showVentas();
    void vincularCompraVenta();
    int idCompra;
};

#endif // COMPRAVENTA_H
