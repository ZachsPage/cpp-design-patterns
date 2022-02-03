#include <string>
#include <iostream>
#include <memory>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
//! Abstract base class that `decorators` will expand upon
class Car {
protected:
    string _str;
public:
    Car() { _str = "Unknown Car"; }
    virtual ~Car() {}
    virtual string getDescription() { return _str; }
    virtual double getCost() = 0;
};
////////////////////////////////////////////////////////////////////////////////
//! Concrete implementation for the base class
class CarModel1 : public Car {       
public:
    CarModel1() { _str = "CarModel1"; }
    virtual ~CarModel1(){}
    virtual double getCost() { return 31000.23; }
};
////////////////////////////////////////////////////////////////////////////////
//! Decorator base class for Car
class OptionsDecorator : public Car {
public:
    virtual string getDescription() override = 0;
    virtual ~OptionsDecorator() {}
};
////////////////////////////////////////////////////////////////////////////////
//! Decorator class
class Navigation: public OptionsDecorator {
    std::shared_ptr<Car> _car;
public:
    Navigation(std::shared_ptr<Car> car) { _car = car; }
    string getDescription() override { return _car->getDescription() + ", Navigation"; }
    double getCost() { return 300.56 + _car->getCost(); }
};
////////////////////////////////////////////////////////////////////////////////
//! Decorator class
class PremiumSoundSystem: public OptionsDecorator {
    std::shared_ptr<Car> _car;
public:
    PremiumSoundSystem(std::shared_ptr<Car> car) { _car = car; }
    string getDescription() { return _car->getDescription() + ", PremiumSoundSystem"; }
    double getCost() { return 0.30 + _car->getCost(); }
};
////////////////////////////////////////////////////////////////////////////////
//! Decorator class
class ManualTransmission: public OptionsDecorator {
    std::shared_ptr<Car> _car;
public:
    ManualTransmission(std::shared_ptr<Car> car) { _car = car; }
    string getDescription() { return _car->getDescription()+ ", ManualTransmission"; }
    double getCost() { return 0.30 + _car->getCost(); }
};
////////////////////////////////////////////////////////////////////////////////
int main()
{
    // Instantiate base class pointer to concrete implementation
    std::shared_ptr<Car> car = std::make_shared<CarModel1>();
    cout << "Base model of " << car->getDescription() << 
            " costs $" << car->getCost() << "\n";  
        
    // Pass in current object to create a new decorated object + print new desc / cost
    car = std::make_shared<Navigation>(car);
    cout << car->getDescription() << " will cost you $" << car->getCost() << "\n";
    car = std::make_shared<PremiumSoundSystem>(car);
    car = std::make_shared<ManualTransmission>(car);
    cout << car->getDescription() << " will cost you $" << car->getCost() << "\n";

    return 0;
}