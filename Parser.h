#ifndef PARSER_H
#define PARSER_H
#include <QObject>
#include <QSocketNotifier>

class Parser: public QObject
{
    Q_OBJECT
public:
    explicit Parser(QObject* parent = nullptr);
    ~Parser();
};

#endif // PARSER_H
