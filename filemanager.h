#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <QString>
#include <QVector>

class FileManager: QObject
{
public:
    static FileManager& Instance();
    void filesCheck();
    void fileConnect(const QString& path);
    void fileDisconnect(const QString& path);

signals:
    void fileChanged();
    void fileDeleted();
    void fileInit();
    void fileMoved();

public slots:
    void exitProgramm();

private:
    FileManager();
    ~FileManager();
    FileManager(FileManager const&);
    FileManager& operator= (FileManager const&);

    QVector <const QString&> m_files;
};

#endif // FILEMANAGER_H
