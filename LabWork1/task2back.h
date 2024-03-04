#ifndef TASK2BACK_H
#define TASK2BACK_H

#include <QObject>
#include <QRegularExpression>
#include"sort_algorithms.h"
#include<string>

class task2back : public QObject
{
    Q_OBJECT

    //QProperties Macros
    //Mode
    Q_PROPERTY(int mode READ mode WRITE setMode NOTIFY modeChanged FINAL)
    //Error Input
    Q_PROPERTY(QString arrInputError READ arrInputError WRITE setArrInputError NOTIFY arrInputErrorChanged FINAL)

    //Calculation result
    Q_PROPERTY(QString calcResult READ calcResult WRITE setCalcResult NOTIFY calcResultChanged FINAL)

    //Errors that can happen during input of min max and element count values
    Q_PROPERTY(QString minFieldError READ minFieldError WRITE setMinFieldError NOTIFY minFieldErrorChanged FINAL)
    Q_PROPERTY(QString maxFieldError READ maxFieldError WRITE setMaxFieldError NOTIFY maxFieldErrorChanged FINAL)
    Q_PROPERTY(QString elemCountFieldError READ elemCountFieldError WRITE setElemCountFieldError NOTIFY elemCountFieldErrorChanged FINAL)

    //Generation result
    Q_PROPERTY(QString genResult READ genResult WRITE setGenResult NOTIFY genResultChanged FINAL)
public:
    //Main ctor
    explicit task2back(QObject *parent = nullptr);

    //Q_INVOKABLE functions
    Q_INVOKABLE void setArray(const QString& strArray);
    Q_INVOKABLE void calculate();

    //Q_INVOKABLE Functions for Array generator
    Q_INVOKABLE void setMin(const QString& min);
    Q_INVOKABLE void setMax(const QString& max);
    Q_INVOKABLE void setElementCount(const QString& elemCount);
    Q_INVOKABLE void generateArray();
    Q_INVOKABLE bool failStatus();
    Q_INVOKABLE bool arrayGenerated();

    //Destructor
    ~task2back();

    //Error message

    //Mode of the task 1 - manual fill 2 - random generation
    int mode() const;


    QString arrInputError() const;
    void setArrInputError(const QString &newArrInputError);

    QString calcResult() const;
    void setCalcResult(const QString &newCalcResult);

    QString minFieldError() const;
    void setMinFieldError(const QString &newMinFieldError);

    QString maxFieldError() const;
    void setMaxFieldError(const QString &newMaxFieldError);

    QString elemCountFieldError() const;
    void setElemCountFieldError(const QString &newElemCountFieldError);

    QString genResult() const;
    void setGenResult(const QString &newGenResult);

public slots:
    void setMode(int newMode);


signals:

    void modeChanged();

    void arrInputErrorChanged();

    void calcResultChanged();

    //Generator signals
    void minFieldErrorChanged();

    void maxFieldErrorChanged();

    void elemCountFieldErrorChanged();

    void genResultChanged();

private:
    //State

    bool m_alloc;//Indicates wether array is allocated
    double* m_array;//double pointer to the double array
    QString m_arrInputError;//Error that can happen while parsing the input array

    //Generator properties
    int m_max;//Max range of array
    int m_min;//Min range of array
    int m_elementCount;//Amount of elements

    //Generator error properties
    QString m_calcResult;
    QString m_minFieldError;
    QString m_maxFieldError;
    QString m_elemCountFieldError;
    QString m_genResult;
    bool m_arrayGenerated;

    unsigned char m_mode;//Mode of the task    
    bool m_fail;
    //Private functions

    void ParseStringArray(QString strArray, double*& array,
                          std::string &error);

    bool ParseInt(const QString &value, int &output, std::string &error,
std::function<void(int)> add_Condition = nullptr, int base = 10);

    template<class T>
    void Allocate(T*& array, std::size_t count, bool& isAllocated);

    template<class T>
    void DeAllocate(T*& array, bool& isAllocated);

};

#endif // TASK2BACK_H
