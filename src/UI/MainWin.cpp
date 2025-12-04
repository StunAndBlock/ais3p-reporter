#include "internal/UI/MainWin.hpp"


MainWin::MainWin(Display* dpy, int scr) : BaseWin(dpy, scr){

}


error::error MainWin::create(const char* name, Window parent ){
        XSetWindowAttributes winAttr;
        winAttr.background_pixel = 0xbbbbbb;
        winAttr.event_mask = ExposureMask | KeyPressMask | 
                                ButtonPressMask | StructureNotifyMask;
        wnd_ = XCreateWindow(
            dpy_,
            RootWindow(dpy_, scr_),
            100, 100,          
            800, 600,      
            0,                  
            CopyFromParent,     
            InputOutput,        
            CopyFromParent,     
            CWBackPixel | CWEventMask,
            &winAttr
        );
        
        
        if (!wnd_){
            return error::errorf("[UI] Failed to create named window, original error lost, name: %s",name);
        }
        gc_ = XCreateGC(dpy_, wnd_, 0, nullptr);
        XStoreName(dpy_, wnd_, name);
        Visual* visual = DefaultVisual(dpy_, scr_);
        Colormap colormap = DefaultColormap(dpy_, scr_);
        xftDraw_ = XftDrawCreate(dpy_, wnd_, visual, colormap);
        XRenderColor renderColor = {48059, 48059, 48059, 65535};
        XftColorAllocValue(dpy_, visual, colormap, &renderColor, &xftColor_);
        xftFont_ = XftFontOpenName(dpy_, scr_, 
         "DejaVu Sans-10:italic");
        return error::null;
}


int MainWin::callback(XEvent& event){

    switch (event.type)
    {
    case Expose:
        XSetForeground(dpy_, gc_, 0x6495ED);
        XSetBackground(dpy_, gc_, WhitePixel(dpy_, scr_));
        XSetLineAttributes(dpy_, gc_, 2, LineSolid, CapRound, JoinRound);
        XDrawLine(dpy_,wnd_,gc_,1,1,1,600);
        XDrawLine(dpy_,wnd_,gc_,799,1,799,600);
        XFillRectangle(dpy_, wnd_, gc_, 0, 180, 800, 20);
        XFillRectangle(dpy_, wnd_, gc_, 0, 280, 800, 20);
        XFillRectangle(dpy_, wnd_, gc_, 0, 380, 800, 20);
        XftDrawStringUtf8(xftDraw_, &xftColor_, xftFont_, -323, 195, 
        (FcChar8*)"ais3p-reporter    \u00A6    hello    \u00A6    ais3p-reporter    \u00A6    where am i    \u00A6    ais3p-reporter    \u00A6    are you here to create report ?    \u00A6    ais3p-reporter    \u00A6    hello    \u00A6    ais3p-reporter    \u00A6    where am i    \u00A6    ais3p-reporter    \u00A6    are you here to create report ?    \u00A6    ", 296);
        XftDrawStringUtf8(xftDraw_, &xftColor_, xftFont_, -691, 295, 
        (FcChar8*)"ais3p-reporter    \u00A6    hello    \u00A6    ais3p-reporter    \u00A6    where am i    \u00A6    ais3p-reporter    \u00A6    are you here to create report ?    \u00A6    ais3p-reporter    \u00A6    hello    \u00A6    ais3p-reporter    \u00A6    where am i    \u00A6    ais3p-reporter    \u00A6    are you here to create report ?    \u00A6    ", 296);
        XftDrawStringUtf8(xftDraw_, &xftColor_, xftFont_, -5, 395, 
        (FcChar8*)"ais3p-reporter    \u00A6    hello    \u00A6    ais3p-reporter    \u00A6    where am i    \u00A6    ais3p-reporter    \u00A6    are you here to create report ?    \u00A6    ais3p-reporter", 162);
        break;
    case ButtonPress:
        return 1;
        break;
    
    default:
        break;
    }

    return 0;
}