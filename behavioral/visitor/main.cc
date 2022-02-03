#include <string>
#include <iostream>
#include <vector>
#include <memory>
using namespace std;
 
class Wheel;
class Engine;
class Body;
class Car;
//////////////////////////////////////////////////////////////////////////////// 
//! Interface for "car visitors" to implement - must virtualize all "visits".
//!  The "visit" param object should implement "accept" that calls the 
//!  the "visitors" implemention of "visit"
struct CarElementVisitor {
    // Visit the base object - cycles through all elements
	virtual void visitCar(Car& car) const = 0;
    // Visit the elements
	virtual void visit(Wheel& wheel) const = 0;
	virtual void visit(Engine& engine) const = 0;
	virtual void visit(Body& body) const = 0;
};
//////////////////////////////////////////////////////////////////////////////// 
//! Interface for elements to allow the visitor to visit them
struct CarElementIntfc {
	// Calls the CarElementVisitor implementor's "visit" callback, passing
	//  the element in that implements this interface
	virtual void accept(const CarElementVisitor& visitor) = 0;	
};
// Element Implementations
//////////////////////////////////////////////////////////////////////////////// 
class Wheel : public CarElementIntfc {
public:
	explicit Wheel(const string& name) : name_(name) {}
	const string& getName() const { return name_; }
	void accept(const CarElementVisitor& visitor) { visitor.visit(*this); }
private:
	string name_;
};
class Engine : public CarElementIntfc {
public:
	void accept(const CarElementVisitor& visitor) { visitor.visit(*this); }
};
class Body : public CarElementIntfc {
public:
	void accept(const CarElementVisitor& visitor) { visitor.visit(*this); }
};
//////////////////////////////////////////////////////////////////////////////// 
//! Car creation using the implemented elements 
class Car {
public:
	Car() {
		elements_.push_back( make_unique<Wheel>("front left") );
		elements_.push_back( make_unique<Wheel>("front right") );
		elements_.push_back( make_unique<Wheel>("back left") );
		elements_.push_back( make_unique<Wheel>("back right") );
		elements_.push_back( make_unique<Body>() );
		elements_.push_back( make_unique<Engine>() );
	}
	// Give access to all of the elements to be visted
	vector<unique_ptr<CarElementIntfc>>& getElements() { return elements_; }
private:
	vector<unique_ptr<CarElementIntfc>> elements_;
};
// Visitor implementations - show different functionality on an unchanged Car class
//////////////////////////////////////////////////////////////////////////////// 
//! Visitor to check each element
class CarElementChecker : public CarElementVisitor {
public:
	// These are specific implementations added to the original object
	// without modifying the original struct
	void visit(Wheel& wheel) const { 
		cout << "Checking " << wheel.getName() << " wheel" << endl;
	}
	void visit(Engine& engine) const { cout << "Checking engine" << endl; }
	void visit(Body& body) const { cout << "Checking body" << endl; }
	void visitCar(Car& car) const {
		cout << endl << "Checking car" << endl;
		vector<unique_ptr<CarElementIntfc>>& elems = car.getElements();
		// Issue the callback i.e. "visit" the element  
		for(auto &it : elems) it->accept(*this);
	}
};
//! Visitor to do something to each element
class CarElementInteractor: public CarElementVisitor {
public:
	void visit(Wheel& wheel) const {
		cout << "Kicking my " << wheel.getName() << " wheel" << endl;
	}
	void visit(Engine& engine) const { cout << "Starting my engine" << endl; }
	void visit(Body& body) const { cout << "Moving my body" << endl; }
	void visitCar(Car& car) const {
		cout << endl << "Starting my car" << endl;
		vector<unique_ptr<CarElementIntfc>>& elems = car.getElements();
		for(auto& it : elems) it->accept(*this);
	}
};
//////////////////////////////////////////////////////////////////////////////// 
int main() {
	Car car;
	CarElementChecker car_checker;
	CarElementInteractor car_doer;

	car_checker.visitCar(car);
	car_doer.visitCar(car);

	return 0;
}