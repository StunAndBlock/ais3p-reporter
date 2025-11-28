#include "internal/Error/Error.hpp"


Error::Error(const char* msg){
    msg_ = new char[strlen(msg) + 1];
    strcpy(msg_, msg);
    code_ = -1;
}

Error::Error(int code){
    msg_ = nullptr;
    code_ = code;
}

Error::Error(int code, const char* msg){
    msg_ = new char[strlen(msg) + 1];
    strcpy(msg_, msg);
    code_ = code;
}


const char* Error::msg() const {
    return msg_;
}

const int Error::code() const {
    return code_;
}
Error::Error(){
    msg_ = nullptr;
    code_ = 0;
}

bool Error::operator!() const {
    return !code_;
}


bool Error::operator!=(int rhs) const {
    return code_ != rhs;
}

bool Error::operator==(int rhs) const {
    return code_ == rhs;
}

Error::operator bool() const {
    return code_;
}


error::error error::errorf(int code, const char* format, ...){
    va_list args;
    va_start(args, format);

    va_list args_copy;
    va_copy(args_copy, args);
    int length = std::vsnprintf(NULL, 0, format, args_copy);
    va_end(args_copy);

    if (length < 0) {
        va_end(args);
        return error(code,format);
    }
    char buf[length+1];
    std::vsnprintf(buf, length + 1, format, args);
    va_end(args);
    return error(code, buf);
}


error::error error::errorf(const char* format, ...){
    va_list args;
    va_start(args, format);

    va_list args_copy;
    va_copy(args_copy, args);
    int length = std::vsnprintf(NULL, 0, format, args_copy);
    va_end(args_copy);

    if (length < 0) {
        va_end(args);
        return error(format);
    }
    char buf[length+1];
    std::vsnprintf(buf, length + 1, format, args);
    va_end(args);
    return error(buf);
}