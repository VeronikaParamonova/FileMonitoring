#ifndef ILOG_H
#define ILOG_H
#include <QString>



class ILog //применяем множественное наследование в LogToConsole. Для того, чтобы в конструкторе LogToConsole вызвать конструктор QObject, а не ILog, т к в ILog конструктор не прописан
{
public:
    //конструктор не определяем, так как класс абстрактный, и м не сможем создать объект этого класса, только указатель на него. Компилятор автоматически сгенерирует конструктор по умолчанию, он будет недоступен для создания объектов
    virtual ~ILog() = default;
    virtual void printLog(const QString& message) = 0;

};

#endif // ILOG_H
