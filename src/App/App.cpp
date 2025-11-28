#include "internal/App/App.hpp"
#include <iostream>

App::App(int argc, char* argv[]){


}


error::error App::bootstrap(){
    error::error err;
    log_.info("Bootstraping started");
    err = cm_.init();
    if (err) {
        if (err == ConfigIO::STATUS::NO_CFG_FILE){
            log_.info("First start triggered");
            err = this->firstStart("config.cfg");
            if (err) {
                return err;                
            } 
            err = cm_.init(); 
            if (err) {
                return err;                
            } 
            ui_.triggerFirstStart();
        } else {
            return err;
        }
    }
  
    err = cm_.start();
    if (err) {
        return err;
    }
    auto res = cm_.loadValue("applevel");
    log_.setLevel(*res.second);
    err = ui_.init();
    if (err) {
        return err;
    }
    err = ui_.dispatch();
    return err;
}



error::error App::firstStart(std::filesystem::path cfgFN){
    error::error err;
    std::ofstream file(cfgFN);
    if (!file.is_open()) {
        char* errmsg;
        sprintf(errmsg, "[APP] Failed to create configuration file on first start, reason %s",std::strerror(errno));
        return error::error(errmsg);
    }
    file.close();
    if (!file.good()){
        char* errmsg;
        sprintf(errmsg, "[APP] Failed to close configuration file on first start, reason %s",std::strerror(errno));
        return error::error(errmsg);
    }
    return error::null;
}