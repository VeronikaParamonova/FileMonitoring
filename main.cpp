#include <QCoreApplication>
#include <QString>
#include <QDebug>
#include <QTimer>
#include <QDir>
#include "filemanager.h"
#include "logtoconsole.h"
#include "InputHandler.h"
#include <conio.h>   // для _kbhit

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    qDebug() << "Current working directory:" << QDir::currentPath();

    LogToConsole log; //создаём логер в стеке, т к он времени жизни переменной в стеке нам достаточно
    FileManager& manager = FileManager::Instance(); //первый вызов Instance создаст статический объект filemanager и вернёт ссылку на него
    InputHandler input_handler; //создаём парсер в стеке аналогично логгеру
    QTimer file_timer;


    QTimer consoleTimer;
    QObject::connect(&consoleTimer, &QTimer::timeout, [&]() {
        if (_kbhit()) //_kbhit() — это функция, которая проверяет консоль на наличие нажатий клавиш, не приостанавливая выполнение программы. Она возвращает ненулевое значение, если клавиша нажата, и в противном случае, что позволяет создавать неблокирующий ввод.
        {
            QTextStream in(stdin);
            QString line = in.readLine();
            if (!line.isEmpty()) {
                input_handler.preparationRead(line);
            }
        }
    });
    consoleTimer.start(100);  // проверяем каждые 100 мс


    //проводим все необходимые коннекты
    QObject::connect(&manager, &FileManager::logMessage,&log, &LogToConsole::printLogSlot);
    QObject::connect(&file_timer, &QTimer::timeout, &manager, &FileManager::checkAllFiles);
    QObject::connect(&input_handler, &InputHandler::transmissionPath, &manager, &FileManager::inputString);
    QObject::connect(&input_handler, &InputHandler::logMessage, &log, &LogToConsole::printLogSlot);
    QObject::connect(&input_handler, &InputHandler::exitWord, &manager, &FileManager::exitProgramm);



    log.printLog("The program has started. Please enter the path to the file or the word EXIT to terminate the program.");

    file_timer.QTimer::setInterval(100);
    file_timer.QTimer::setSingleShot(false);
    file_timer.start();

    return a.exec();

}
