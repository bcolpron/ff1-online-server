#ifndef INCLUDE_COMM_H
#define INCLUDE_COMM_H

struct Message;

class Comm
{
public:
    virtual void sendAll(const Message& msg) = 0;
};

#endif