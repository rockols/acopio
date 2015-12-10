#ifndef AGREGAROFRECIDO_H
#define AGREGAROFRECIDO_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class AgregarOfrecido;
}

class AgregarOfrecido : public QDialog
{
    Q_OBJECT

public:
    explicit AgregarOfrecido(QWidget *parent = 0);
    int editarOfrecido(int id);
    ~AgregarOfrecido();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    int on_pushButton_8_clicked();

private:
    Ui::AgregarOfrecido *ui;
    QSqlDatabase db;
    int validarOfrecido();
};

#endif // AGREGAROFRECIDO_H
