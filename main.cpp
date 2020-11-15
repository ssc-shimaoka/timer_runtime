#include "main.h"
#include <string>

//------------------------------------------------
//  グローバル変数
//------------------------------------------------
myMicroBit    uBit;
Model         model;

void initTimer();
void RingCYARUMERA();
//------------------------------------------------
//  イベントハンドラ
//------------------------------------------------
/***
 *  Aボタン押下イベント
 * 
 */
void onButtonA(MicroBitEvent e)
{
    if (e.value == MICROBIT_BUTTON_EVT_CLICK)
    {
        // タイマー状態：待ち受け時
        if(model.timerStatus == 0)
        {
            initTimer();
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

/***
 *  Bボタン押下イベント
 * 
 */
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

/***
 *  A+Bボタン押下イベント
 * 
 */
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

//------------------------------------------------
//  関数
//------------------------------------------------
/***
 *  タイマー初期化処理
 * 
 */
void initTimer()
{
    // タイマー状態：待ち受け時
    if(model.timerStatus == 0)
    {
        model.setTime = model.blockNumber * model.blockSurvivalTime * model.updateInterval;
        model.timerFlg = 0;
        model.operatingTime = 0;
        model.startTime = 0;
        model.elapsedTime = 0;
        model.pauseStartTime = 0;
        model.pauseEndTime = 0;
        model.pauseTotalTime = 0;
    }
}

/***
 *  タイマー満了処理
 * 
 */
void onTimerEvent()
{
    //uBit.serial.send("in event");
    if(model.timerStatus == 1)
    {
        model.timerFlg = 1;
        model.timerStatus = 0;
        uBit.display.scrollAsync("HAPPY!!");

        RingCYARUMERA();
    }
}

/***
 *  残りブロック数計算
 * 
 */
int getBlockNum()
{
    // 現在の稼働時間取得
    model.operatingTime = uBit.systemTime();
    // 残りブロック数計算
    model.elapsedTime = (model.setTime - (int)(model.operatingTime - model.startTime));
    int block = (model.elapsedTime / model.blockSurvivalTime / model.updateInterval);
    
    return block;
}

/***
 *  ブロック表示処理
 * 
 */
void dispBlock(int block, int z)
{  
    int line = block / 5;
    int individual = block % 5;

    MicroBitImage Block("0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n");

    for(int i = 0; i < line; i ++)
    {
        Block.setPixelValue(i,0,255);
        Block.setPixelValue(i,1,255);
        Block.setPixelValue(i,2,255);
        Block.setPixelValue(i,3,255);
        Block.setPixelValue(i,4,255);
    }

    for(int j = 0; j <= individual; j++)
    {
        if(j == individual)
        {
            Block.setPixelValue(line, 4-j, 255);
            uint8_t lightLevel = (uint8_t)(255 / z);
            uBit.serial.send(lightLevel);
        }else{
            Block.setPixelValue(line,4-j,255);
        }
    }

    uBit.display.print(Block);
}

/***
 * チャルメラ鳴らす
 * 
 */
void RingCYARUMERA()
{
    // チャルメラ？
    uBit.io.P0.setAnalogValue(512);

    uBit.io.P0.setAnalogPeriodUs(5000); // ド（低）
    uBit.sleep(500);
    uBit.io.P0.setAnalogPeriodUs(4500); // レ
    uBit.sleep(500);
    uBit.io.P0.setAnalogPeriodUs(4000); // ミ
    uBit.sleep(500);
    uBit.io.P0.setAnalogPeriodUs(4500); // レ
    uBit.sleep(500);
    uBit.io.P0.setAnalogPeriodUs(5000); // ド
    uBit.sleep(500);

    uBit.io.P0.setAnalogValue(0);
    uBit.sleep(500);

    uBit.io.P0.setAnalogValue(512);
    uBit.io.P0.setAnalogPeriodUs(5000); // ド（低）
    uBit.sleep(500);
    uBit.io.P0.setAnalogPeriodUs(4500); // レ
    uBit.sleep(500);
    uBit.io.P0.setAnalogPeriodUs(4000); // ミ
    uBit.sleep(500);
    uBit.io.P0.setAnalogPeriodUs(4500); // レ
    uBit.sleep(500);
    uBit.io.P0.setAnalogPeriodUs(5000); // ド
    uBit.sleep(500);

    uBit.io.P0.setAnalogPeriodUs(4500); // レ
    uBit.sleep(3000);
    uBit.io.P0.setAnalogValue(0);
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

    // イベント登録
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_EVT_ANY, onButtonA);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_EVT_ANY, onButtonB);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_AB, MICROBIT_EVT_ANY, onButtonAB);

    int z = 1;
    // main ループ
    while(1) 
    {
        uBit.sleep(1000);
        //  タイマー状態：動作時
        if(model.timerStatus == 1)
        {
            if(z > model.blockSurvivalTime)
            {
                z = 1;
            }
            int block = getBlockNum();
            dispBlock(block, z);
            z = z + 1;

            if(model.elapsedTime <= 0 && model.timerFlg == 0)
            {
                uBit.serial.send("send event");
                onTimerEvent();
            }
        }
    }
}
