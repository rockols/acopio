#ifndef HELPER_H
#define HELPER_H

#include <QComboBox>

class Helper
{
public:
    Helper();
    static void populateCerealField(QComboBox *box);
    static void populateClienteField(QComboBox *box);
    static void populateCosechaField(QComboBox *box);
    static void populateLocalizacionField(QComboBox *box);


signals:

public slots:
};

#endif // HELPER_H
