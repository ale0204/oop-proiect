#include "../../../include/CandyCrush/exceptions/SDLInitException.h"

SDLInitException::SDLInitException(const std::string& msg, int code) 
    : std::runtime_error(msg), code{code} {}

int SDLInitException::GetErrorCode(void) const
{
    return code;
}