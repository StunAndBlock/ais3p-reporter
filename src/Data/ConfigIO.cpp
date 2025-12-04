#include "internal/Data/ConfigIO.hpp"
#include <iostream>
#include <fcntl.h>
ConfigIO::ConfigIO(std::filesystem::path fn){
    fn_ = fn;
}


ConfigIO::~ConfigIO(){

}

error::error ConfigIO::open(){
    fd_.open(fn_);
    if (!fd_.is_open()){
        if (errno == ENOENT) {
            return error::error(NO_CFG_FILE);
        } else {
            return error::errorf("[IO] Failed to open cfg file, cfgFilePath: %s ,reason: %s",
                std::filesystem::absolute(fn_).string().c_str(),
                std::strerror(errno)
            );
        }
    }
    return error::null;
}


error::error ConfigIO::firstStart(){
    fd_.open(fn_, std::ios::out);
    if (!fd_.is_open()){

    }
    return error::null;
}

error::error ConfigIO::close(){
    if (!fd_.is_open()){
        return error::error("[IO] Failed to properly close cfg file, reason: decriptor lost file context");
    }
    fd_.close();
    // if (!fd_.good()){
    //     char errmsg[strlen("[IO] Failed to properly close cfg file, reason: %s") + strlen(std::strerror(errno))];
       
    //     sprintf(errmsg, "[IO] Failed to properly close cfg file, reason: %s", std::strerror(errno));
    //      std::cout << errmsg;
    //     return error(errmsg);
    // }
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


error::error ConfigIO::readAll(std::unordered_map<std::string, std::string*>& valuesVault){
    const std::streamsize MAX_LINE_LEN = 255;
    size_t pos;
    char lineRaw[MAX_LINE_LEN];
    while (fd_.getline(lineRaw, MAX_LINE_LEN)){
       
        std::string line(lineRaw);
        size_t eqCharPos = line.find_first_of(eqChar_);
        //std::cout << eqCharPos << '\n';
        if (eqCharPos != std::string::npos){
            std::size_t keyLen= eqCharPos;
            //std::cout << keyLen << '\n';
            if (keyLen > 0){
                std::string key = line.substr(0, keyLen);
                //std::cout << key << '\n';
                size_t delimeterPos = line.find_first_of(delimeter_);
                if (delimeterPos != std::string::npos){
                    std::size_t valueLen = abs(delimeterPos - eqCharPos - 1);
                    //std::cout << "vl: " << valueLen << '\n';
                    if (valueLen > 0){
                        std::string value = line.substr(eqCharPos + 1, valueLen);
                        if (valuesVault.find(key) !=valuesVault.end()){
                            valuesVault[key] = new std::string(value);
                        }
                    }
                }
            }
            
        }
    }
    return error::null;
}

// error ConfigIO::writeValue(const std::string& cfgKey, const std::string& value){
//     if (valuesLocationVault_.find(cfgKey) == valuesLocationVault_.end()){
//         char* errmsg;
//         sprintf(errmsg, "[IO] Failed to write value to cfg file, reason: no position associated with this name, cfgKey: %s", cfgKey.c_str());
//         return error(errmsg);
//     }
//     size_t* lineNumberPtr = valuesLocationVault_[cfgKey];
//     if (lineNumberPtr == nullptr){
//         char* errmsg;
//         sprintf(errmsg, "[IO] Failed to write value to cfg file, reason: position associated with key is empty, cfgKey: %s", cfgKey.c_str());
//         return error(errmsg);
//     }
//     fd_.seekg(0, std::ios::beg);
//     for(size_t i = 0; i++; i < *lineNumberPtr){
//         fd_.getline()
//     }
//     char* line;
//     sprintf(line,"%s=%s;\n",cfgKey.c_str(),value.c_str());
//     fd_.write(line, cfgKey.length() + value.length() + 3U);
//     if (!fd_.good()){
//         char* errmsg;
//         sprintf(errmsg, "[IO] Failed to write value to cfg file, reason: %s, cfgKey: %s", std::strerror(errno), cfgKey.c_str());
//         return error(errmsg);
//     }
//     return error::null;
// }


error::error ConfigIO::writeAll(std::unordered_map<std::string,std::string*>& vault){
    this->close();
    fd_.open(fn_, std::ios::out | std::ios::trunc);

    for(const auto& iPair : vault){
        if (iPair.second != nullptr){
            char line[iPair.first.length() + iPair.second->length() + 3U];
            sprintf(line,"%s=%s;\n",iPair.first.c_str(),iPair.second->c_str());
            fd_.write(line, iPair.first.length() + iPair.second->length() + 3U);
            if (!fd_.good()){
                return error::errorf("[IO] Failed to write value to cfg file, reason: %s, cfgKey: %s",
                    std::strerror(errno),
                    iPair.first.c_str()
                );
            }
        }
    }
    this->close();
    this->open();
    // if (valuesLocationVault_.find(cfgKey) == valuesLocationVault_.end()){
    //     char* errmsg;
    //     sprintf(errmsg, "[IO] Failed to write value to cfg file, reason: no position associated with this name, cfgKey: %s", cfgKey.c_str());
    //     return error(errmsg);
    // }
    // size_t* lineNumberPtr = valuesLocationVault_[cfgKey];
    // if (lineNumberPtr == nullptr){
    //     char* errmsg;
    //     sprintf(errmsg, "[IO] Failed to write value to cfg file, reason: position associated with key is empty, cfgKey: %s", cfgKey.c_str());
    //     return error(errmsg);
    // }
    // fd_.seekg(0, std::ios::beg);
    // for(size_t i = 0; i++; i < *lineNumberPtr){
    //     fd_.getline()
    // }
    // char* line;
    // sprintf(line,"%s=%s;\n",cfgKey.c_str(),value.c_str());
    // fd_.write(line, cfgKey.length() + value.length() + 3U);
    // if (!fd_.good()){
    //     char* errmsg;
    //     sprintf(errmsg, "[IO] Failed to write value to cfg file, reason: %s, cfgKey: %s", std::strerror(errno), cfgKey.c_str());
    //     return error(errmsg);
    // }
    return error::null;
}
