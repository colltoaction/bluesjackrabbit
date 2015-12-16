#ifndef BLUESJACKRABBIT_EDITOR_CANVASITEM_H
#define BLUESJACKRABBIT_EDITOR_CANVASITEM_H
#include <stdint.h>

class CanvasItem {
 public:
  CanvasItem(uint64_t item_id) : item_id_(item_id) {}
  uint64_t item_id() const {return item_id_;}
  CanvasItem& dereference() {return *this;}

 private:
  uint64_t item_id_;
};

#endif // BLUESJACKRABBIT_EDITOR_CANVASITEM_H