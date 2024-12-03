#ifndef SDL_INIT_EXCEPTION_H_
#define SDL_INIT_EXCEPTION_H_

#include <stdexcept>

class SDLInitException : public std::runtime_error {
private:
    int code;
public:
    SDLInitException(const std::string& msg, int code);
    int GetErrorCode(void) const;
};
#endif /* SDL_INIT_EXCEPTION_H_ */