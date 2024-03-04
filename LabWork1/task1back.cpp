#include "task1back.h"

task1back::task1back(QObject *parent)
    : QObject{parent}, m_error(""), m_fail(true),
    m_day(0),m_month(monthes_qml_env::monthes::Undefined), m_leapYear(false)

{}

bool task1back::leapYear() const
{
    return m_leapYear;
}

void task1back::setleapYear(bool newLeapYear)
{
    if (m_leapYear == newLeapYear)
        return;
    m_leapYear = newLeapYear;
    emit leapYearChanged();
}

int task1back::getDay()
{
    return m_day;
}

bool task1back::isFail()
{
    return m_fail;
}

bool task1back::TryParseToUINt(const std::string &input, uint& out, std::string& error)
{
    try {

        out = (uint)std::stoi(input);

        return true;

    } catch (std::invalid_argument er)
    {
        error = er.what();

        return false;
    }
}

monthes_qml_env::monthes task1back::ConvertToMonthes(uint month_number)
{
    if(month_number < 1 && month_number > 12)
        return monthes_qml_env::monthes::Undefined;

    switch(month_number)
    {
    case 1:
        return monthes_qml_env::monthes::January;
    case 2:
        return monthes_qml_env::monthes::February;
    case 3:
        return monthes_qml_env::monthes::March;
    case 4:
        return monthes_qml_env::monthes::April;
    case 5:
        return monthes_qml_env::monthes::May;
    case 6:
        return monthes_qml_env::monthes::June;
    case 7:
        return monthes_qml_env::monthes::July;
    case 8:
        return monthes_qml_env::monthes::August;
    case 9:
        return monthes_qml_env::monthes::September;
    case 10:
        return monthes_qml_env::monthes::October;
    case 11:
        return monthes_qml_env::monthes::November;
    case 12:
        return monthes_qml_env::monthes::December;
    }

    return monthes_qml_env::monthes::Undefined;
}

void task1back::calculate(QString dateInput)
{
    m_fail = false;

    m_error = "";

    std::string date = dateInput.toStdString();

    //Check if input string is empty
    if(date.empty())
    {
        m_fail = true;
        setError("Empty input!");
        return;
    }

    uint date_inp = 0;

    std::string temp;
    //try to parse date string to uint
    m_fail = !TryParseToUINt(date, date_inp, temp);

    if(m_fail)
    {
        setError("Cannot parse date string!");
        return;
    }
    //Range check
    if(date_inp == 0 || date_inp > 366)
    {
        m_fail = true;
        setError("Invalid range! Valid range is (1 - 366)");
        return;
    }

    if(!m_leapYear && date_inp > 365)
    {
        m_fail = true;
        setError("Error! Range exceeds 365 days, when ordinary year is set!");
        return;
    }

    //main calculation algorithm

    bool thirtyOneOrthirty = true;//Controlls the day count in each month

    uint day_in_a_month = 31;

    uint currentday = 0;

    unsigned char currentMonth = 1;

    for(uint start = 0; start < date_inp; ++start, ++currentday)// O(n)
    {        
        if(start == day_in_a_month)
        {            
            currentday = 0;

            ++currentMonth;

            if(currentMonth == 2)
            {
                day_in_a_month += m_leapYear? 29 : 28;
            }
            else if(currentMonth == 8 || currentMonth == 3)
            {
                day_in_a_month += 31;
            }
            else
            {
                if(thirtyOneOrthirty)
                    thirtyOneOrthirty = false;
                else
                    thirtyOneOrthirty = true;

                day_in_a_month += thirtyOneOrthirty? 31 : 30;
            }
        }
    }

    m_day = currentday;

    qDebug() << m_day <<"."<< currentMonth;

    setMonth(ConvertToMonthes(currentMonth));
}

QString task1back::error() const
{
    return m_error;
}

void task1back::setError(const QString &newError)
{
    if (m_error == newError)
        return;
    m_error = newError;
    emit errorChanged();
}



monthes_qml_env::monthes task1back::month() const
{
    return m_month;
}

void task1back::setMonth(const monthes_qml_env::monthes &newMonth)
{
    m_month = newMonth;

    emit monthChanged();
}
