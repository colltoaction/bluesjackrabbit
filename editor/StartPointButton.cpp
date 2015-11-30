#include <string>
#include "StartPointButton.h"
#define START_POINT_BUTTON_LABEL "Start Point"
#define START_POINT_IMAGE_FILENAME "little blues.png"

StartPointButton::StartPointButton(int width, int height) :
    ControlToolButton(START_POINT_IMAGE_FILENAME, START_POINT_BUTTON_LABEL, width, height) {
}
