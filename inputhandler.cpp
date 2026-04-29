#include "InputHandler.h"
#include <QDebug>

InputHandler::InputHandler(QObject* parent): QObject(parent)
{

}

InputHandler::~InputHandler()
{

}

int InputHandler::count(QString str, QString substr)
{
    int count = 0;
    int pos = str.indexOf(substr);
    while (pos != -1) {
        count++;
        pos = str.indexOf(substr, pos + substr.length());
    }
    return count;
}

void InputHandler::preparationRead(QString str)
{
    str = str.trimmed();

    if (str.isEmpty())
    {
        emit logMessage("ERROR: empty string entered");
        return;
    }

    if (str.compare("EXIT") == 0) //нам необходимо непросто найти ключевое слово со входящей строкой, нам необходимо сравнить её лексически (возвращает 0 в случае, если строки лексически равн). Т к возможен случай папки с таким названием или пути к файлу под названием EXIT.txt Отметим, что функция ЧУВСТВИТЕЛЬНА к регистру. Можно это исправить, введя второй аргумент Qt::CaseInsensitive
    {
        emit exitWord(); // сигнал подготовки программы к завершению
        return;
    }

    if (InputHandler::count(str,":") > 1)
    {
        emit logMessage("ERROR: more than one file entered");
        return;
    }
    if (str.right(4) != ".txt")
    {
        emit logMessage("ERROR: incorrect file format");
        return;
    }
    if (InputHandler::count(str,":") == 0)
    {
        emit logMessage("WARNING: The tracked file must be in the project folder.");
    }

    //создание списка всех названий из пути
    QChar re1 = ':';
    QChar re2 = '\\';
    QList<QString> names = str.split(re1);

    if (names.size() > 1)
    {
    QString path_without_disk = names[1];

    names.removeLast();
    names += path_without_disk.split(re2);
    }


    if (names.size() == 1)
    {
    QString path_without_disk = names[0];

    names.removeLast();
    names += path_without_disk.split(re2);
    }


    //создаём список запрещённых элементов в названиях пути
    QList<QString> filter = {"\\", "/", ":", "*", "?", "\"", "<", ">", "|", "CON", "PRN", "AUX", "NUL"};
    for (int i = 1; i <= 9; i++)
    {
        QString s = "COM" + QString::number(i);
        filter.append(s);
        s = "LPT" + QString::number(i);
        filter.append(s);
    }
    for (int i = 0; i <= 31; i++)
    {
        QString s = QChar(i);
        filter.append(s);
    }


    for (int i = 0; i < names.size(); i++)
        for (int j = 0; j < filter.size(); j++ )
        {
            if (names[i].contains(filter[j]))
            {
                emit logMessage("ERROR: file path contains illegal characters");
                return;
            }
        }

    emit transmissionPath(str);

}
