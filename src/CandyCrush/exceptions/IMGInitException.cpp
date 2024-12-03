#include "../../../include/CandyCrush/exceptions/IMGInitException.h"

IMGInitException::IMGInitException(const std::string& msg, int code) 
    : std::runtime_error(msg), code{code} {}

int IMGInitException::GetErrorCode(void) const
{
    return code;
}