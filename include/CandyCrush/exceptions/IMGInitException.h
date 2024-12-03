#ifndef IMG_INIT_EXCEPTION_H_
#define IMG_INIT_EXCEPTION_H_

#include <stdexcept>

class IMGInitException : public std::runtime_error {
private:
    int code;
public:
    IMGInitException(const std::string& msg, int code);
    int GetErrorCode(void) const;
};

#endif /* IMG_INIT_EXCEPTION_H_ */