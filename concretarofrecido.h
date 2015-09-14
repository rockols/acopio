#ifndef CONCRETAROFRECIDO_H
#define CONCRETAROFRECIDO_H

#include <QDialog>

namespace Ui {
class ConcretarOfrecido;
}

class ConcretarOfrecido : public QDialog
{
    Q_OBJECT

public:
    explicit ConcretarOfrecido(QWidget *parent = 0);
    int concretar(int id);
    int nuevaCompra();
    int modificar(int id);

private slots:
    void on_pushButton_2_clicked();
    int on_pushButton_clicked();
    void on_cliente_currentIndexChanged();
    void on_pushButton_3_clicked();
    int on_pushButton_4_clicked();

private:
    Ui::ConcretarOfrecido *ui;
    void populateClienteField();
    void populateCerealField();
    int validarCompra();
    void populateLocalizacionField();
    void nuevoCliente();
    int insertCompra();
    int updateCompra();
};

#endif // CONCRETAROFRECIDO_H
