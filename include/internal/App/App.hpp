#ifndef APP_HPP_
#define APP_HPP_

#include "internal/Data/ConfigManager.hpp"    

class App {
    public:
        error startup();
        error firstStart(std::filesystem::path);
        App(int, char*[]);
        ~App() = default;
    private:
        ConfigManager cm_;
    protected:
        
};





#endif //!APP_HPP