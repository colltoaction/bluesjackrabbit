#ifndef BLUESJACKRABBIT_COMMON_MESSAGE_H
#define BLUESJACKRABBIT_COMMON_MESSAGE_H


// TODO(tinchou): Make this an abstract class
class Message {
 public:
  explicit Message(char type);

  virtual ~Message() {}

  /**
   * This is the character that identifies the type of the message when communicating
   * through sockets.
   */
  virtual char type();

 private:
  char type_;
};


#endif  // BLUESJACKRABBIT_COMMON_MESSAGE_H
