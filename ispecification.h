#ifndef ISPECIFICATION_H
#define ISPECIFICATION_H


class ISpecification
{
public:
    virtual bool IsSatisfied(const QString& s) = 0;
    ISpecification() {}
    virtual ~ISpecification() = 0;
};

#endif // ISPECIFICATION_H
