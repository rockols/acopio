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

private slots:
    void on_nuevocliente_clicked();

    void on_eliminar_clicked();

    void on_tableView_clicked();

private:
    Ui::ListadoClientes *ui;
    void mostrarClientes();
    void enableButtons();
    void disableButtons();
    void eliminarCliente();
};

#endif // LISTADOCLIENTES_H
