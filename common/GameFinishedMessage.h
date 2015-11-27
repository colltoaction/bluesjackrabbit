#ifndef BLUESJACKRABBIT_COMMON_GAMEFINISHEDMESSAGE_H
#define BLUESJACKRABBIT_COMMON_GAMEFINISHEDMESSAGE_H


#include "Message.h"
#include "Socket.h"

class GameFinishedMessage: public Message {
 public:
  explicit GameFinishedMessage(Socket *socket);
  virtual ~GameFinishedMessage();
  static char type_id();
  virtual char type();

  /**
   * Reads a message indicating the current game has finished.
   */
  void read();

  /**
   * Sends a message indicating the game has finished and whether the user has won.
   */
  void send(bool won);

  /**
   * Indicates whether the user has won.
   */
  bool won();

 private:
  Socket *socket_;
  char won_;
};


#endif  // BLUESJACKRABBIT_COMMON_GAMEFINISHEDMESSAGE_H
