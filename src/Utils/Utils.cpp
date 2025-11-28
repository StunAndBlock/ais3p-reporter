
#include "internal/Utils/Utils.hpp"

namespace utils {
        std::string prettyf(const char* format, ...){
            va_list args;
            va_start(args, format);

            va_list args_copy;
            va_copy(args_copy, args);
            int length = std::vsnprintf(NULL, 0, format, args_copy);
            va_end(args_copy);

            if (length < 0) {
                va_end(args);
                return nullptr;
            }
            char buf[length+1];
            std::vsnprintf(buf, length + 1, format, args);
            va_end(args);
            return buf;
        }

}