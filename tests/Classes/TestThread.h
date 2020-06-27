#include "Core/Thread/Thread.h"

class TestThread : public Michka::Thread
{
public:
    TestThread(int& _tv): Thread(), mTestVar(_tv)
    {
    }
protected:
    virtual void run()
    {
        mTestVar++;
    }

public:
    int& mTestVar;
};
