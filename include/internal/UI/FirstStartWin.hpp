#include "internal/UI/BaseWin/BaseWin.hpp"
#include <X11/Xft/Xft.h>
class FirstStartWin : public BaseWin {
    public:
        FirstStartWin(Display*, int);
        ~FirstStartWin() = default;
        error::error create(const char*, Window) override;
        int callback(XEvent&) override;
    private:
        XftColor xftColor_;
        XftDraw* xftDraw_;
        XftFont* xftFont_;
};