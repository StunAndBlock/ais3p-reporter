#ifndef BASE_WIN_HPP_
#define BASE_WIN_HPP_

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include  "internal/Error/Error.hpp"
#include <iostream>
class BaseWin {
    public:
        BaseWin() = default;
        ~BaseWin();
        virtual void callback(XEvent&);
        virtual error::error create(const char*);
        virtual void init(Display*, int);
        Window getWindow();
        virtual void show();
        virtual void hide();
    protected:
        Window wnd_;
        GC gc_;
        Display* dpy_;
        int scr_;
};








#endif //!BASE_WIN_HPP_