#pragma once

#include <iostream>
#include <vector>

using namespace std;

class State {
public:
	State() {};
	virtual ~State() {
		cout << "State destroyed" << endl;
	};

	virtual void init() = 0;
	virtual void handleInput() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void pause() {};
	virtual void resume() {};
};

class StateManager {
private:
	vector<unique_ptr<State>> stateStack;
	unique_ptr<State> newState;
	
	bool push;
	bool pop;
	
public:
	StateManager();
	~StateManager();

	void pushState(unique_ptr<State> newState);
	void popState();
	void changeState();
	unique_ptr<State>& getCurrentState();
};