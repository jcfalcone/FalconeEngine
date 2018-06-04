#include "uitemplate.h"

#include <iostream>
#include "../stdafx.h"

namespace FalconeEngine
{
    UITemplate::UITemplate()
    {

    }

    void UITemplate::printCMD(std::string msg)
    {
        std::cout << msg << std::endl;
    }

    void UITemplate::printAll(std::string msg)
    {
        this->print(msg);
        this->printCMD(msg);
    }
}
