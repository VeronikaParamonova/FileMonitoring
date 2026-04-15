#include <QCoreApplication>
#include <QString>
#include <QDebug>
#include <QTimer>
#include "filemanager.h"
#include "logtoconsole.h"
#include "InputHandler.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LogToConsole log; //создаём логер в стеке, т к он времени жизни переменной в стеке нам достаточно
    FileManager& manager = FileManager::Instance(); //первый вызов Instance создаст статический объект filemanager и вернёт ссылку на него
    InputHandler input_handler; //создаём парсер в стеке аналогично логгеру
    QTimer timer;


    //проводим все необходимые коннекты
    QObject::connect(&manager, &FileManager::logMessage,&log, &LogToConsole::printLogSlot);
    QObject::connect(&timer, &QTimer::timeout, &manager, &FileManager::checkAllFiles);
    QObject::connect(&input_handler, &InputHandler::transmissionPath, &manager, &FileManager::inputString);
    QObject::connect(&input_handler, &InputHandler::logMessage, &log, &LogToConsole::printLogSlot);
    QObject::connect(&input_handler, &InputHandler::exitWord, &manager, &FileManager::exitProgramm);

    log.printLog("The program has started. Please enter the path to the file or the word EXIT to terminate the program.");

    timer.QTimer::setInterval(100);
    timer.QTimer::setSingleShot(false);
    timer.start();
    //manager.fileConnect("C:\\Users\\User\\Desktop\\TRPO\\File1.txt");
    return a.exec();
}
