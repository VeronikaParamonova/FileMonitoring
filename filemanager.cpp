#include "filemanager.h"
#include <QDebug>

FileManager& FileManager::Instance()
{
    static FileManager manager;
    return manager;
}

FileManager::FileManager(QObject* parent) : QObject(parent) {}

FileManager::~FileManager()
{
    allFilesDisconnect();
}

bool FileManager::fileConnect(const QString& path)
{
    if (path.isEmpty())
    {
        emit logMessage("ERROR: Empty path entered");
        return false;
    }

    if (findFile(path))
    {
        emit logMessage("The file is already being tracked");//предупреждение, что файл уже отслеживается в нашей работе программы никогда не выведется, так как в слоте InputHandler уже есть проверка перед подключением файла есть ли он в списке подключённых. Эта же проверка сделана для будущей разработки программы, если разработчик захочет подключить уже подключённый файл, что приведёт к дублированию FileIsWatched
        return false;
    }

    FileIsWatched* file = new FileIsWatched(path, this);//выделение памяти, в качестве родителя передаём файл-менеджер, который будет управлять временем жизни
    connect(file, &FileIsWatched::stateChanged, this, &FileManager::fileStateChanged);//подключения сигнала файла к слоту файл менеджера

    m_files.append(file);
    file->checkState(); //вывод начального состояния

    emit logMessage("Successful connection for monitoring");
    return true;
}

bool FileManager::fileDisconnect(const QString &path)
{
    FileIsWatched* file = findFile(path);
    if (!file)
    {
        emit logMessage("The file to be deleted is not tracked");//аналогично 26-ой строчке. Это сообщение никогда не выводится при отработке нашей программы. Оно нужно для дальнейшей разработки в качестве проверки при ручном вызове отключения файла
        return false;
    }

    m_files.removeOne(file);
    delete file; // освобождение памяти

    emit logMessage("Successful escape for monitoring");
    return true;
}

void FileManager::allFilesDisconnect()
{
    for (FileIsWatched* file : m_files) //освобождение памяти для каждого объекта FileIsWatched, которые остались перед закрытием программы
    {
        delete file;
    }
    m_files.clear();//очищение списка файлов под наблюдением

    emit logMessage("The program is ready to close");
}

void FileManager::checkAllFiles()
{
    //qDebug() << "checkAllFiles: tracking" << m_files.size() << "files";
    for (FileIsWatched* file : m_files)
    {
        file->checkState();
    }
}

void FileManager::inputString(const QString& str)
{
  if (str.isEmpty())
    {
        return;//если на вход пришла пустая строка, то мы не передаём её на подключение. Повторная проверка
    }

    //основная часть обработки
    if (findFile(str))
    {
        fileDisconnect(str);
    }
    else
    {
        fileConnect(str);
    }
}

void FileManager::fileStateChanged(const QString &path, qint64 size, bool exists, ChangeType change)
{
    //emit logMessage("fileStateChanged received");
    //начинаем формировать сообщение для передачи в логер
    QString message;

    switch (change)
    {
    case Initial:
        message = "Initial state: ";
        break;
    case Created:
        message = "File created: ";
        break;
    case Deleted:
        message = "File deleted: ";
        break;
    case SizeChanged:
        message = "The file size has been changed: ";
        break;
    }

    message += path;

    if(exists)
    {
        message += " exists, its size: " + QString::number(size) + " bites.";
    }
    else
    {
        message += " not exists.";
    }

    emit logMessage(message);
}

FileIsWatched* FileManager::findFile(const QString &path) const
{
    for (FileIsWatched* file : m_files)
    {
        if (file->getPath() == path)
        {
            return file;
        }
    }
    return nullptr;
}

void FileManager::exitProgramm()
{
    emit logMessage("Exiting the program...");
    allFilesDisconnect();
    QCoreApplication::quit();
}
