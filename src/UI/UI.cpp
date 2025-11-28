#include "internal/UI/UI.hpp"


UI::UI(){
    isFirstStart_ = false;
    display_ = nullptr;
    screen_ = 0;
}

UI::~UI(){
    for (const auto& iPair : chain_){
        if (iPair.second!=nullptr){
            delete iPair.second;
        }
    }
    XCloseDisplay(display_);
}

void UI::triggerFirstStart(){
    isFirstStart_ = true;
}

error::error UI::init(){
    error::error err;
    display_ = XOpenDisplay(nullptr);
    if (display_ == nullptr){
        return error::error("Failed to create UI context, reason: failed to open display");
    }
    screen_ = DefaultScreen(display_);
    
    MainWin* mw = new MainWin();
    mw->init(display_,screen_);
    err = mw->create("Main");
    if (err){
        return err;
    }
    chain_[mw->getWindow()] = mw;
    

    mw->show();
    return err;
}


error::error UI::dispatch(){
    XEvent event;
    bool running = true;
    while (running) {
        XNextEvent(display_, &event);
        switch (event.type)
        {
        case FocusIn:
            chain_[event.xfocus.window]->callback(event);
            break;
        
        default:
            break;
        }
    }
    return error::null;
}