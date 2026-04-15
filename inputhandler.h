#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include <QObject>
#include <QWinEventNotifier>
#include <windows.h>
#include <QTextStream>
#include <iostream>
#include <QString>


class InputHandler: public QObject
{
    Q_OBJECT
public:
    explicit InputHandler(QObject* parent = nullptr);
    ~InputHandler();
protected:
    int count(QString str, QString substr);
signals:
    void logMessage(const QString& message); //сигнал для логера
    void exitWord();
    void transmissionPath(QString str);
private slots:
    void preparationRead();
private:
    QWinEventNotifier* m_winevent_notifier;
};

#endif // INPUTHANDLER_H
