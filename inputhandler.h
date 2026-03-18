#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include <QString>
#include <QVector>
#include <ispecification.h>

class InputHandler: QObject
{
public:
    static InputHandler& Instance();
    const QString& InputPath(QString& paths);
    void GetPath(ISpecification *spec);
protected:
    const QString& InputOnePath(QString& paths);
    QVector <const QString&> InputFolderPath(QString& paths);
    const QString& InputUncorrectPath(QString& paths);
    const QString& InputNameWithoutPath(QString& paths);
    const QString& InputUncorrectPath(QString& paths);

signals:
    void exitProgramm();
    void uncorrectPath();
    void voidDirPath();
    void onlyName();//будет выводить предупреждение, что к какой папке подключён или ожидается файл(откуда запускается программа)

private:
    InputHandler();
    ~InputHandler();
    InputHandler(InputHandler const&);
    InputHandler& operator= (InputHandler const&);

};

#endif // INPUTHANDLER_H
