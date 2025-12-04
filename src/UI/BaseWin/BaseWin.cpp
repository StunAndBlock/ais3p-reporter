#include "internal/UI/BaseWin/BaseWin.hpp"

BaseWin::~BaseWin(){
    if (wnd_){
        XDestroyWindow(dpy_, wnd_);
    }
    if (gc_) {
        XFreeGC(dpy_, gc_);
    }
}
BaseWin::BaseWin(Display* dpy, int scr){
    dpy_ = dpy;
    scr_ = scr;
}



error::error BaseWin::create(const char* name = "GenericWindow",Window parent = 0){
    
        XSetWindowAttributes winAttr;
        winAttr.background_pixel = WhitePixel(dpy_, scr_);
        // Create window
        wnd_ = XCreateWindow(
            dpy_,
            RootWindow(dpy_, scr_),
            100, 100,          
            800, 600,      
            2,                  
            CopyFromParent,     
            InputOutput,        
            CopyFromParent,     
            CWBackPixel,
            &winAttr
        );
        

        if (!wnd_){
            return error::errorf("[UI] Failed to create named window, original error lost, name: %s",name);
        }
        gc_ = XCreateGC(dpy_, wnd_, 0, nullptr);
        XStoreName(dpy_, wnd_, name);

        return error::null;
}

Window BaseWin::getWindow(){
    return wnd_;
}

void BaseWin::show(){
    XMapWindow(dpy_,wnd_);
}

void BaseWin::hide(){
    XUnmapWindow(dpy_,wnd_);
}