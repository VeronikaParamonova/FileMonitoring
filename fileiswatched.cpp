#include "fileiswatched.h"
#include <QDebug>

FileIsWatched::FileIsWatched(const QString& path, QObject* parent) : QObject(parent), m_path(path), m_size(0), m_exists(false), m_first_check(true) {} //на момент инициализации объекта ещё не известен его размер и существование. Флаг первой проверки ставим true, так как файл ещё ни разу не проверялся(нужен для вывода первоначального состояния)

FileIsWatched::~FileIsWatched()
{
    //деструктор пустой, так как временем жизни управляет родитель
}

void FileIsWatched::checkState()
{
    QFileInfo file(m_path); //инициализируем объект типа QFileInfo для получения информации об отслеживаемом файле с помощью методов класса QFileInfo
    file.refresh();
    qint64 nowSize = file.size(); //здесь раскрывается, зачем мы используем тип данных qint64, а не int. Дело в том, что метод size класса QFileInfo возвращает qint64
    bool nowExists = file.exists();

    ChangeType change; //создаём объект перечисления

    if (m_first_check)
    {
        change = Initial;
        m_first_check = false; //данный if сработает только при первой проверке состояния, что будет говорить нам о том, что требуется вывести сообщение о подключении. Больше в этот if мы не зайдём
    }
    else
    {
        if (nowExists != m_exists)
        {
            if (nowExists)
            {
                change = Created;
            }
            else
            {
                change = Deleted;
            }
        }
        else if (nowExists && (nowSize != m_size))
        {
            change = SizeChanged;
        }
        else
        {
            return; //если ничего не изменилось, то сигнал нам испускать не нужно, выходим
        }
    }

    m_size = nowSize;
    m_exists = nowExists;

    emit stateChanged(m_path, nowSize, nowExists, change);
}
