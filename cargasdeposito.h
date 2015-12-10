#ifndef CARGASDEPOSITO_H
#define CARGASDEPOSITO_H

#include <QDialog>

namespace Ui {
class CargasDeposito;
}

class CargasDeposito : public QDialog
{
    Q_OBJECT

public:
    explicit CargasDeposito(QWidget *parent = 0);
    ~CargasDeposito();

private slots:
    void on_deposito_clicked();

    void on_salir_clicked();

    void on_asociar_clicked();

private:
    Ui::CargasDeposito *ui;
    void loadData();
};

#endif // CARGASDEPOSITO_H
