#include <memory>

////////////////////////////////////////////////////////////////////////////////
class Computer {
public:
    virtual void Run() = 0;
    virtual void Stop() = 0;
    virtual ~Computer() {}; //!< Virtual dtor to ensure derived class's dtor runs
};
////////////////////////////////////////////////////////////////////////////////
class Laptop: public Computer
{
public:
    void Run() override {mHibernating = false;}; 
    void Stop() override {mHibernating = true;}; 
    virtual ~Laptop() {}; //!< Need virtual dtor since we have virtual functions
private:
    bool mHibernating; // Whether or not the machine is hibernating
};
////////////////////////////////////////////////////////////////////////////////
class Desktop: public Computer {
public:
    void Run() override {mOn = true;}; 
    void Stop() override {mOn = false;}; 
    virtual ~Desktop() {};
private:
    bool mOn; // Whether or not the machine has been turned on
};
////////////////////////////////////////////////////////////////////////////////
class ComputerFactory {
public:
    static std::shared_ptr<Computer> createNewComputer(const std::string &description) {
        if(description == "laptop")
            return std::make_shared<Laptop>();
        if(description == "desktop")
            return std::make_shared<Desktop>();
        return nullptr;
    }
};
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv) {
    ComputerFactory comp_factory;
    auto laptop = comp_factory.createNewComputer("laptop");
    auto desktop = comp_factory.createNewComputer("desktop");
}