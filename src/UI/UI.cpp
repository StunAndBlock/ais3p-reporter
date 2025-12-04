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
    if (display_){
        XCloseDisplay(display_);
    }
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
    
    MainWin* mWdn = new MainWin(display_, screen_);
    err = mWdn->create("Main");
    if (err){
        return err;
    }
    chain_[mWdn->getWindow()] = mWdn;
    mWdn->show();
    if(isFirstStart_){
        FirstStartWin* firstStartWnd = new FirstStartWin(display_, screen_);
        err = firstStartWnd->create("First start", mWdn->getWindow());
            if (err){
                return err;
            }
        chain_[firstStartWnd->getWindow()] = firstStartWnd;
        firstStartWnd->show();
    }
    return err;
}


error::error UI::dispatch(){
    XEvent event;
    bool running = true;
    int code = 0;
    while (running) {
        XNextEvent(display_, &event);
        code = chain_[event.xfocus.window]->callback(event);
        if (code == 1){
            return error::null;
        }
    }
    return error::null;
}