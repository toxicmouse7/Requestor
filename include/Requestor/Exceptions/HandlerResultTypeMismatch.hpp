//
// Created by Aleksej on 23.04.2023.
//

#ifndef TRANSLATOR_HANDLERRESULTTYPEMISMATCH_HPP
#define TRANSLATOR_HANDLERRESULTTYPEMISMATCH_HPP

#include <exception>
#include <string>
#include <fmt/format.h>

class HandlerResultTypeMismatch : public std::runtime_error
{
public:
    HandlerResultTypeMismatch(
            const std::string& handlerName, const std::string& rightType, const std::string& wrongType)
            : std::runtime_error(
            fmt::format(
                    "Result type for handler '{0}' is '{1}', but '{2}' was requested", handlerName, rightType,
                    wrongType).c_str())
    {}
};


#endif //TRANSLATOR_HANDLERRESULTTYPEMISMATCH_HPP
