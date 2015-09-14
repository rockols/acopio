#ifndef VENTAS_H
#define VENTAS_H

#include <QWidget>

namespace Ui {
class Ventas;
}

class Ventas : public QWidget
{
    Q_OBJECT

public:
    explicit Ventas(QWidget *parent = 0);
    ~Ventas();

private slots:
    void on_nuevaVenta_clicked();

    void on_ventasList_clicked();

    void on_eliminarVenta_clicked();

    void on_modificarVenta_clicked();

    void on_vincularVenta_clicked();

private:
    Ui::Ventas *ui;
    void showVentas();
    void agregarVenta();
    void disableButtons();
    void enableButtons();
    void eliminarVenta();
    void vincularVenta();
    void modificarVenta();


};

#endif // VENTAS_H
