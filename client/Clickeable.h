#ifndef CLICKEABLE_H_
#define CLICKEABLE_H_

class Clickeable {
 public:
    virtual ~Clickeable() {
    }
    virtual void onClick() = 0;
};

#endif /* CLICKEABLE_H_ */
