#ifndef AGREGARVENTA_H
#define AGREGARVENTA_H

#include <QDialog>

namespace Ui {
class AgregarVenta;
}

class AgregarVenta : public QDialog
{
    Q_OBJECT

public:
    explicit AgregarVenta(QWidget *parent = 0);
    ~AgregarVenta();
    int agregarventa(int tipograno, int tiponegocio, QString moneda );
    int fillVentasFields(int id);

private slots:
    void on_nuevo_comprador_clicked();

    void on_cancelar_clicked();

    void on_aceptar_clicked();

    void on_actualizar_clicked();

private:
    Ui::AgregarVenta *ui;
    void nuevoComprador();
    void agregarventa();
    void populateCompradorField();
    void populateCerealField();
    int validarVenta();
    int actualizarVenta();



};

#endif // AGREGARVENTA_H
