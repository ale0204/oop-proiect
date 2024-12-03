#include "../../../include/CandyCrush/exceptions/TTFInitException.h"

TTFInitException::TTFInitException(const std::string& msg, int code) 
    : std::runtime_error(msg), code{code} {}

int TTFInitException::GetErrorCode(void) const
{
    return code;
}