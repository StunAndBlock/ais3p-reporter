#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <cstdint>

class Error {
    public:
        Error(const char*);
        Error(int8_t);
        Error(int8_t, const char*);
        Error();
        ~Error() = default;
        bool operator!() const;
        operator bool() const;
        bool operator==(int8_t) const;
        bool operator!=(int8_t) const;
        const char* msg() const;
        const int8_t code() const;
        static constexpr struct {
            operator Error() const { return Error(); }
        } null{};        
    private:
        const char* msg_;
        int8_t code_; 
};

typedef Error error;



#endif //!ERROR_HPP_