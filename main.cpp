#include "main.h"
#include <string>

//------------------------------------------------
//  グローバル変数
//------------------------------------------------
myMicroBit    uBit;
Model         model;

//------------------------------------------------
//  イベントハンドラ
//------------------------------------------------
// Aボタン押下時
void onButtonA(MicroBitEvent e)
{
    if (e.value == MICROBIT_BUTTON_EVT_CLICK)
    {
        // タイマー状態：待ち受け時
        if(model.timerStatus == 0)
        {
            model.setTime = model.blockNumber * model.blockSurvivalTime * model.updateInterval;
            model.startTime = uBit.systemTime();
            model.timerStatus = 1;

            uBit.serial.send(model.setTime);
            uBit.serial.send("\n");
        }

    }
    if (e.value == MICROBIT_BUTTON_EVT_LONG_CLICK)
    {
        uBit.display.scroll("A LONG");
    }
}

void onButtonB(MicroBitEvent e)
{
    if (e.value == MICROBIT_BUTTON_EVT_CLICK)
    {
        uBit.display.scroll("B CLICK");
    }
    if (e.value == MICROBIT_BUTTON_EVT_LONG_CLICK)
    {
        uBit.display.scroll("B LONG");
    }
}

void onButtonAB(MicroBitEvent e)
{
    if (e.value == MICROBIT_BUTTON_EVT_CLICK)
    {
        uBit.display.scroll("AB CLICK");
    }
    if (e.value == MICROBIT_BUTTON_EVT_LONG_CLICK)
    {
        uBit.display.scroll("AB LONG");
    }
}

void onTimerEvent()
{
    uBit.serial.send("in event");
    if(model.timerStatus == 1)
    {
        uBit.display.scroll("HAPPY!!");
        model.timerFlg = 1;
        model.timerStatus = 0;
    }
}

//----------------------------------------------------------------------------------
int getBlockNum()
{
    model.operatingTime = uBit.systemTime();
    model.elapsedTime = (model.setTime - (int)(model.operatingTime - model.startTime));
    //uBit.serial.send(model.elapsedTime);

    int block = (model.elapsedTime / model.blockSurvivalTime / model.updateInterval) + 1;
    uBit.serial.send(block);
    return block;
}

