#ifndef COMPRAS_H
#define COMPRAS_H

#include <QWidget>

namespace Ui {
class Compras;
}

class Compras : public QWidget
{
    Q_OBJECT

public:
    explicit Compras(QWidget *parent = 0);

private slots:
    void on_nuevaCompra_clicked();
    void on_comprasList_clicked();
    void on_eliminarCompra_clicked();
    void on_modificarCompra_clicked();
    void on_vincularCompra_clicked();
    void on_comprasList_doubleClicked();

private:
    Ui::Compras *ui;
    void showCompras();
    void nuevaCompra();
    void enableButtons();
    void disableButtons();
    void deleteCompra();
    void modifyCompra();
    void vincCompra();

};

#endif // COMPRAS_H
