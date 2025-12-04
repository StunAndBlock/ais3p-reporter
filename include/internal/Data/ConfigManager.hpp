#ifndef CONFIG_MANAGER_HPP_
#define CONFIG_MANAGER_HPP_

#include "internal/Data/ConfigIO.hpp"
#include "internal/Data/Config.hpp"



class ConfigManager {
    public:
        ConfigManager();
        ~ConfigManager() = default;
        error::error init();
        error::error start();
        error::error firstStart();
        error::error exit();
        error::error saveValue(const std::string&, const std::string&);
        std::pair<error::error, std::string*> loadValue(const std::string&);
         std::unordered_map<std::string,std::string*>& loadValues();
    private:
        ConfigIO cIO_;
        Config c_;
};


#endif //!CONFIG_MANAGER_HPP