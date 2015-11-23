#ifndef BLUESJACKRABBIT_COMMON_GAMEOBJECTMESSAGE_H
#define BLUESJACKRABBIT_COMMON_GAMEOBJECTMESSAGE_H


#include <vector>
#include <engine/GameObject.h>
#include "Message.h"
#include "Socket.h"

class GameObjectMessage: public Message {
 public:
  explicit GameObjectMessage(Socket *socket);

  static char type_id();

  /**
   * Reads a game object sent through the socket.
   */
  void read();

  /**
   * Sends a game object through the socket.
   */
  void send(uint32_t object_id, GameObject *position);

  /**
   * Returns the object id that has been read.
   */
  uint32_t object_id() const;

  /**
   * Returns the object type that has been read.
   */
  char object_type() const;

  /**
   * Returns the position that has been read.
   */
  const Vector &position() const;

  /**
   * Returns the points that have been read.
   */
  const std::vector<Vector> &points() const;

  /**
   * Returns whether the object that has been read is alive.
   */
  bool alive() const;

 private:
  Socket *socket_;
  uint32_t object_id_;
  Vector position_;
  char object_type_;
  std::vector<Vector> points_;
  char alive_;
  void read_object_points();
  void send_object_points(Socket *socket, const std::vector<Vector> &points);
};


#endif  // BLUESJACKRABBIT_COMMON_GAMEOBJECTMESSAGE_H