void dispBlock(int block)
{   
    //int y = block / 5 - 1;
    //int x = block % y;

    MicroBitImage block00("0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n");
    MicroBitImage block01("0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n1,0,0,0,0\n");
    MicroBitImage block02("0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n1,0,0,0,0\n1,0,0,0,0\n");
    MicroBitImage block03("0,0,0,0,0\n0,0,0,0,0\n1,0,0,0,0\n1,0,0,0,0\n1,0,0,0,0\n");
    MicroBitImage block04("0,0,0,0,0\n1,0,0,0,0\n1,0,0,0,0\n1,0,0,0,0\n1,0,0,0,0\n");
    MicroBitImage block05("1,0,0,0,0\n1,0,0,0,0\n1,0,0,0,0\n1,0,0,0,0\n1,0,0,0,0\n");
    MicroBitImage block06("1,0,0,0,0\n1,0,0,0,0\n1,0,0,0,0\n1,0,0,0,0\n1,1,0,0,0\n");
    MicroBitImage block07("1,0,0,0,0\n1,0,0,0,0\n1,0,0,0,0\n1,1,0,0,0\n1,1,0,0,0\n");
    MicroBitImage block08("1,0,0,0,0\n1,0,0,0,0\n1,1,0,0,0\n1,1,0,0,0\n1,1,0,0,0\n");
    MicroBitImage block09("1,0,0,0,0\n1,1,0,0,0\n1,1,0,0,0\n1,1,0,0,0\n1,1,0,0,0\n");
    MicroBitImage block10("1,1,0,0,0\n1,1,0,0,0\n1,1,0,0,0\n1,1,0,0,0\n1,1,0,0,0\n");
    MicroBitImage block11("1,1,0,0,0\n1,1,0,0,0\n1,1,0,0,0\n1,1,0,0,0\n1,1,1,0,0\n");
    MicroBitImage block12("1,1,0,0,0\n1,1,0,0,0\n1,1,0,0,0\n1,1,1,0,0\n1,1,1,0,0\n");
    MicroBitImage block13("1,1,0,0,0\n1,1,0,0,0\n1,1,1,0,0\n1,1,1,0,0\n1,1,1,0,0\n");
    MicroBitImage block14("1,1,0,0,0\n1,1,1,0,0\n1,1,1,0,0\n1,1,1,0,0\n1,1,1,0,0\n");
    MicroBitImage block15("1,1,1,0,0\n1,1,1,0,0\n1,1,1,0,0\n1,1,1,0,0\n1,1,1,0,0\n");
    MicroBitImage block16("1,1,1,0,0\n1,1,1,0,0\n1,1,1,0,0\n1,1,1,0,0\n1,1,1,1,0\n");
    MicroBitImage block17("1,1,1,0,0\n1,1,1,0,0\n1,1,1,0,0\n1,1,1,1,0\n1,1,1,1,0\n");
    MicroBitImage block18("1,1,1,0,0\n1,1,1,0,0\n1,1,1,1,0\n1,1,1,1,0\n1,1,1,1,0\n");
    MicroBitImage block19("1,1,1,0,0\n1,1,1,1,0\n1,1,1,1,0\n1,1,1,1,0\n1,1,1,1,0\n");
    MicroBitImage block20("1,1,1,1,0\n1,1,1,1,0\n1,1,1,1,0\n1,1,1,1,0\n1,1,1,1,0\n");
    MicroBitImage block21("1,1,1,1,0\n1,1,1,1,0\n1,1,1,1,0\n1,1,1,1,0\n1,1,1,1,1\n");
    MicroBitImage block22("1,1,1,1,0\n1,1,1,1,0\n1,1,1,1,0\n1,1,1,1,1\n1,1,1,1,1\n");
    MicroBitImage block23("1,1,1,1,0\n1,1,1,1,0\n1,1,1,1,1\n1,1,1,1,1\n1,1,1,1,1\n");
    MicroBitImage block24("1,1,1,1,0\n1,1,1,1,1\n1,1,1,1,1\n1,1,1,1,1\n1,1,1,1,1\n");
    MicroBitImage block25("1,1,1,1,1\n1,1,1,1,1\n1,1,1,1,1\n1,1,1,1,1\n1,1,1,1,1\n");

    MicroBitImage BlockArrey[] = {block00,block01,block02,block03,block04,block05,block06,block07,block08,block09,
                                  block10,block11,block12,block13,block14,block15,block16,block17,block18,block19,
                                  block20,block21,block22,block23,block24,block25};

    uBit.display.print(BlockArrey[block]);
}

//------------------------------------------------
//  main
//------------------------------------------------
int main()
{
    // MicroBitインスタンス初期化
    uBit.init();
    //uBit.serial.send("hello\n");
    
    // モデルインスタンス初期化
    model.init();
    uBit.display.scroll(model.blockNumber);

    // イベント登録
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_EVT_ANY, onButtonA);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_EVT_ANY, onButtonB);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_AB, MICROBIT_EVT_ANY, onButtonAB);

    //MicroBitEvent onTimerEvent(MICROBIT_ID_ANY, MICROBIT_EVT_ANY, CREATE_ONLY);
    //uBit.messageBus.listen(MICROBIT_ID_ANY, MICROBIT_EVT_ANY, onTimerEvent);

    // main ループ
    while(1) 
    {
        uBit.sleep(1000);
        //  タイマー状態：動作時
        if(model.timerStatus == 1)
        {
            int block = getBlockNum();
            dispBlock(block);

            if(model.elapsedTime <= 0 && model.timerFlg == 0)
            {
                uBit.serial.send("send event");
                onTimerEvent();
            }
        }else{

        }
    }
}
