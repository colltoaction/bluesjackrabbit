#include <common/NumericHelper.h>

void NumericHelper::convert_to_littleendian(char *buffer, int len, uint32_t *object_id) {
  char *byte = static_cast<char*>(static_cast<void*>(object_id));
  int index = 0;
  if (is_littleendian()) {
    for (int i = 0; i < len; i++) {
      buffer[index] = byte[i];
      index++;
    }
  } else {
    for (int i = len - 1; i >= 0; i--) {
      buffer[index] = byte[i];
      index++;
    }
  }
}

bool NumericHelper::is_littleendian() {
  int number = 1;
  char *check = static_cast<char*>(static_cast<void*>(&number));
  return check[0] == 1;
}

void NumericHelper::convert_from_littleendian(char *buffer, int len, uint32_t *object_id) {
  char *byte = static_cast<char*>(static_cast<void*>(object_id));
    int index = 0;
    if (is_littleendian()) {
      for (int i = 0; i < len; i++) {
        byte[index] = buffer[i];
        index++;
      }
    } else {
      for (int i = len - 1; i >= 0; i--) {
        byte[index] = buffer[i];
        index++;
      }
    }
}
