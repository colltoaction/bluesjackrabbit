#ifndef BLUESJACKRABBIT_COMMON_LEVELFINISHEDMESSAGE_H
#define BLUESJACKRABBIT_COMMON_LEVELFINISHEDMESSAGE_H

#include "Message.h"
#include "Socket.h"

class LevelFinishedMessage: public Message {
 public:
  explicit LevelFinishedMessage(Socket *socket);
  virtual ~LevelFinishedMessage();
  static char type_id();
  virtual char type();

  void read();

  void send(bool won);

  bool won();

 private:
  Socket *socket_;
  char won_;
};

#endif /* BLUESJACKRABBIT_COMMON_LEVELFINISHEDMESSAGE_H */
