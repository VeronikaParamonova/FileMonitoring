#ifndef LOGTOCONSOLE_H
#define LOGTOCONSOLE_H
#include <ilog.h>
#include <iostream>
#include <QObject>

class LogToConsole: public QObject, public ILog
{
    Q_OBJECT
public:
    explicit LogToConsole(QObject *parent = nullptr); //ключевое слово explicit защищает от неявного преобразования типов, например, программа не преобразует nullptr в объект типа QObject. Рекомендуется для конструкторов с одним аргументом. Также м передаём в конструктор нулевой указатель на родителя. Для классов, наследников QObject, полезно передавать в конструктор родителя, т к при удалении родителя удалятся и все объекты, в которых он выступал родителем. В нашем случае логер создаётся в стеке в main, поэтому укзатель на родителя является нулевым, он нам попросту не нужен. Но данная конструкция оставлена ради сохранения единообразия
    void printLog(const QString& message) override;
public slots:
    void printLogSlot(const QString& message);
};

#endif // LOGTOCONSOLE_H
