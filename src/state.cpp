#include "../include/state.h"

StateManager::StateManager() {

}

StateManager::~StateManager() {

}

void StateManager::setState(unique_ptr<State> newState) {
	currentState = move(newState);
}

unique_ptr<State>& StateManager::getState() {
	return currentState;
}