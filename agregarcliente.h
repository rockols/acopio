#ifndef AGREGARCLIENTE_H
#define AGREGARCLIENTE_H

#include <QDialog>

namespace Ui {
class AgregarCliente;
}

class AgregarCliente : public QDialog
{
    Q_OBJECT

public:
    explicit AgregarCliente(QWidget *parent = 0);
    ~AgregarCliente();

private slots:
    void on_aceptar_clicked();

    void on_cancelar_clicked();

private:
    Ui::AgregarCliente *ui;
    int validarFormulario();
    QString ucfirst(const QString str);
};

#endif // AGREGARCLIENTE_H
