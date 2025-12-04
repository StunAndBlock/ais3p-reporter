#include "internal/UI/FirstStartWin.hpp"

FirstStartWin::FirstStartWin(Display* dpy, int scr) : BaseWin(dpy, scr){

}


error::error FirstStartWin::create(const char* name, Window parent){
        XSetWindowAttributes winAttr;
        winAttr.background_pixel = 0xbbbbbb;
        winAttr.border_pixel = 0x6495ED;
        winAttr.event_mask = ExposureMask | KeyPressMask | 
                                ButtonPressMask | StructureNotifyMask;
        wnd_ = XCreateWindow(
            dpy_,
            parent,
            200, 20,          
            400, 600-20-20,      
            0,                  
            CopyFromParent,     
            InputOutput,        
            CopyFromParent,     
            CWBackPixel | CWEventMask | CWBorderPixel,
            &winAttr
        );
        

        if (!wnd_){
            return error::errorf("[UI] Failed to create named window, original error lost, name: %s",name);
        }
        gc_ = XCreateGC(dpy_, wnd_, 0, nullptr);
        Visual* visual = DefaultVisual(dpy_, scr_);
        Colormap colormap = DefaultColormap(dpy_, scr_);
        xftDraw_ = XftDrawCreate(dpy_, wnd_, visual, colormap);
        XRenderColor renderColor = {48059, 48059, 48059, 65535};
        XftColorAllocValue(dpy_, visual, colormap, &renderColor, &xftColor_);
        xftFont_ = XftFontOpenName(dpy_, scr_, 
         "DejaVu Sans-10:italic");
        // if (!xftFont_) {
        //     xftFont_ = XftFontOpenName(dpy_, scr_, 
        //         "Liberation Sans:style=Italic:size=12");
        // }
        XStoreName(dpy_, wnd_, name);
        return error::null;
}

int FirstStartWin::callback(XEvent& event){
    switch (event.type)
    {
    case Expose:
        XSetForeground(dpy_, gc_, 0x6495ED);
        XSetBackground(dpy_, gc_, WhitePixel(dpy_, scr_));
        XSetLineAttributes(dpy_, gc_, 2, LineSolid, CapRound, JoinRound);
        XDrawLine(dpy_,wnd_,gc_,1,1,1,560);
        XDrawLine(dpy_,wnd_,gc_,399,1,399,560);
        XFillRectangle(dpy_, wnd_, gc_, 0, 50, 400, 20);
        XftDrawStringUtf8(xftDraw_, &xftColor_, xftFont_, 
                        -11, 65, (FcChar8*)"first start    \u00A6    ais3p-reporter    \u00A6    first start    \u00A6    ais3p-reporter", 80);
        break;
    case ButtonPress:
        return 1;
        break;
    
    default:
        break;
    }
    return 0;
}