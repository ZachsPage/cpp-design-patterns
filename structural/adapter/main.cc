#include <iostream>

////////////////////////////////////////////////////////////////////////////////
//! Interface Class to adapt
class Cat {
public:
	virtual ~Cat() = default;
	virtual void performConversion() const = 0;
};
////////////////////////////////////////////////////////////////////////////////
//! Concrete Cat
class CatFemale : public Cat {
public:
	virtual void performConversion() const override { 
        std::cout << "Cat female performs conversion." << std::endl; 
    }
};
////////////////////////////////////////////////////////////////////////////////
//! Interface Class to adapt **to**
class Dog {
public:
	virtual ~Dog() = default;
	virtual void performConversion() const = 0;
};
////////////////////////////////////////////////////////////////////////////////
//! Concrete Dog
class DogFemale : public Dog {
public:
	virtual void performConversion() const override { 
        std::cout << "Dog female performs conversion." << std::endl; 
    }
};
////////////////////////////////////////////////////////////////////////////////
//! Class to hold nature functions for Dogs
class DogNature {
public:
    //! Function to show adapted class can be treated as the newly `adapted` class
	void carryOutNature(Dog& dog) {
		std::cout << "On with the Dog nature!" << std::endl;
		dog.performConversion();
	}
};
////////////////////////////////////////////////////////////////////////////////
//! Main Adapter class for Cat to call Dog functions
class ConversionAdapter : public Dog {
private:
	Cat& cat;
public:
	ConversionAdapter(Cat& c) : cat(c) {}
    //! Adapter by overriding Dog's function to call desired Cat's function
	virtual void performConversion() const override { cat.performConversion(); }
};
////////////////////////////////////////////////////////////////////////////////
//! 
int main() { 
	DogFemale dogFemale;
	CatFemale catFemale;
	DogNature dogNature;
	ConversionAdapter adaptedCat = ConversionAdapter(catFemale);
	dogNature.carryOutNature(dogFemale);
	dogNature.carryOutNature(adaptedCat);
	return 0;
}