#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H


class InputHandler
{
public:
    static InputHandler& Instance();
signals:
    void exitProgramm();

private:
    InputHandler();
    ~InputHandler();
    InputHandler(InputHandler const&);
    InputHandler& operator= (InputHandler const&);

};

#endif // INPUTHANDLER_H
