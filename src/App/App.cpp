#include "internal/App/App.hpp"
#include <iostream>

App::App(int argc, char* argv[]) : log_("App", logger::Core::LOGGER_LEVEL::PRODUCTION){
    std::unordered_map<std::string, logger::Core::LOGGER_LEVEL> opts = {
        {"--dev", logger::Core::LOGGER_LEVEL::DEVELOPMENT},
        {"--debug", logger::Core::LOGGER_LEVEL::DEBUG},
    };
    
    if (argc > 1){
        if (const auto& it = opts.find(argv[1]); it!= opts.end()){
            log_ = logger::Logger("App",it->second);
        }
    } 
}

error::error App::bootstrap(){
    error::error err;
    err = cm_.init();
    ui_.triggerFirstStart();
    if (err) {
        if (err == ConfigIO::STATUS::NO_CFG_FILE){
            log_.info("First start detected");
            err = cm_.firstStart();
            if (err) {
                return err;                
            } 
            ui_.triggerFirstStart();
        } else {
            return err;
        }
    } else {
        err = cm_.start();
        if (err) {
            return err;
        }
    }
    err = ui_.init();
    if (err) {
        return err;
    }
    return err;
}

error::error App::run(){
    error::error err;
    err = ui_.dispatch();
    return err;
}