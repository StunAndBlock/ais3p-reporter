#ifndef CONFIG_IO_HPP_
#define CONFIG_IO_HPP_


#include "Common.hpp"
#include <unordered_set>

class ConfigIO {
    public:
        enum STATUS : int8_t { NO_CFG_FILE = -33};
        ConfigIO(std::filesystem::path);
        ~ConfigIO();
        error::error open();
        error::error close();
       //error writeValue(const std::string&, const std::string&);
        error::error readAll(std::unordered_map<std::string, std::string*>&);
        error::error writeAll(std::unordered_map<std::string, std::string*>&);
    private:
        const char eqChar_ = '=';
        const char delimeter_ = ';';
        //std::unordered_map<std::string, size_t*> valuesLocationVault_;
        std::filesystem::path fn_;
        std::fstream fd_;

};


#endif //!CONFIG_IO_HPP_