#ifndef FILEISWATCHED_H
#define FILEISWATCHED_H
#include <QString>

class FileIsWatched: QObject
{
public:
    FileIsWatched();
    FileIsWatched(const QString& m_path);
    ~FileIsWatched();

    const QString& getPath();
    int getSize();
    bool getExsist();

    QString& setPath();
    int setSize();
    bool setExsist();

public slots:
    void setFileChanged();
    void setFileDeleted();
    void setFileInit();
    void setfileMoved();

private:
    QString& m_path;
    int m_size;
    bool m_exsist;
};

#endif // FILEISWATCHED_H
