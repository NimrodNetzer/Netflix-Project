#ifndef RUNNABLE_H
#define RUNNABLE_H



class Runnable {
  public:
    virtual ~Runnable() = default;

    virtual void run() = 0;

};



#endif //RUNNABLE_H
