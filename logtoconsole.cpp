#include "logtoconsole.h"

LogToConsole::LogToConsole(QObject *parent) : QObject(parent) {} //указание того, что родитель нулевой, находится в заголовочном файле, здесь не дублируем. После двоеточия начинается список инициализации, мы обязаны явно вызвать конструктор базового класса, чтобы правильно сформировать объект

void LogToConsole::printLog(const QString &message)
{
    std::cout << message.toStdString() << std::endl; //Напрямую cuot не может вывести QString, из-за разных типов данных. Поэтому используем метод toStdString()

}
