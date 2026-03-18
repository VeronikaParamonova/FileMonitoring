#include "inputhandler.h"

static InputHandler:: InputHandler& Instance()
{
    static InputHandler h;
    return h;
}

void InputHandler::GetPath(ISpecification *spec)
{

}
