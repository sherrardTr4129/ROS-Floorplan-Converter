#pragma once

/**
 * @brief an enum representing the possible application states.
*/
typedef enum {
    BOUNDARY_SELECTION,
    SCALE_IDENTIFICATION,
    TEXT_SELECTION,
    DOOR_SELECTION,
    MAP_GENERATED
} application_state_t;

/**
 * @brief a class for managing the application state.
*/
class ApplicationStateMachine {
public:
    public:
        /**
         * @brief default constructor.
        */
        ApplicationStateMachine();

        /**
         * @brief copy constructor.
        */
        ApplicationStateMachine(const ApplicationStateMachine &other);

        /**
         * @brief copy assignment operator.
        */
        ApplicationStateMachine operator=(const ApplicationStateMachine &other);

        /**
         * @brief advances the current state machine by a 
         * single state step.
        */
        void advanceStateMachine();
        
        /**
         * @brief returns the current state of the state machine.
        */
        application_state_t getCurrentState();
    
private:
    application_state_t current_state;
}; 