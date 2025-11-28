#include "internal/UI/BaseWin/BaseWin.hpp"

BaseWin::~BaseWin(){
    if (wnd_){
        XDestroyWindow(dpy_, wnd_);
    }
    if (gc_) {
        XFreeGC(dpy_, gc_);
    }
}

void BaseWin::init(Display* dpy, int scr){
    dpy_ = dpy;
    scr_ = scr;
}

void BaseWin::callback(XEvent& event){
    std::cout << "yay";
        switch (event.type) {
            case ClientMessage:
                // Window close request
                Atom wm_delete_window = XInternAtom(dpy_, "WM_DELETE_WINDOW", False);
                if (event.xclient.data.l[0] == wm_delete_window) {
                    
                }
                break;
        }

}

error::error BaseWin::create(const char* name){
    
        XSetWindowAttributes winAttr;
        winAttr.background_pixel = WhitePixel(dpy_, scr_);
        winAttr.event_mask = ExposureMask | KeyPressMask | 
                                ButtonPressMask | StructureNotifyMask;
        // Create window
        wnd_ = XCreateWindow(
            dpy_,
            RootWindow(dpy_, scr_),
            100, 100,          
            100, 100,      
            2,                  
            CopyFromParent,     
            InputOutput,        
            CopyFromParent,     
            CWBackPixel | CWEventMask,
            &winAttr
        );
        

        if (!wnd_){
            return error::errorf("[UI] Failed to create named window, original error lost, name: %s",name);
        }
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