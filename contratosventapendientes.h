#ifndef CONTRATOSVENTAPENDIENTES_H
#define CONTRATOSVENTAPENDIENTES_H

#include <QDialog>

namespace Ui {
class contratosVentaPendientes;
}

class contratosVentaPendientes : public QDialog
{
    Q_OBJECT

public:
    explicit contratosVentaPendientes(QWidget *parent = 0);
    ~contratosVentaPendientes();

private:
    Ui::contratosVentaPendientes *ui;
    void loadData();
};

#endif // CONTRATOSVENTAPENDIENTES_H
