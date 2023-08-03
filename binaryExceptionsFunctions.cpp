/**
 * @file binaryExceptionsFunctions.cpp
 * @author Laila Staschenuk
 * @version 0.1
 * @date 2021-02-17
 */

#include "binaryExceptions.hpp"

Error::Error( std::string errThrown )
{
    errText = errThrown;
}

