#ifndef CONFIG_MANAGER_HPP_
#define CONFIG_MANAGER_HPP_

#include "internal/Data/ConfigIO.hpp"
#include "internal/Data/Config.hpp"



class ConfigManager {
    public:
        ConfigManager() = default;
        ~ConfigManager() = default;
        error init(std::filesystem::path);
        error start();
        error exit();
        error saveValue(const std::string&, const std::string&);
        std::pair<error, std::string> loadValue(const std::string&);
         std::unordered_map<std::string,std::string*>& loadValues();
    private:
        ConfigIO cIO_;
        Config c_;
};


#endif //!CONFIG_MANAGER_HPP