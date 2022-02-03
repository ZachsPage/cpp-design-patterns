#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <memory>

////////////////////////////////////////////////////////////////////////////////
//! The Handler interface
class HandlerIntfc {
public:
    virtual bool Handle(std::string request) = 0; //!< Function to handle a request
};
////////////////////////////////////////////////////////////////////////////////
//! Handler to create the chain, and call each HandlerIntfc implementation...
//! - (Not technically the pattern - see the readme note)
class Handler : public HandlerIntfc {
public:
    //! Add a new handler to a chain 
    //! @return This obj so we can make one big AddNew()...AddNew()...AddNew()...
    template<typename T>
    Handler& AddNew() {
        static_assert(std::is_base_of<HandlerIntfc, T>::value,
                        "AddNew must be called with implementor of HandlerIntfc!");
        _chain.emplace_back( new T );
        return *this;
    }
    // Calls each handler until one handles the request
    bool Handle(std::string request) override {
        for( auto& handler : _chain ) {
            if( handler->Handle(request) ) return true;
        }
        return false;
    }
private:
    std::list< std::unique_ptr<HandlerIntfc> > _chain;
};
// Handler implementations 
////////////////////////////////////////////////////////////////////////////////
class MonkeyHandler : public HandlerIntfc {
public:
    bool Handle(std::string request) override {
        if( request != "Banana" ) return false;
        std::cout << "Monkey: I'll eat the " + request + ".\n";
        return true;
    }
};
class SquirrelHandler : public HandlerIntfc {
public:
    bool Handle(std::string request) override {
        if( request != "Nut" ) return false;
        std::cout << "Squirrel: I'll eat the " + request + ".\n";
        return true;
    }
};
class DogHandler : public HandlerIntfc {
public:
    bool Handle(std::string request) override {
        if( request != "MeatBall" ) return false;
        std::cout << "Dog: I'll eat the " + request + ".\n";
        return true;
    }
};
////////////////////////////////////////////////////////////////////////////////
// Client to use handlers. Though, it most cases, the client is suited to work 
// with a single handler and does not know about the rest of the chain
class Client {
public:
    Client() {
        _our_handler.AddNew<MonkeyHandler>().AddNew<SquirrelHandler>().AddNew<DogHandler>();
    }

    void RunThroughRequests() {
        std::vector<std::string> foods = {"Nut", "Banana", "Cup of coffee"};
        for(const auto& food : foods ) {
            std::cout << "Client: Who wants a " << food << "?\n";
            if( not _our_handler.Handle(food) )
                std::cout << "  " << food << " was left untouched.\n";
        }
    }
private:
    Handler _our_handler;
};
////////////////////////////////////////////////////////////////////////////////
int main() {
    Client new_client;
    new_client.RunThroughRequests();
    return 0;
}