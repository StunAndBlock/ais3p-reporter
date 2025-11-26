#include "internal/App/App.hpp"







int main(int argc, char* argv[]){
    error err;
    App app(argc, argv);
    err = app.startup();
    if (err) {
        return err.code();
    }

    return 0;
}