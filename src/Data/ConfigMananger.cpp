#include "internal/Data/ConfigManager.hpp"



error ConfigManager::init(const std::filesystem::path cfgFP){
    error err;
    err = cIO_.open(cfgFP);
    return err;
}


error ConfigManager::start(){
    error err;
    auto& vaultRef = c_.getVault();
    err = cIO_.readAll(vaultRef);
    return err;
}



error ConfigManager::exit(){
    error err;
    err = cIO_.close();
    return err;
}


error ConfigManager::saveValue(const std::string& nameKey, const std::string& value){
    error err;
    err = cIO_.writeValue(nameKey,value);
    if (!err){
        err = c_.setValue(nameKey,value);
    }
    return err;
}


std::pair<error, std::string> ConfigManager::loadValue(const std::string& nameKey){
    error err;
    auto result = c_.getValue(nameKey);
    return result;
}


 std::unordered_map<std::string,std::string*>& ConfigManager::loadValues(){
    return c_.getVault();
}
