#ifndef MAIN_WIN_HPP_
#define MAIN_WIN_HPP_


#include "internal/UI/BaseWin/BaseWin.hpp"
#include <chrono>
#include <thread>
class MainWin : public BaseWin {
    public:
        MainWin(Display*, int);
        ~MainWin() = default;
        error::error create(const char*, Window = 0) override;
        int callback(XEvent&) override;
    private:
        XftColor xftColor_;
        XftDraw* xftDraw_;
        XftFont* xftFont_;

};












#endif //!MAIN_WIN_HPP_