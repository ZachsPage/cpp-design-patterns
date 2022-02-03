#include <iostream>

////////////////////////////////////////////////////////////////////////////////
//! Interface class that requires the implementor to have `requiredFcn()`
template<typename T>
class IntfcClass {
public:
    void callImplFcn() { impl_.requiredFcn(); }
private:
    T impl_;
};
////////////////////////////////////////////////////////////////////////////////
//! Implementor that satisifes IntfcClass's needed functions
class Impl {
public:
    void requiredFcn() { std::cout << "Impl's required function! " << std::endl; }
};
////////////////////////////////////////////////////////////////////////////////
int main() {
    // Instantiate IntfcClass using the Impl implementation
    IntfcClass<Impl> obj;
    obj.callImplFcn();
}