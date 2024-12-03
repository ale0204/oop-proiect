#ifndef TTF_INIT_EXCEPTION_H_
#define TTF_INIT_EXCEPTION_H_

#include <stdexcept>

class TTFInitException : public std::runtime_error {
private:
    int code;
public:
    TTFInitException(const std::string& msg, int code);
    int GetErrorCode(void) const;
};

#endif /* TTF_INIT_EXCEPTION_H_ */