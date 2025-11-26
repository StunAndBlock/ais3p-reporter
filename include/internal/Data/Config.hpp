#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include "Common.hpp"
class Config {
    public:
        enum Status : int8_t { UNKNOWN_CONFIGURATION = -22, EMPTY_VALUE = -23};
        Config();
        ~Config();
        error setValue(const std::string&, const std::string& );
        std::pair<error, std::string> getValue(const std::string&);
        std::unordered_map<std::string,std::string*>& getVault();
    private: 
        std::unordered_map<std::string,std::string*> valuesVault_;
};















#endif //!CONFIG_HPP_