#include "internal/Data/Config.hpp"

Config::Config(){
    valuesVault_ = {
        {"username", nullptr},
    };
}

Config::~Config(){
    for (const auto& iPair : valuesVault_) {
        if (iPair.second != nullptr){
            delete iPair.second;
        }
    }
}
error Config::setValue(const std::string& nameKey,const std::string& value){
    if (valuesVault_.find(nameKey) == valuesVault_.end()){
        char* errmsg;
        sprintf(errmsg, "Unknown configuration: %s", nameKey.c_str());
        return error(UNKNOWN_CONFIGURATION, errmsg);
    }
    return error::null;


}


std::pair<error,std::string> Config::getValue(const std::string& nameKey){
    if (valuesVault_.find(nameKey) == valuesVault_.end()){
        char* errmsg;
        sprintf(errmsg, "Unknown configuration: %s", nameKey.c_str());
        return {error(UNKNOWN_CONFIGURATION, errmsg), nullptr};
    }
    std::string* valuePtr = nullptr;
    valuePtr = valuesVault_[nameKey];
    if (valuePtr == nullptr) {
        char* errmsg;
        sprintf(errmsg, "Empty value associated with: %s", nameKey.c_str());
        return {error(EMPTY_VALUE, errmsg), nullptr };
    }
    return {error::null, *valuePtr};
}

std::unordered_map<std::string,std::string*>& Config::getVault(){
    return valuesVault_;
}



