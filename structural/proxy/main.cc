#include <iostream>
#include <memory>

////////////////////////////////////////////////////////////////////////////////
//! Interface class shared between proxy / real implementations
class CarIntfc {
public:
    virtual void DriveCar() = 0;
    virtual ~CarIntfc() {}
};
////////////////////////////////////////////////////////////////////////////////
//! Real implementation
class Car : public CarIntfc {
public:
    void DriveCar() override { std::cout << "Car has been driven!" << std::endl; }
};
////////////////////////////////////////////////////////////////////////////////
//! Proxy implementation to abstract real implementation until condition is met
class ProxyCar : public CarIntfc {
public:
    ProxyCar(int driver_age) : driver_age_(driver_age) {}
    void OwnerHasBirthday() { std::cout << "Happy birthday!\n"; driver_age_++; }
    void DriveCar() override {
        if( driver_age_ < 16 ) {
            std::cout << "Sorry, the driver is too young to drive." << std::endl;
        } else {
            if( not real_car_ ) real_car_ = std::make_unique<Car>();
            real_car_->DriveCar();
        }
    }
private:
    std::unique_ptr<CarIntfc> real_car_;
    int driver_age_;
};
////////////////////////////////////////////////////////////////////////////////
int main() {
    constexpr auto kDriverAge = 15;
    ProxyCar car(kDriverAge);
    car.DriveCar();
    car.OwnerHasBirthday();
    car.DriveCar();
    return 0;
}