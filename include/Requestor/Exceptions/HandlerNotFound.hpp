//
// Created by Aleksej on 23.04.2023.
//

#ifndef TRANSLATOR_HANDLERNOTFOUND_HPP
#define TRANSLATOR_HANDLERNOTFOUND_HPP

#include <exception>
#include <string>
#include <format>

class HandlerNotFound : public std::runtime_error
{
public:
    explicit HandlerNotFound(const std::string& handlerName)
        : std::runtime_error(fmt::format("Handler for '{0}' request was not found", handlerName).c_str())
    {

    }
};

#endif //TRANSLATOR_HANDLERNOTFOUND_HPP
