#include "task2back.h"

task2back::task2back(QObject *parent)
    : m_array(nullptr), m_mode(1), m_max(0), m_min(0), m_elementCount(0),
    m_fail(false), m_arrayGenerated(false), QObject{parent}
{
    setMin("");
    setMax("");
    setElementCount("");
    setGenResult("");
}

task2back::~task2back()
{
    if(m_array != nullptr)
        delete[] m_array;
}



void task2back::ParseStringArray(QString strArray, double*& array,
                                 std::string &error)
{    
    try
    {
        QStringList temp = strArray.split(QRegularExpression("\\,"));

        auto begin = temp.begin();
        auto end = temp.end();

        if(array != nullptr)
            delete[] array;

        m_elementCount = temp.count();

        array = new double[temp.count()];
        int i = 0;
        while(begin != end)
        {
            bool isNumb = false;
            *(array + i) = begin->toDouble(&isNumb);
            if(!isNumb)
            {
                throw std::runtime_error("Error while parsing string to double number! Check your input!");
            }
            ++i;
            ++begin;
        }
    }
    catch(std::runtime_error& er)
    {
        if(array != nullptr)
            delete[] array;

        error = er.what();
    }
    catch (...)//catch all possible exceptions
    {
        if(array != nullptr)
            delete[] array;

        error = "Error while parsing Array!";
    }
}

bool task2back::ParseInt(const QString &value, int &output, std::string &error,
                         std::function<void(int)> add_Condition, int base)
{
    if(value.isEmpty())
    {
        error = "Empty input!";
        return false;
    }

    bool result = false;

    try {
        output = value.toInt(&result, base);

        if(add_Condition != nullptr)
            add_Condition(output);

        if(!result)
            throw std::runtime_error("Failed to parse input to Int!");
    }
    catch(std::runtime_error &err)
    {
        error = err.what();
        return false;
    }
    catch (...)
    {
        error = "Unknown error while parsing!";
        return false;
    }

    return true;
}

void task2back::setArray(const QString& strArray)
{
    std::string errorTemp("");

    ParseStringArray(strArray, m_array, errorTemp);

    if(!errorTemp.empty())
    {
        setArrInputError(QString::fromStdString(errorTemp));

        m_fail = true;
    }
    else
        m_fail = false;

    //array was parssed succesfully or fail happened
}

void task2back::calculate()
{
    using namespace std;

    QString result;

    if(m_array != nullptr && !m_fail)
    {
        //1) Sort array using quick sort
        sort_algorithms<double>::quickSort(m_array, 0, m_elementCount - 1);

        //2) Iterate array from end to the end and find 3 numbers
        int count = 2;
        int currCount = 0;

        int end = m_elementCount - 1;

        double maxTemp = *(m_array + end);

        end-=1;

        result += to_string(maxTemp);

        for(; end >= 0 && currCount < count ; --end)
        {
            if(*(m_array + end) != maxTemp)
            {
                maxTemp = *(m_array + end);

                result += " | " + to_string(maxTemp);

                ++currCount;
            }
        }
    }

    setCalcResult(result);

    if(m_mode == 1)
        setArrInputError("");//Reset Error signal
}

//Generator definitions

void task2back::setMin(const QString& minStr)
{
    std::string errorTemp("");

    int temp = 0;

    if(!ParseInt(minStr, temp, errorTemp)) //error happened
    {
        setMinFieldError(QString::fromStdString(errorTemp));
        m_fail = true;
    }
    else
    {
        setMinFieldError("");
        m_fail = false;
        m_min = temp;
    }

}

void task2back::setMax(const QString& maxStr)
{
    std::string errorTemp("");

    int temp = 0;

    if(!ParseInt(maxStr, temp, errorTemp, [this](int n)-> void
                  {
            if(n < m_min)
                throw std::runtime_error("Max can't be <= min!");
            if(n == m_min)
                throw std::runtime_error("Max can't be == min!");
        })) //error happened
    {
        setMaxFieldError(QString::fromStdString(errorTemp));
        m_fail = true;
    }
    else
    {
        setMaxFieldError("");
        m_fail = false;
        m_max = temp;
    }
}

void task2back::setElementCount(const QString& elemCountStr)
{
    std::string errorTemp("");

    int temp = 0;

    if(!ParseInt(elemCountStr, temp, errorTemp, [](int n)-> void
                  {
                        if(n <= 0)
                          throw std::runtime_error("Amount of elem must be > 0!");
                  })) //error happened
    {
        setElemCountFieldError(QString::fromStdString(errorTemp));
        m_fail = true;
    }
    else
    {
        setElemCountFieldError("");
        m_fail = false;
        m_elementCount = temp;
    }
}

void task2back::generateArray()
{
    using namespace std;
    try {

        if(m_array != nullptr)
            delete[] m_array;

        srand(std::time(nullptr));

        m_array = new double[this->m_elementCount];

        int range = m_max - m_min + 1;

        QString str;

        for(std::size_t i = 0; i < m_elementCount; ++i)
        {
            *(m_array + i) = m_min + rand() % range;

            str += to_string(*(m_array + i)) + ",";
        }

        setGenResult(str);

        m_fail = false;

        m_arrayGenerated = true;

    } catch (...) {

        if(m_array != nullptr)
            delete[] m_array;

        setGenResult("Gen error!");

        m_fail = true;

        m_arrayGenerated = false;
    }
}

bool task2back::failStatus()
{
    return m_fail;
}

bool task2back::arrayGenerated()
{
    return m_arrayGenerated;
}

//Read and Write Properties

int task2back::mode() const
{
    return m_mode;
}

void task2back::setMode(int newMode)
{
    if (m_mode == newMode)
        return;
    m_mode = newMode;
    emit modeChanged();
}

QString task2back::arrInputError() const
{
    return m_arrInputError;
}

void task2back::setArrInputError(const QString &newArrInputError)
{
    if (m_arrInputError == newArrInputError)
        return;
    m_arrInputError = newArrInputError;
    emit arrInputErrorChanged();
}

QString task2back::calcResult() const
{
    return m_calcResult;
}

void task2back::setCalcResult(const QString &newCalcResult)
{
    if (m_calcResult == newCalcResult)
        return;
    m_calcResult = newCalcResult;
    emit calcResultChanged();
}

//Array Generator Read Write

QString task2back::minFieldError() const
{
    return m_minFieldError;
}

void task2back::setMinFieldError(const QString &newMinFieldError)
{
    if (m_minFieldError == newMinFieldError)
        return;
    m_minFieldError = newMinFieldError;
    emit minFieldErrorChanged();
}

QString task2back::maxFieldError() const
{
    return m_maxFieldError;
}

void task2back::setMaxFieldError(const QString &newMaxFieldError)
{
    if (m_maxFieldError == newMaxFieldError)
        return;
    m_maxFieldError = newMaxFieldError;
    emit maxFieldErrorChanged();
}

QString task2back::elemCountFieldError() const
{
    return m_elemCountFieldError;
}

void task2back::setElemCountFieldError(const QString &newElemCountFieldError)
{
    if (m_elemCountFieldError == newElemCountFieldError)
        return;
    m_elemCountFieldError = newElemCountFieldError;
    emit elemCountFieldErrorChanged();
}

QString task2back::genResult() const
{
    return m_genResult;
}

void task2back::setGenResult(const QString &newGenResult)
{
    if (m_genResult == newGenResult)
        return;
    m_genResult = newGenResult;
    emit genResultChanged();
}
