#ifndef VECT_ERROR_H
#define VECT_ERROR_H
#include "QString"

class vect_error
{
public:
    QString error;
    vect_error(QString err){ error = err;};
};

#endif // VECT_ERROR_H
