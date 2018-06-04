#ifndef UITEMPLATE_H
#define UITEMPLATE_H

#include <string>
#include "../stdafx.h"

namespace FalconeEngine
{
    class UITemplate
    {
    public:
        UITemplate();

        virtual void print(std::string msg) = 0;
        virtual void clean() = 0;
        void printCMD(std::string msg);

        void printAll(std::string msg);

    };
}
#endif // UITEMPLATE_H
