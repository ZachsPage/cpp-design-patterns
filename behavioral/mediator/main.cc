#include <iostream>
#include <string>
#include <list>

class MediatorInterface;

////////////////////////////////////////////////////////////////////////////////
class ColleagueInterface {
	std::string name;
public: // Implemented functions
	ColleagueInterface(const std::string& newName) : name (newName) {}
	std::string getName() const {return name;}
public: // Pure virtuals to require implementation
	// User function to send a message
	virtual void sendMessage(const MediatorInterface&, const std::string&) const = 0;
	// Used by Meditator to distribute message to everyone in its list
	virtual void receiveMessage(const ColleagueInterface*, const std::string&) const = 0;
};
////////////////////////////////////////////////////////////////////////////////
class MediatorInterface {
private:
	std::list<ColleagueInterface*> colleagueList;
public: // Implemented functions
	const std::list<ColleagueInterface*>& getColleagueList() const { return colleagueList; }
	virtual void registerColleague(ColleagueInterface* colleague) { colleagueList.emplace_back (colleague); }
public: // Pure virtuals to require implementation
	// Forward the message to everyone in the list to mediate
	virtual void distributeMessage(const ColleagueInterface*, const std::string&) const = 0;
};
////////////////////////////////////////////////////////////////////////////////
class Colleague : public ColleagueInterface {
public:
	// Allows use of ColleageInterface constructor
	using ColleagueInterface::ColleagueInterface;
	// Send message into the Mediator
	virtual void sendMessage(const MediatorInterface& mediator, const std::string& message) const override {
		mediator.distributeMessage(this, message);
	}
private:
	// Print the message when received
	virtual void receiveMessage(const ColleagueInterface* sender, const std::string& message) const override {
		std::cout << getName() << " received the message from " << sender->getName() << ": " << message << std::endl;			
	}
};
////////////////////////////////////////////////////////////////////////////////
class Mediator : public MediatorInterface {
private:
    virtual void distributeMessage(const ColleagueInterface* sender, const std::string& message) const override {
		for (const ColleagueInterface* x : getColleagueList())
			if (x != sender) x->receiveMessage (sender, message);
	}
};
////////////////////////////////////////////////////////////////////////////////
int main() {
	Colleague 
		*bob = new Colleague("Bob"),  *sam = new Colleague("Sam"),  
		*frank = new Colleague("Frank"),  *tom = new Colleague("Tom");
	Colleague* staff[] = {bob, sam, frank, tom};

	// Create full message list for staff
	Mediator mediatorStaff;
	for (Colleague* x : staff) mediatorStaff.registerColleague(x);
	// - Send message to be received by entire staff
	bob->sendMessage(mediatorStaff, "I'm quitting this job!");

	// Create message list of Sam's buddies only...
	Mediator mediatorSamsBuddies;
	mediatorSamsBuddies.registerColleague(frank);  
	mediatorSamsBuddies.registerColleague(tom);
	// - Send exclusive message 
	sam->sendMessage(mediatorSamsBuddies, "Hooray!  He's gone!  Let's go for a drink, guys!");	
	return 0;
}