#include "internal/Error/Error.hpp"


Error::Error(const char* msg){
    msg_ = msg;
    code_ = -1;
}

Error::Error(int8_t code){
    msg_ = nullptr;
    code_ = code;
}

Error::Error(int8_t code, const char* msg){
    msg_ = msg;
    code_ = code;
}


const char* Error::msg() const {
    return msg_;
}

const int8_t Error::code() const {
    return code_;
}
Error::Error(){
    msg_ = nullptr;
    code_ = 0;
}

bool Error::operator!() const {
    return !code_;
}


bool Error::operator!=(int8_t rhs) const {
    return code_ != rhs;
}

bool Error::operator==(int8_t rhs) const {
    return code_ == rhs;
}

Error::operator bool() const {
    return code_;
}