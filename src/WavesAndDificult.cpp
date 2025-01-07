#include "WavesAndDificult.h"

///======WAVES======///
void WavesAndDificult::Waves(){
        ///STOPWAVES//
            if((LV.EnemysActivesNOW == 0) && !LV.PauseWaves){
                DrawText("NEXT WAVE",GetScreenWidth() / 3.15,GetScreenHeight() / 2.60,50,WHITE);
                LV.EnemysActives = 0;
                LV.WavesCount--;
                    EnemyInit(GetRenderHeight() + 30);
                        if(LV.WavesCount<=0){
                            DrawText("Time to Buy",GetScreenWidth() / 3.15,GetScreenHeight() / 2.60,50,WHITE);
                            LV.PauseWaves=true;
                        }
            }
        ///IF DEAD//
            if(LV.GameOver){
                DrawText("GAMEOVER",GetScreenWidth() / 3.15,GetScreenHeight() / 2.60,50,WHITE);
                DrawText("Press START to Restart",GetScreenWidth() / 3,GetScreenHeight() / 2,20,WHITE);
            }
}
