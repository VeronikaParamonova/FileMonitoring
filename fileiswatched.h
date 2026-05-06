#ifndef FILEISWATCHED_H
#define FILEISWATCHED_H
#include <QString>
#include <QObject>
#include <QFileInfo>


enum ChangeType {Initial, Created, Deleted, SizeChanged}; //Используем перечисление для типов исзменения состояния. Для более безопасного кода (чтобы безопасно его масштабировать) можно использовать enum class для исключения конфликта имён и случайного сравнения типа изменения с целым числом. Но в таком случае при каждом использовании типа изменения нужно применять область видимости. Для упрощённой работы с перечислением на данный момент используем классический enum

class FileIsWatched: public QObject
{
    Q_OBJECT

public:
    explicit FileIsWatched(const QString& path, QObject* parent = nullptr);
    ~FileIsWatched(); //пока пустой, так как в конструкторе присутствует указатель на родителя, который может управлять временем жизни

    void checkState(); //проверка состояния. Будет вызываться менеджером каждый такт таймера

    const QString getPath() {return m_path;}
    qint64 getSize() {return m_size;}
    bool getExists() {return m_exists;}

    bool getFirstCheck() {return m_first_check;}

signals:
    void stateChanged(const QString& path, qint64 size, bool exists, ChangeType change); //сигнал при изменении состояния файла. Будет передавать путь к файлу, существование, размер и тип изменения

private:
    QString m_path;
    qint64 m_size;
    bool m_exists;

    bool m_first_check; //флаг, используемый в методе checkState(), для вывода первоначального состояния при подключении
};

#endif // FILEISWATCHED_H
