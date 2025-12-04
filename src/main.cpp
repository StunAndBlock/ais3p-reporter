#include "internal/App/App.hpp"




int main(int argc, char* argv[]){
    error::error err;

    App app(argc, argv);
    err = app.bootstrap();
    if (err) {
        return err.code();
    }
    err = app.run();
    return err;
}