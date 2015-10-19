#ifndef BLUESJACKRABBIT_CLIENT_TRANSFORM_H
#define BLUESJACKRABBIT_CLIENT_TRANSFORM_H


#include "Point.h"

class Transform {
 public:
//    double Width() const;
//    double Height() const;
    Point Position() const;
 private:
    Point position;
};


#endif  // BLUESJACKRABBIT_CLIENT_TRANSFORM_H
