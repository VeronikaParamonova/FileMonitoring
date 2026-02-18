#include <QCoreApplication>
#include <QFileInfo>
#include <QString>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString const Name = QString('C:\\Users\\User\\Desktop\\TRPO\\drh.txt');
    QFileInfo File = QFileInfo(Name);
    std::cout << 'FFFFFFFFFFF';
    std::cout << File.exists();

    return a.exec();
}
