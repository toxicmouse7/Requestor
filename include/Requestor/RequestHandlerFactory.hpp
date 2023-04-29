//
// Created by Aleksej on 23.04.2023.
//

#ifndef TRANSLATOR_REQUESTHANDLERFACTORY_HPP
#define TRANSLATOR_REQUESTHANDLERFACTORY_HPP

#include <string>
#include <functional>
#include <map>

#include "deps/requestor/include/Requestor/Interfaces/IRequest.hpp"
#include "deps/requestor/include/Requestor/Interfaces/IRequestHandler.hpp"
#include "Concepts.hpp"
#include "deps/requestor/include/Requestor/Exceptions/HandlerResultTypeMismatch.hpp"

class RequestHandlerFactory
{
private:
    std::map<std::string, std::function<void*()>> handlerBuilders{};
    std::map<std::string, std::string> handlerResultTypes{};
public:
    template<class Request, typename Result>
    requires Derived<IRequest, Request>
    IRequestHandler<Request, Result>* Create(const std::string& requestHandlerName)
    {
        if (handlerResultTypes[requestHandlerName] != typeid(Result).name())
            throw HandlerResultTypeMismatch(
                    requestHandlerName, handlerResultTypes[requestHandlerName], typeid(Result).name());

        return reinterpret_cast<IRequestHandler<Request, Result>*>(handlerBuilders[requestHandlerName]());
    }

    template<class RequestHandler, class Request = typename RequestHandler::RequestType, typename Result = typename RequestHandler::ResultType>
    requires Derived<IRequestHandler<Request, Result>, RequestHandler>
    void RegisterType()
    {
        auto typeBuilder = []()
        {
            return new RequestHandler();
        };

        handlerBuilders[typeid(RequestHandler).name()] = typeBuilder;
        handlerResultTypes[typeid(RequestHandler).name()] = typeid(Result).name();
    }
};

#endif //TRANSLATOR_REQUESTHANDLERFACTORY_HPP
