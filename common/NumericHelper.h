#ifndef BLUESJACKRABBIT_COMMON_NUMERICHELPER_H
#define BLUESJACKRABBIT_COMMON_NUMERICHELPER_H

#include <unistd.h>
#include <stdint.h>

class NumericHelper {
 public:
  static const ssize_t UINT32_T_LENGTH = sizeof(uint32_t);
  static bool is_littleendian();
  static void convert_to_littleendian(char *buffer, int len, uint32_t *object_id);
  static void convert_from_littleendian(char *buffer, int len, uint32_t *object_id);
};

#endif /* BLUESJACKRABBIT_COMMON_NUMERICHELPER_H */
