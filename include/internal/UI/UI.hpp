#ifndef UI_HPP_
#define UI_HPP_
#include "internal/UI/Common.hpp"
#include <unordered_map>
#include "internal/UI/MainWin.hpp"
class UI {
    public:
        UI();
        ~UI();
        error::error dispatch();
        error::error init();
        void triggerFirstStart();
    private:
        bool isFirstStart_;
        Display* display_;
        int screen_;
        std::unordered_map<Window,BaseWin*> chain_;

};

















#endif //!UI_HPP_