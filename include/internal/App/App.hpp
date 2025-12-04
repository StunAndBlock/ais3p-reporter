#ifndef APP_HPP_
#define APP_HPP_

#include "internal/Data/ConfigManager.hpp"    
#include "internal/UI/UI.hpp"
#include "internal/Logger/Logger.hpp"
class App {
    public:
        App(int, char*[]);
        ~App() = default;
        error::error bootstrap();
        error::error run();
    private:
        logger::Logger log_;
        ConfigManager cm_;
        UI ui_;
    protected:
        
};





#endif //!APP_HPP