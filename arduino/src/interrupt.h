#ifndef INTERRUPT_H
#define INTERRUPT_H

class Interrupt
{
private:
    int interruptPin;
public:
    Interrupt(int interruptPin);
    bool mustStop();
};

#endif
