#include <iostream>
#include <string>
#include <sstream>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
// Free function to return argument as a string
template <typename T> std::string toString(const T& t) {
	std::stringstream ss;
	ss << t;
	return ss.str();
}
class Memento;
////////////////////////////////////////////////////////////////////////////////
class Object {
  	private:
		int value;
		std::string name;
		double decimal;  // and suppose there are loads of other data members
  	public:
		static constexpr char kPrefix[] = "Object";
	    Object (int newValue): value (newValue), name (kPrefix + toString(value)), decimal ((float)value / 100) {}
	    void doubleValue() {value = 2 * value;  name = kPrefix + toString(value);  decimal = (float)value / 100;}
	    void increaseByOne() {value++;  name = kPrefix + toString (value);  decimal = (float)value / 100;}
	    int getValue() const {return value;}
	    std::string getName() const {return name;}
	    double getDecimal() const {return decimal;}
	// Implemented later....
	    Memento* createMemento() const;
	    void reinstateMemento (Memento* mem);
};
////////////////////////////////////////////////////////////////////////////////
class Memento {
  	private:
 	    Object object;
  	public:
		Memento (const Object& obj):  object (obj) {}
		Object snapshot() const {return object;}  // want a snapshot of Object itself because of its many data members
};
////////////////////////////////////////////////////////////////////////////////
// Implement Object functions now that Memento is fully defined
Memento* Object::createMemento() const { return new Memento (*this); }
void Object::reinstateMemento (Memento* mem) { *this = mem->snapshot(); }

////////////////////////////////////////////////////////////////////////////////
class Command {
private:
	typedef void (Object::*Action)();
	Object* receiver;
	Action action;
	static std::vector<Command*> commandList;
	static std::vector<Memento*> mementoList;
	static int numCommands;
	static int maxCommands;
public:
	Command (Object *newReceiver, Action newAction): receiver (newReceiver), action (newAction) {}
	virtual void execute() {
		if (mementoList.size() < numCommands + 1)
			mementoList.resize (numCommands + 1);
		mementoList[numCommands] = receiver->createMemento();  // saves the last value
		if (commandList.size() < numCommands + 1)
			commandList.resize (numCommands + 1);
		commandList[numCommands] = this;  // saves the last command
		if (numCommands > maxCommands)
			maxCommands = numCommands;
		numCommands++;
		(receiver->*action)();
	}
	static void undo() {
		if (numCommands == 0) {
			std::cout << "There is nothing to undo at this point." << std::endl;
			return;
		}
		commandList[numCommands - 1]->receiver->reinstateMemento (mementoList[numCommands - 1]);
		numCommands--;
	}
	void static redo() {
		if (numCommands > maxCommands) {
			std::cout << "There is nothing to redo at this point." << std::endl;
			return ;
		}
		Command* commandRedo = commandList[numCommands];
		(commandRedo->receiver->*(commandRedo->action))();
		numCommands++;
	}
};
////////////////////////////////////////////////////////////////////////////////
// `Object` Static Inits...
std::vector<Command*> Command::commandList;
std::vector<Memento*> Command::mementoList;
int Command::numCommands = 0;
int Command::maxCommands = 0;
constexpr char Object::kPrefix[];
////////////////////////////////////////////////////////////////////////////////
int main() {
	int i;
	std::cout << "Please enter an integer: ";
	std::cin >> i;
	Object *object = new Object(i);
	
	Command *commands[3];
	commands[1] = new Command(object, &Object::doubleValue);
	commands[2] = new Command(object, &Object::increaseByOne);
	
	std::cout << "0.Exit,  1.Double,  2.Increase by one,  3.Undo,  4.Redo: ";
	std::cin >> i;
	
	while (i != 0)
	{
		if (i == 3) Command::undo();
		else if (i == 4) Command::redo();
		else if (i > 0 && i <= 2) commands[i]->execute();
		else {
			std::cout << "Enter a proper choice: ";
			std::cin >> i;
			continue;
		}
		std::cout << "   " << object->getValue() << "  " << object->getName() << "  " << object->getDecimal() << std::endl;
		std::cout << "0.Exit,  1.Double,  2.Increase by one,  3.Undo,  4.Redo: ";
		std::cin >> i;
	}
}