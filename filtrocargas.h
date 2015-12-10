#ifndef FILTROCARGAS_H
#define FILTROCARGAS_H

#include <QDialog>

namespace Ui {
class filtroCargas;
}

class filtroCargas : public QDialog
{
    Q_OBJECT

public:
    explicit filtroCargas(QWidget *parent = 0);
    ~filtroCargas();

private slots:
    void on_pushButton_2_clicked();

    void on_aceptar_clicked();

private:
    Ui::filtroCargas *ui;
};

#endif // FILTROCARGAS_H
