#include "../include/state.h"

StateManager::StateManager() 
	: push(false), pop(false) {

}

StateManager::~StateManager() {

}

void StateManager::pushState(unique_ptr<State> newState) {
	push = true;
	this->newState = move(newState);
}

void StateManager::popState() {
	pop = true;
}

void StateManager::changeState() {
	if (pop) {
		if (!stateStack.empty()) {
			stateStack.back() = nullptr;
			stateStack.pop_back();
		}

		if (!stateStack.empty()) {
			stateStack.back()->resume();
		}
		pop = false;
	}

	if (push) {
		if (!stateStack.empty()) {
			stateStack.back()->pause();
		}

		stateStack.push_back(move(newState));
		stateStack.back()->init();
		push = false;
	}
}

unique_ptr<State>& StateManager::getCurrentState() {
	if (!stateStack.empty()) {
		return stateStack.back();
	}

	throw runtime_error("State stack is empty");
}
