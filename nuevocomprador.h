#ifndef NUEVOCOMPRADOR_H
#define NUEVOCOMPRADOR_H

#include <QDialog>

namespace Ui {
class NuevoComprador;
}

class NuevoComprador : public QDialog
{
    Q_OBJECT

public:
    explicit NuevoComprador(QWidget *parent = 0);
    ~NuevoComprador();

private slots:
    void on_cancelar_clicked();

    void on_aceptar_clicked();

private:
    Ui::NuevoComprador *ui;
    QString ucfirst(const QString str);
    int validarFormulario();
    void guardarComprador();
};

#endif // NUEVOCOMPRADOR_H
