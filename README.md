# Requestor

## About

Requestor is a library, which provides divided application-defined requests handling.

While C++ doesn't have reflection, Requestor is based on templates and concepts (which means C++ 20 or upper is required).

## Quick Setup

There are two ways to use this library.

- The first and simplest is to copy **`include/Requestor`** directly to your project.

- The second is to use CMake:
  - Create dependencies folder and clone Requestor:
    ```shell
    mkdir deps
    git submodule add 'https://github.com/toxicmouse7/Requestor.git' deps/requestor
    ```
  - In your CMakeLists.txt file add next lines:
    ```cmake
    add_subdirectory("deps/requestor")
    # ...
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE "Requestor")
    ```

## Quick Start

Requestor is used as singleton. All you have to do is to define requests and handlers

#### **`HelloWorldRequest.hpp`**
```c++
#ifndef HelloWorldRequest
#define HelloWorldRequest

#include <string>

#include <Requestor/Interfaces/IRequest.hpp>

class HelloWorldRequest : public IRequest
{
public:
    std::string message = "Hello, World!";
};

#endif // HelloWorldRequest
```

#### **`HelloWorldRequestHandler.hpp`**
```c++
#ifndef HelloWorldRequestHandler
#define HelloWorldRequestHandler

#include <string>
#include <iostream>

#include <Requestor/Interfaces/IRequestHandler.hpp>

#include "HelloWorldRequest.hpp"

// Here HelloWorldRequest is the request, which will be handled, and void is the return type of the handler
class HelloWorldRequestHandler : public IRequestHandler<HelloWorldRequest, void>
{
public:
    void Handle(const HelloWorldRequest& request) override
    {
        std::cout << request.message << std::endl;
    }
};

#endif // HelloWorldRequestHandler
```

#### **`main.cpp`**
```c++
#include <Requestor/Requestor.hpp>

#include "HelloWorldRequest.hpp"
#include "HelloWorldRequestHandler.hpp"

int main()
{
    // Get instance of requestor
    auto& requestor = Requestor::Instance();
    
    // Register your request handlers
    requestor.RegisterHandler<HelloWorldRequestHandler>();
    
    // Create request
    auto request = HelloWorldRequest();
    
    // Handle request
    requestor.Handle(request);
    
    return 0;
}
```

``Output: Hello, World!``

## A bit complex example

#### **`HelloRequest.hpp`**
```c++
#ifndef HelloRequest
#define HelloRequest

#include <string>

#include <Requestor/Interfaces/IRequest.hpp>

class HelloRequest : public IRequest
{
public:
    std::string format = "Hello, {0}!";
};

#endif // HelloRequest
```

#### **`HelloRequestHandler.hpp`**
```c++
#ifndef HelloRequestHandler
#define HelloRequestHandler

#include <string>
#include <iostream>
#include <format>

#include <Requestor/Interfaces/IRequestHandler.hpp>

#include "HelloRequest.hpp"

class HelloRequestHandler : public IRequestHandler<HelloRequest, std::string>
{
public:
    std::string Handle(const HelloRequest& request) override
    {
        std::string name;
        std::cin >> name;
        return std::format(request.format, name);
    }
};

#endif // HelloRequestHandler
```

#### **`main.cpp`**
```c++
#include <iostream>

#include <Requestor/Requestor.hpp>

#include "HelloRequest.hpp"
#include "HelloRequestHandler.hpp"

int main()
{
    // Get instance of requestor
    auto& requestor = Requestor::Instance();
    
    // Register your request handlers
    requestor.RegisterHandler<HelloRequestHandler>();
    
    // Create request
    auto request = HelloRequest();
    
    // Handle request
    auto result = requestor.Handle<std::string>(request);
    
    std::cout << result << std::endl;
    
    return 0;
}
```

```
Input: Tim
Output: Hello, Tim!
```
