#ifndef AGREGARCARGA_H
#define AGREGARCARGA_H

#include <QDialog>

namespace Ui {
class AgregarCarga;
}

class AgregarCarga : public QDialog
{
    Q_OBJECT

public:
    explicit AgregarCarga(QWidget *parent = 0);
    ~AgregarCarga();

private slots:
    void on_aceptar_clicked();
    void on_cancelar_clicked();
    void on_cliente_currentIndexChanged();

private:
    Ui::AgregarCarga *ui;
    bool validarCarga();
    bool chequearCompra(qlonglong cliente, int grano);
    int guardar();
    void guardarYcalzar();
};

#endif // AGREGARCARGA_H
