/**
 * @file binaryExceptions.hpp
 * @author Laila Staschenuk
 * @version 0.1
 * @date 2021-02-17
 */

#pragma once

#include <string>

/**
 * @class Error
 * @brief very rudimental Error class
 * @details uses parameterized constructor to assingn error messages to runtime errors
 */
class Error
{
    public:

    /**
     * @brief Construct a new Error object, parameterized constructor 
     * @param errThrown > errormessage will be displayed to user in occuring runtime error, is assigned to errText
     */
    Error( std::string errThrown );

    std::string errText;
};

