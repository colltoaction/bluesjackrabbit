#ifndef BLUESJACKRABBIT_COMMON_MESSAGEWRITER_H
#define BLUESJACKRABBIT_COMMON_MESSAGEWRITER_H


#include <list>
#include "Socket.h"

class MessageWriter {
 public:
  explicit MessageWriter(Socket *socket);

  /**
   * Sends a message containing the available maps through the socket.
   */
  void send_available_maps(const std::list<char> &map_ids);

 private:
  Socket *socket_;
};

#endif  // BLUESJACKRABBIT_COMMON_MESSAGEWRITER_H
