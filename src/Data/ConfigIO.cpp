#include "internal/Data/ConfigIO.hpp"
#include <iostream>
ConfigIO::~ConfigIO(){
    for (const auto& iPair : valuesLocationVault_) {
        if (iPair.second != nullptr){
            delete iPair.second;
        }
    }
}

error ConfigIO::open(const std::filesystem::path cfgFP){
    fd_.open(cfgFP);
    if (!fd_.is_open()){
        if (errno == ENOENT) {
            return error(NO_CFG_FILE);
        } else {
            char* errmsg;
            sprintf(errmsg, "[IO] Failed to open cfg file, cfgFilePath: %s ,reason: %s",
                std::filesystem::absolute(cfgFP).string().c_str(), 
                std::strerror(errno));
            return error(errmsg);
        }
    }
    return error::null;
}

error ConfigIO::close(){
    if (!fd_.is_open()){
        return error("[IO] Failed to properly close cfg file, reason: decriptor lost file context");
    }
    fd_.close();
    if (!fd_.good()){
        char* errmsg;
        sprintf(errmsg, "[IO] Failed to properly close cfg file, reason: %s", std::strerror(errno));
        return error(errmsg);
    }
    return error::null;
}

// error ConfigIO::readAll(std::unordered_map<std::string, std::string*>& valuesVault){
//     std::string currentKey;
//     char ch;

//     fd_.seekg(0);
//     std::streampos keyStart = fd_.tellg();
//     std::streampos lineStart = keyStart;
//     std::streampos eqCharPos = 0;
//     std::streampos current = keyStart;
//     std::streampos delimeterPos;
//     bool eqCharFoundFlag = false;
//     while (fd_.get(ch)) {
//         if (ch == eqChar_){
//             eqCharFoundFlag = true;
//             eqCharPos = current; 
//         } else if (ch == delimeter_ && eqCharFoundFlag){
//             delimeterPos = current; 
//             std::streamoff keyLen = (eqCharPos - 1) - lineStart;  
//             std::streamoff valueLen = (delimeterPos - 1) - eqCharPos; 
//             if (keyLen > 0 && valueLen > 0) {
//                 fd_.seekg(lineStart);
//                 std::string key(keyLen, '\0');
//                 fd_.read(&key[0], keyLen);
//                 if (valuesVault.find(key) != valuesVault.end()){
//                     std::streampos valueStartPos = eqCharPos + 1;
//                     fd_.seekg(valueStartPos);
//                     std::string value(valueLen, '\0');
//                     fd_.read(&value[0], valueLen);
//                     valuesVault[key] = new std::string(key);
//                     valuesLocationVault_[key] = new std::streampos(valueStartPos);
//                 }
//             }
//             lineStart = current;  
//             eqCharFoundFlag = false;  
//         } else if (ch == '\n') {
//             lineStart = current;  
//             eqCharFoundFlag = false;
//         }
//         current = fd_.tellg();
//     }
//     return error::null;
// }


error ConfigIO::readAll(std::unordered_map<std::string, std::string*>& valuesVault){
    const std::streamsize MAX_LINE_LEN = 255;
    std::streampos current = fd_.tellg();

    size_t pos;
    char lineRaw[MAX_LINE_LEN];
    while (fd_.getline(lineRaw, MAX_LINE_LEN)){
        
        std::string line(lineRaw);
        size_t eqCharPos = line.find_first_of(eqChar_);
        if (eqCharPos != std::string::npos){
            std::size_t keyLen= abs(eqCharPos - current);
            if (keyLen > 1){
                std::string key = line.substr(current, keyLen);
                size_t delimeterPos = line.find_first_of(delimeter_);
                if (delimeterPos != std::string::npos){
                    std::size_t valueLen = abs(delimeterPos - eqCharPos - 1);
                    if (valueLen > 1){
                        std::string value = line.substr(eqCharPos + 1, valueLen);
                        valuesVault[key] = new std::string(value);
                        valuesLocationVault_[key] = new std::streampos(current);
                    }
                }
            }
            
        }

        current += line.length();
    }
    return error::null;
}

error ConfigIO::writeValue(const std::string& cfgKey, const std::string& value){
    if (valuesLocationVault_.find(cfgKey) == valuesLocationVault_.end()){
        char* errmsg;
        sprintf(errmsg, "[IO] Failed to write value to cfg file, reason: no position associated with this name, cfgKey: %s", cfgKey.c_str());
        return error(errmsg);
    }
    std::streampos* posPtr = valuesLocationVault_[cfgKey];
    if (posPtr == nullptr){
        char* errmsg;
        sprintf(errmsg, "[IO] Failed to write value to cfg file, reason: position associated with key is empty, cfgKey: %s", cfgKey.c_str());
        return error(errmsg);
    }
    fd_.seekp(*posPtr);
    char* line;
    sprintf(line,"%s=%s;\n",cfgKey.c_str(),value.c_str());
    fd_.write(line, cfgKey.length() + value.length() + 3U);
    if (!fd_.good()){
        char* errmsg;
        sprintf(errmsg, "[IO] Failed to write value to cfg file, reason: %s, cfgKey: %s", std::strerror(errno), cfgKey.c_str());
        return error(errmsg);
    }
    return error::null;
}
