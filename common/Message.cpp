#include "Message.h"

Message::Message(char type)
    : type_(type) {
}

char Message::type() {
  return type_;
}
