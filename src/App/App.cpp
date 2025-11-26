#include "internal/App/App.hpp"
#include <iostream>

App::App(int argc, char* argv[]){


}


error App::startup(){
    error err;
    err = cm_.init("config.cfg");
    if (err) {
        if (err == ConfigIO::Status::NO_CFG_FILE){
            err = this->firstStart("config.cfg");
            if (err) {
                return err;                
            } 
            err = cm_.init("config.cfg"); 
            if (err) {
                return err;                
            } 
        } else {
            return err;
        }
    }
    err = cm_.start();
    if (err) {
        return err;
    }
    std::string value;
    std::tie(err, value) = cm_.loadValue("username");
    std::cout << value;
    return err;
}



error App::firstStart(std::filesystem::path cfgFN){
    std::ofstream file(cfgFN);
    if (!file.is_open()) {
        char* errmsg;
        sprintf(errmsg, "[APP] Failed to create configuration file on first start, reason %s",std::strerror(errno));
        return error(errmsg);
    }
    file << "username=default;\n";
    file.close();
    if (!file.good()){
        char* errmsg;
        sprintf(errmsg, "[APP] Failed to close configuration file on first start, reason %s",std::strerror(errno));
        return error(errmsg);
    }
    return error::null;
}