#include <string>
#include "SpawnPointButton.h"
#define SPAWN_POINT_BUTTON_LABEL "Spawn Point"
#define SPAWN_POINT_IMAGE_FILENAME "devan.png"

SpawnPointButton::SpawnPointButton(int width, int height) :
    ControlToolButton(SPAWN_POINT_IMAGE_FILENAME, SPAWN_POINT_BUTTON_LABEL, width, height) {
}
