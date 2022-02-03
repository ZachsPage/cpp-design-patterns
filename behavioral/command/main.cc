#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
//! The Command interface
class Command {
public:
	virtual void execute() = 0; //!< `Callback` for each implementor
};
////////////////////////////////////////////////////////////////////////////////
//! Example receiver class for each Command implementor to enact upon
class Light {
public:
	Light() {}
	void turnOn() { cout << "The light is on" << endl; }
    void turnOff() { cout << "The light is off" << endl; }
};
////////////////////////////////////////////////////////////////////////////////
//! Command implementor for turning on the light
class FlipUpCommand : public Command {
public:
	FlipUpCommand(Light& light) : theLight(light) {}
	virtual void execute() { theLight.turnOn(); }
private:
	Light& theLight;
};
////////////////////////////////////////////////////////////////////////////////
//! Command implementor for turning off the light
class FlipDownCommand : public Command {
public:   
	FlipDownCommand(Light& light) : theLight(light) {}
	virtual void execute() { theLight.turnOff(); }
private:
	Light& theLight;
};
////////////////////////////////////////////////////////////////////////////////
//! The test class or client that could take swappable Command implemenations
class Switch {
public:
	Switch(Command& flipUpCmd, Command& flipDownCmd) :
        flipUpCommand(flipUpCmd),flipDownCommand(flipDownCmd)
    {}
	void flipUp() { flipUpCommand.execute(); }
	void flipDown() { flipDownCommand.execute(); } 
private:
	Command& flipUpCommand;
	Command& flipDownCommand;
};
////////////////////////////////////////////////////////////////////////////////
int main() 
{
	Light lamp;
	FlipUpCommand switchUp(lamp);
	FlipDownCommand switchDown(lamp);

	Switch s(switchUp, switchDown);
	s.flipUp();
	s.flipDown();
}