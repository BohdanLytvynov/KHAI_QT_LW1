#ifndef TASK1BACK_H
#define TASK1BACK_H

#include <QObject>
#include<string>
#include<QDebug>
#include"monthes_qml_env.h"

typedef unsigned int uint;

class task1back : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool leapYear READ leapYear WRITE setleapYear NOTIFY leapYearChanged FINAL)
    Q_PROPERTY(QString error READ error WRITE setError NOTIFY errorChanged FINAL)
    Q_PROPERTY(monthes_qml_env::monthes month READ month WRITE setMonth NOTIFY monthChanged FINAL)

public:
    //Ctor convertor
    explicit task1back(QObject *parent = nullptr);

    //QML Invocable functions
    Q_INVOKABLE void calculate(QString dateInput);
    Q_INVOKABLE int getDay();
    Q_INVOKABLE bool isFail();
    //LeapYear Getter
    bool leapYear() const;

    //Month Getter Setter
    monthes_qml_env::monthes month() const;
    void setMonth(const monthes_qml_env::monthes &newMonth);

    //Error Getter Setter
    QString error() const;
    void setError(const QString &newError);

signals:

    void leapYearChanged();

    void errorChanged();

    void monthChanged();

public slots:

    void setleapYear(bool newLeapYear);

private:

    //State
    QString m_error;//Error happened during runtime
    bool m_fail;//Indicates wether operaion was succeded
    uint m_day;//calculated day
    monthes_qml_env::monthes m_month;//calculated month
    bool m_leapYear;//wether year is leap

    //private functions

    //Trys to parse string in uint format to the uint
    bool TryParseToUINt(const std::string &input, uint& out, std::string& error);

    monthes_qml_env::monthes ConvertToMonthes(uint month_number);


};

#endif // TASK1BACK_H
