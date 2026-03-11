#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H


class ErrorHandler
{
public:
    static ErrorHandler& Instance();

private:
    ErrorHandler();
    ~ErrorHandler();
    ErrorHandler(ErrorHandler const&);
    ErrorHandler& operator= (ErrorHandler const&);
}

#endif // ERRORHANDLER_H
