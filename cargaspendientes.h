#ifndef CARGASPENDIENTES_H
#define CARGASPENDIENTES_H

#include <QDialog>

namespace Ui {
class CargasPendientes;
}

class CargasPendientes : public QDialog
{
    Q_OBJECT

public:
    explicit CargasPendientes(QWidget *parent = 0);
    ~CargasPendientes();

private slots:
    void on_pushButton_clicked();

    void on_contratosVenta_clicked();

private:
    Ui::CargasPendientes *ui;
    void loadPendientes();
    void Imprimir();
};

#endif // CARGASPENDIENTES_H
