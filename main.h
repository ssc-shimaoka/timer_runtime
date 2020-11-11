#include "MicroBit.h"
#include "model.h"

class myMicroBit : public MicroBit
{



    void onButtonA(MicroBitEvent e);
    void onButtonB(MicroBitEvent e);
    void onButtonAB(MicroBitEvent e);
};