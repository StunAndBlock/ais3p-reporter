#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <cstdint>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <string>
class Error {
    public:
        Error(const char*);
        Error(int);
        Error(int, const char*);
        Error();
        ~Error() = default;
        bool operator!() const;
        operator bool() const;
        bool operator==(int) const;
        bool operator!=(int) const;
        const char* msg() const;
        const int code() const;     
    private:
        char* msg_;
        int code_; 
};


namespace error {
    typedef Error error;
    static constexpr struct {
        operator Error() const { return Error(); }
    }null{};   
    error errorf(const char*, ...);
    error errorf(int, const char*, ...);

}


#endif //!ERROR_HPP_