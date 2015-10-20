#ifndef BLUESJACKRABBIT_CLIENT_POINT_H
#define BLUESJACKRABBIT_CLIENT_POINT_H


class Point {
 public:
    double X() const;
    double Y() const;

    void X(double d);

    void Y(double d);

 private:
    double x;
    double y;
};


#endif  // BLUESJACKRABBIT_CLIENT_POINT_H
