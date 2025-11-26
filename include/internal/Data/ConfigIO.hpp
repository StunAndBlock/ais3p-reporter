#ifndef CONFIG_IO_HPP_
#define CONFIG_IO_HPP_


#include "Common.hpp"
#include <unordered_set>

class ConfigIO {
    public:
        enum Status : int8_t { NO_CFG_FILE = -33};
        ConfigIO() = default;
        ~ConfigIO();
        error open(const std::filesystem::path);
        error close();
        error writeValue(const std::string&, const std::string&);
        error readAll(std::unordered_map<std::string, std::string*>&);
    private:
        const char eqChar_ = '=';
        const char delimeter_ = ';';
        std::unordered_map<std::string, std::streampos*> valuesLocationVault_;
        std::fstream fd_;

};


#endif //!CONFIG_IO_HPP_