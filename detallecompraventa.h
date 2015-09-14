#ifndef DETALLECOMPRAVENTA_H
#define DETALLECOMPRAVENTA_H

#include <QDialog>

namespace Ui {
class DetalleCompraVenta;
}

class DetalleCompraVenta : public QDialog
{
    Q_OBJECT

public:
    explicit DetalleCompraVenta(int idCompra, int idVenta, QWidget *parent = 0);
    ~DetalleCompraVenta();

private:
    Ui::DetalleCompraVenta *ui;
    void showDetalles(int idCompra,int idVenta);
    void populateCerealField();
    void populateClienteField();
    void populateLocalizacionField();
};

#endif // DETALLECOMPRAVENTA_H
