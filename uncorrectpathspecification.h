#ifndef UNCORRECTPATHSPECIFICATION_H
#define UNCORRECTPATHSPECIFICATION_H
#include <ispecification.h>
#include <QString>
#include <QVector>


class UncorrectPathSpecification : public ISpecification
{
public:
    UncorrectPathSpecification();
    bool IsSatisfied(const QString& s) override;
    ~ISpecification() override;

    QVector <const QString&> GetFilter();

signals:

private:
    QVector <const QString&> _filter;

};

#endif // UNCORRECTPATHSPECIFICATION_H
