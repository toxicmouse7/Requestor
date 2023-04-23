//
// Created by Aleksej on 23.04.2023.
//

#ifndef TRANSLATOR_REQUESTOR_HPP
#define TRANSLATOR_REQUESTOR_HPP

#include <iostream>
#include <map>
#include <typeindex>
#include <string>

#include "Interfaces/IRequest.hpp"
#include "Interfaces/IRequestHandler.hpp"
#include "RequestHandlerFactory.hpp"
#include "Concepts.hpp"
#include "Exceptions/HandlerNotFound.hpp"
#include "Exceptions/HandlerAlreadyRegistered.hpp"

class Requestor
{
private:
    inline static Requestor* instance = nullptr;

    Requestor() = default;

    std::map<std::type_index, std::string> requestHandlers;

    RequestHandlerFactory requestHandlerFactory;

public:
    Requestor(const Requestor& requestor) = delete;

    Requestor operator=(const Requestor& requestor) = delete;

    static Requestor& Instance()
    {
        if (instance == nullptr)
            instance = new Requestor();

        return *instance;
    }

    template<typename Result, class Request>
    requires Derived<IRequest, Request>
    Result Handle(const Request& request)
    {
        if (!requestHandlers.contains(std::type_index(typeid(Request))))
            throw HandlerNotFound(typeid(Request).name());

        auto& handlerName = requestHandlers.at(std::type_index(typeid(Request)));
        auto* handler = requestHandlerFactory.Create<Request, Result>(handlerName);
        auto result = handler->Handle(request);
        delete handler;
        return result;
    }

    template<class Request>
    requires Derived<IRequest, Request>
    void Handle(const Request& request)
    {
        if (!requestHandlers.contains(std::type_index(typeid(Request))))
            throw HandlerNotFound(typeid(Request).name());

        auto& handlerName = requestHandlers.at(std::type_index(typeid(Request)));
        auto* handler = requestHandlerFactory.Create<Request, void>(handlerName);
        handler->Handle(request);
        delete handler;
    }

    template<class RequestHandler, class Request = typename RequestHandler::RequestType, typename Result = typename RequestHandler::ResultType>
    requires Derived<IRequestHandler<Request, Result>, RequestHandler>
    void RegisterHandler()
    {
        if (requestHandlers.contains(std::type_index(typeid(Request))))
            throw HandlerAlreadyRegistered(
                    requestHandlers[std::type_index(typeid(Request))], typeid(Request).name());

        requestHandlers[std::type_index(typeid(Request))] = typeid(RequestHandler).name();
        requestHandlerFactory.RegisterType<RequestHandler>();
    }

};

#endif //TRANSLATOR_REQUESTOR_HPP
