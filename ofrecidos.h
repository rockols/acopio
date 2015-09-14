#ifndef OFRECIDOS_H
#define OFRECIDOS_H

#include <QWidget>
#include <QSqlRelationalDelegate>

namespace Ui {
class Ofrecidos;
}

class Ofrecidos : public QWidget
{
    Q_OBJECT

public:
    explicit Ofrecidos(QWidget *parent = 0);

private slots:
    void on_nuevoOfrecido_clicked();
    void on_eliminarOfrecido_clicked();
    void on_ofrecidosList_clicked();
    void on_modificarOfrecido_clicked();
    void on_ofrecidosList_doubleClicked();
    void on_concretarOfrecido_clicked();

private:
    Ui::Ofrecidos *ui;
    void showOfrecidos();
    void newOfrecido();
    void eliminarOfrecido();
    void disableButtons();
    void enableButtons();
    void modifyOfrecido();
    void ConcOfrecido();

};

#endif // OFRECIDOS_H
