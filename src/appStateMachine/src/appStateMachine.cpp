#include "../include/appStateMachine.h"
#include <cstdint>

ApplicationStateMachine::ApplicationStateMachine(){
    this->current_state = BOUNDARY_SELECTION;
}

ApplicationStateMachine::ApplicationStateMachine(const ApplicationStateMachine &other){
    this->current_state = other.current_state;
}

ApplicationStateMachine ApplicationStateMachine::operator=(const ApplicationStateMachine &other) {
    this->current_state = other.current_state;
    return *this;
}

void ApplicationStateMachine::advanceStateMachine() {
    // if we aren't at the end of the state machine,
    // simply increment the state.
    if(this->getCurrentState() != MAP_GENERATED){
        this->current_state = static_cast<application_state_t> ((uint8_t) this->getCurrentState() + 1);
    }

    // otherwise, wrap around to the start.
    else {
        this->current_state = BOUNDARY_SELECTION;
    }
}

application_state_t ApplicationStateMachine::getCurrentState() {
    return this->current_state;
}