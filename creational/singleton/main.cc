#include <iostream>
#include <string>
#include <memory>

////////////////////////////////////////////////////////////////////////////////
//! Class with single instance holding shared data between references
class StringSingleton {
private:
    std::string mString;
public:
    std::string GetString() const { return mString; }
    void SetString(const std::string &newStr) { mString = newStr; }

    // Creates objects once, or returns the instance if already created
    static StringSingleton& Instance() {
        static StringSingleton instance;
        return instance;
    }
private: 
    //! Hide ctor 
    StringSingleton() {}
    //! Delete copy ctor - prevents someone from accidently copying with
    //!  a call like `StringSingleton copy = StringSingleton::Instance();`
    StringSingleton(const StringSingleton &old);
    //! Delete assignment operator
    const StringSingleton &operator=(const StringSingleton &old);
};
////////////////////////////////////////////////////////////////////////////////
int main() {
    StringSingleton& ref_1 = StringSingleton::Instance();
    std::cout << "Data is " << ref_1.GetString() << std::endl;

    StringSingleton& ref_2 = StringSingleton::Instance();
    std::cout << "Data is now " << ref_2.GetString() << std::endl;
    return 0;
}