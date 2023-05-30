#pragma once

#include <iostream>

using namespace std;

class State {
public:
	State() {};
	virtual ~State() {};

	virtual void init() = 0;
	virtual void handleInput() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};

class StateManager {
private:
	unique_ptr<State> currentState;
	
public:
	StateManager();
	~StateManager();

	void setState(unique_ptr<State> newState);
	unique_ptr<State>& getState();
};