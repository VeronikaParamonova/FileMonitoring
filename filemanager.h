#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <QString>
#include <QList>
#include <fileiswatched.h>
#include <QCoreApplication>

class FileManager: public QObject
{
    Q_OBJECT
public:   
    static FileManager& Instance();

    bool fileConnect(const QString& path);
    bool fileDisconnect(const QString& path);

    void allFilesDisconnect(); //отключение всех файлов при выходе из программы

signals:
    void logMessage(const QString& message); //сигнал для логера
public slots:
    void checkAllFiles(); //проверка состояний всех подключённых файлов каждый такт таймера
    void inputString(const QString& str); //обработка входной строки
    void fileStateChanged(const QString& path, qint64 size, bool exists, ChangeType change); //слот для сигнала stateChanged от объекта FileIsWatched
    void exitProgramm();//слот, который будет срабатывать при выходе из программы словом EXIT


private:
    explicit FileManager(QObject* parent = nullptr);
    ~FileManager();
    FileManager(FileManager const&);
    FileManager& operator= (FileManager const&);

    FileIsWatched* findFile(const QString& path) const; //вспомогательный метод нахождения файла по пути в списке подключённых. Используется в подключении и отключении, а также в обработке входной строки. const после списка параметров отвечает за отстутсвие изменений полей объекта FileManager, например, списка подключённых файлов, т к поиск не должен менять список


    QList<FileIsWatched*> m_files;
};

#endif // FILEMANAGER_H
