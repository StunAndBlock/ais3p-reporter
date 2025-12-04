#include "internal/Data/ConfigManager.hpp"



ConfigManager::ConfigManager() : cIO_("config.cfg"){

}

error::error ConfigManager::init(){
    error::error err;
    err = cIO_.open();
    return err;
}


error::error ConfigManager::start(){
    error::error err;
    auto& vaultRef = c_.getVault();
    err = cIO_.readAll(vaultRef);
    return err;
}

error::error ConfigManager::firstStart(){
    error::error err;

    err = cIO_.firstStart();
    return err;
}

error::error ConfigManager::exit(){
    error::error err;
    err = cIO_.close();
    return err;
}


error::error ConfigManager::saveValue(const std::string& nameKey, const std::string& value){
    error::error err;
    std::string* backupValue;
    std::tie(err, backupValue) = c_.getValue(nameKey);
    err = c_.setValue(nameKey,value);
    if (err){
        return err;
    }
    err = cIO_.writeAll(c_.getVault());
    if (err){
        if (backupValue!=nullptr){
            c_.setValue(nameKey, *backupValue);
        }
        return err;
    }
    return err;
}


std::pair<error::error, std::string*> ConfigManager::loadValue(const std::string& nameKey){
    auto result = c_.getValue(nameKey);
    return result;
}


 std::unordered_map<std::string,std::string*>& ConfigManager::loadValues(){
    return c_.getVault();
}
