#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <memory>

// Forward declarations ////////////////////////////////////////////////////////
class Fighter;
class StandingState;  class JumpingState;  class DivingState;
enum Input {DUCK_DOWN, STAND_UP, JUMP, DIVE};

// Main State Interface  ///////////////////////////////////////////////////////
class FighterState {
	public:
		virtual ~FighterState() = default;

        // Function for current state to handle new user input 
		virtual void handleInput(Fighter&, Input) = 0;
        // Function for current state to show / take their action 
		virtual void update(Fighter&) = 0;

        // Static member for the common state to prevent constant dynamic allocation
		static std::shared_ptr<StandingState> standing;
};

// State Interface Declarations  ///////////////////////////////////////////////
// - Each one implements FighterState's virtual functions...
class StandingState : public FighterState {
	public:
        void handleInput (Fighter& fighter, Input input) override;
        void update (Fighter& fighter) override;
};
class JumpingState : public FighterState {
	private:
		int jumpingHeight;
	public:
		JumpingState() {jumpingHeight = std::rand() % 5 + 1;};
        void handleInput (Fighter& fighter, Input input) override;
        void update (Fighter& fighter) override;
};
class DuckingState : public FighterState {
	private:
		int chargingTime;
		static const int FullRestTime = 5;
	public:
		DuckingState() : chargingTime(0) {};
        void handleInput (Fighter& fighter, Input input) override;
        void update (Fighter& fighter) override;
};
class DivingState : public FighterState {
	public:
        void handleInput (Fighter& fighter, Input) override;
        void update (Fighter& fighter) override;
};

// FighterStates static member initilization
std::shared_ptr<StandingState> FighterState::standing(new StandingState);

// Class to utilize the FighterState interface as a member /////////////////////
class Fighter {
	public:
		Fighter (const std::string& newName) :
            _name(newName), _state(FighterState::standing) {}
		std::string getName() const { return _name; }
		int getFatigueLevel() const { return _fatigueLevel; }

        // Update, then delegate our `update` behavior to the new '_state' member
		void changeState(std::shared_ptr<FighterState> newState) {
            _state = newState;
            _state->update(*this);
        }

        // Delegate our input behavior to our current internal '_state' member
		virtual void handleInput(Input input) { _state->handleInput (*this, input); } 

        // Function delegating fatigue cost to each FighterState 
		void changeFatigueLevelBy(int change) {
            _fatigueLevel += change;
            std::cout << "fatigueLevel = " << _fatigueLevel << std::endl;
        }

	private:
		std::string _name;
		std::shared_ptr<FighterState> _state;
		int _fatigueLevel = std::rand() % 10;
};

// State Interface Implementations:  ///////////////////////////////////////////
// - Standing  /////////////////////////////////////////////////////////////////
void StandingState::handleInput(Fighter& fighter, Input input) {
    switch (input) {
        case STAND_UP: 
            std::cout << fighter.getName() << " remains standing." << std::endl; 
            return;
        case DUCK_DOWN:
            fighter.changeState( std::shared_ptr<DuckingState>(new DuckingState) );
        case JUMP:
            return fighter.changeState( std::shared_ptr<JumpingState>(new JumpingState) );
        default: 
            std::cout << "One cannot do that while standing.  " << fighter.getName() <<
                " remains standing by default." << std::endl;
    }
};
void StandingState::update(Fighter& fighter) {
    if (fighter.getFatigueLevel() > 0)
        fighter.changeFatigueLevelBy(-1);
};
// - Jumping  //////////////////////////////////////////////////////////////////
void JumpingState::handleInput(Fighter& fighter, Input input) {
    switch (input) {
        case DIVE:
            fighter.changeState( std::shared_ptr<DivingState>(new DivingState) );
        default:
            std::cout << "One cannot do that in the middle of a jump. " <<
                fighter.getName() << " lands from his jump." << std::endl;
            fighter.changeState(FighterState::standing);
    }
};
void JumpingState::update(Fighter& fighter) {
    std::cout << fighter.getName() << " jumped " << jumpingHeight << " feet." << std::endl;
    if (jumpingHeight >= 3)
        fighter.changeFatigueLevelBy(1);
};
// - Ducking  //////////////////////////////////////////////////////////////////
void DuckingState::handleInput(Fighter& fighter, Input input) {
    switch (input) {
        case STAND_UP: 
            fighter.changeState( FighterState::standing );
        case DUCK_DOWN:
            std::cout << fighter.getName() << " remains in ducking position, ";
            if (chargingTime < FullRestTime) std::cout << "recovering in the meantime." << std::endl;
            else std::cout << "fully recovered." << std::endl;
            return update(fighter);
        default:
            std::cout << "One cannot do that while ducking.  " << fighter.getName() <<
                " remains in ducking position by default." << std::endl;
            update(fighter);
    }
};
void DuckingState::update(Fighter& fighter) {
    chargingTime++;
    std::cout << "Charging time = " << chargingTime << "." << std::endl;
    if (fighter.getFatigueLevel() > 0)
        fighter.changeFatigueLevelBy(-1);
    if (chargingTime >= FullRestTime && fighter.getFatigueLevel() <= 3)
		std::cout << fighter.getName() << " feels strong!" << std::endl;
};
// - Diving  ///////////////////////////////////////////////////////////////////
void DivingState::handleInput(Fighter& fighter, Input) {
    std::cout << "Regardless of what the user input is, " << fighter.getName() <<
        " lands from his dive and is now standing again." << std::endl;
    fighter.changeState( FighterState::standing );
};
void DivingState::update(Fighter& fighter) {
    fighter.changeFatigueLevelBy(2);
}

// Main to run the program  ////////////////////////////////////////////////////
int main() {
	std::srand(std::time(nullptr));
	Fighter rex ("Rex the Fighter"), borg ("Borg the Fighter");
	std::cout << rex.getName() << " and " << borg.getName() << "are currently standing." << std::endl;

	int choice;
	auto chooseAction = [&choice](Fighter& fighter) {
		std::cout << std::endl <<
            DUCK_DOWN + 1 << ") Duck down  " <<
            STAND_UP + 1 << ") Stand up  " <<
            JUMP + 1 << ") Jump  " <<
            DIVE + 1 << ") Dive in the middle of a jump" <<
            std::endl;
		std::cout << "Choice for " << fighter.getName() << "? ";
		std::cin >> choice;
		const Input input1 = static_cast<Input>(choice - 1);
		fighter.handleInput(input1);	
	};

	while (true) {
		chooseAction(rex);
		chooseAction(borg);
	}
}