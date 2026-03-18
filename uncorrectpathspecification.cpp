#include "uncorrectpathspecification.h"

UncorrectPathSpecification::UncorrectPathSpecification()
{
    _filter = {"\\", "/", ":", "*", "?", "\"", "<", ">", "|", "CON", "PRN", "AUX", "NUL"};
    for (int i = 1; i <= 9; i++)
    {
        const QString& s = "COM" + i;
        _filter.append(s);
        const QString& s = "LPT" + i;
        _filter.append(s);
    }
    for (int i = 0; i <= 31; i++)
    {
        const QString& s = QChar(i);
        _filter.append(s);
    }

}

QVector <const QString&> UncorrectPathSpecification::GetFilter()
{
     return _filter;
}

bool UncorrectPathSpecification::IsSatisfied(const QString& s) override
{
     for (int i = 0; i < filter.size(); i++ )
     {
        if (s.contains(_filter[i]))
        {
            return false;
        }
        else
        {
            return true;
        }
     }
}
