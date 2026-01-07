#ifndef APP_HPP
#define APP_HPP

#include <wx/wx.h>

#include "config.hpp"

namespace Ez2note
{

class App : public wxApp
{
public:
    virtual bool OnInit();
    Config &getConfig();

private:
    Config config;
};

}

#endif // APP_HPP
