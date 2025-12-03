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
    log_.info("Bootstraping started");
    log_.debug().info("Bootstraping started");
    logger::LoggerChild l1 = log_.named("new name");
    l1.info("hi");
    logger::LoggerChild l2 = l1.named("test_test");
    l2.info("l2 info");
    l2.debug().info("l2 info");
    // logger::Logger* ln = log_.named("New tested");
    // ln->debug()->info("Creation of new logger");
    // delete ln;
    // log_.~Logger();
    // log_ = logger::Logger("App", logger::Core::LOGGER_LEVEL::PRODUCTION);
    // log_.named("UI FOR UI")->debug()->info("NO DEBUG ? :(");
    // err = cm_.init();
    // if (err) {
    //     if (err == ConfigIO::STATUS::NO_CFG_FILE){
    //         log_.info("First start triggered");
    //         err = this->firstStart("config.cfg");
    //         if (err) {
    //             return err;                
    //         } 
    //         err = cm_.init(); 
    //         if (err) {
    //             return err;                
    //         } 
    //         ui_.triggerFirstStart();
    //     } else {
    //         return err;
    //     }
    // }
  
    // err = cm_.start();
    // if (err) {
    //     return err;
    // }
    // err = ui_.init();
    // if (err) {
    //     return err;
    // }
    // err = ui_.dispatch();
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