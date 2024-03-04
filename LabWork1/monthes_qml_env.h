#ifndef MONTHES_QML_ENV_H
#define MONTHES_QML_ENV_H

#include "qobjectdefs.h"
#include "qtmetamacros.h"
class monthes_qml_env
{
    Q_GADGET

public:
    monthes_qml_env();

    enum struct monthes
    {
        January = 1, February, March, April, May, June, July, August, September, October, November,
        December, Undefined
    };

    Q_ENUM(monthes)
};

#endif // MONTHES_QML_ENV_H
