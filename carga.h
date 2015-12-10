#ifndef CARGA_H
#define CARGA_H

#include <QDialog>
#include <QDate>

namespace Ui {
class Carga;
}

class Carga : public QDialog
{
    Q_OBJECT

public:
    explicit Carga(QDate start, QDate end, QWidget *parent = 0);
    ~Carga();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_cargas_clicked();

    void on_asociar_clicked();

private:
    Ui::Carga *ui;
    void loadCargas(QDate start, QDate end);
    void eliminarCarga(int id);
    int pendiente;
    QDate start;
    QDate end;
};

#endif // CARGA_H
