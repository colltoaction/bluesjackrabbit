#include <string>
#include "GoalButton.h"
#define GOAL_BUTTON_LABEL "Goal"
#define GOAL_IMAGE_FILENAME "goal.png"

GoalButton::GoalButton(int width, int height) :
    ControlToolButton(GOAL_IMAGE_FILENAME, GOAL_BUTTON_LABEL, width, height) {
}
