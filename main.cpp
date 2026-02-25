#include <QCoreApplication>
#include <QFileInfo>
#include <QString>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    const QString &str = "C:\\Users\\User\\Desktop\\TRPO\\drh.txt";
    qDebug() << str;

    QFileInfo file1(str);
    qDebug() << file1.exists();
    qDebug() << file1.size();


    return a.exec();
}
