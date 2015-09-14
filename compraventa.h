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
    explicit CompraVenta(int id_compra, QString grano, QWidget *parent = 0);
    ~CompraVenta();

private slots:
    void on_vincular_clicked();

    void on_ventasList_doubleClicked();

    void on_ventasList_clicked(const QModelIndex &index);

    void on_nueva_venta_clicked();

private:
    Ui::CompraVenta *ui;
    void showVentas(QString grano);
    void vincularCompraVenta();
    int idCompra;
};

#endif // COMPRAVENTA_H
