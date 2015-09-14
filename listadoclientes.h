#ifndef LISTADOCLIENTES_H
#define LISTADOCLIENTES_H

#include <QWidget>

namespace Ui {
class ListadoClientes;
}

class ListadoClientes : public QWidget
{
    Q_OBJECT

public:
    explicit ListadoClientes(QWidget *parent = 0);
    ~ListadoClientes();

private:
    Ui::ListadoClientes *ui;
    void mostrarClientes();
};

#endif // LISTADOCLIENTES_H
