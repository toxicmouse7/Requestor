//
// Created by Aleksej on 22.04.2023.
//

#ifndef TRANSLATOR_IREQUESTHANDLER_HPP
#define TRANSLATOR_IREQUESTHANDLER_HPP

#include "IRequest.hpp"
#include "Requestor/Concepts.hpp"

template<class Request, typename Result>
requires Derived<IRequest, Request>
class IRequestHandler
{
public:
    using ResultType = Result;
    using RequestType = Request;

    virtual Result Handle(const Request& request) = 0;
    virtual ~IRequestHandler() = default;
};

#endif //TRANSLATOR_IREQUESTHANDLER_HPP