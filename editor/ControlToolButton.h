#ifndef BLUESJACKRABBIT_EDITOR_CONTROLTOOLBUTTON_H
#define BLUESJACKRABBIT_EDITOR_CONTROLTOOLBUTTON_H
#include <string>
#include "CustomToolButton.h"

class ControlToolButton : public CustomToolButton {
public:
  ControlToolButton(std::string filename, std::string label,
      int width = 64, int height = 64);

};

#endif // BLUESJACKRABBIT_EDITOR_CONTROLTOOLBUTTON_H