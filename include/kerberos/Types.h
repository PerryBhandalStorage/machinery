//
//  Class: Types
//  Description: Type definitions
//  Created:     17/07/2014
//  Author:      Cédric Verstraeten
//  Mail:        hello@cedric.ws
//  Website:     www.kerberos.io
//
//  The copyright to the computer program(s) herein
//  is the property of kerberos.io, Belgium.
//  The program(s) may be used and/or copied .
//
/////////////////////////////////////////////////////

#ifndef __Types_H_INCLUDED__   // if Types.h hasn't been included yet...
#define __Types_H_INCLUDED__   // #define this so the compiler knows it has been included

#include <string>
#include <vector>
#include <map>
#include "document.h"

namespace kerberos
{
    class Rectangle
    {
        public:
            int m_x1, m_x2;
            int m_y1, m_y2;
            Rectangle(){};
            Rectangle(int x1, int y1, int x2, int y2):m_x1(x1),m_y1(y1),m_x2(x2),m_y2(y2){};
    };
    
    template<class T, class K>
    class tuple
    {
        public:
            T t;
            K k;
            tuple(T t, K k):k(k),t(t){};
    };
    
    class Image;
    typedef std::vector<Image *> ImageVector;
    
    typedef std::map<std::string,std::string> StringMap;
    
    typedef tuple<int,Rectangle> Region;
    typedef std::vector<Region> RegionVector;
    typedef rapidjson::Document JSON;
    typedef rapidjson::Value JSONValue;
}
#endif
