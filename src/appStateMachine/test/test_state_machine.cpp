#include "../include/appStateMachine.h"
#include "gtest/gtest.h"

TEST(stateMachineTesting, TestStateMachineCreation) {
  // test all constructor permutations
  ApplicationStateMachine new_state_machine;
  ApplicationStateMachine copied_state_machine(new_state_machine);
  ApplicationStateMachine copy_assign_state_machine;
  copy_assign_state_machine = copied_state_machine;

  ASSERT_EQ(BOUNDARY_SELECTION, new_state_machine.getCurrentState());
  ASSERT_EQ(BOUNDARY_SELECTION, copied_state_machine.getCurrentState());
  ASSERT_EQ(BOUNDARY_SELECTION, copy_assign_state_machine.getCurrentState());
}

TEST(stateMachineTesting, TestStateMachineAdvance) {
  // create state machine
  ApplicationStateMachine new_state_machine;

  // make sure basic state incrementing works
  for (uint8_t i = 0; i < static_cast<uint8_t>(MAP_GENERATED); i++) {
    application_state_t cur_state = new_state_machine.getCurrentState();
    new_state_machine.advanceStateMachine();
    ASSERT_EQ(static_cast<application_state_t>(i), cur_state);
  }
  // make sure we wrap around correctly when we advance from the final state
  new_state_machine.advanceStateMachine();
  ASSERT_EQ(BOUNDARY_SELECTION, new_state_machine.getCurrentState());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}