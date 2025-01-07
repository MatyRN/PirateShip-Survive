#include "SpritesAndMap.cpp"
//Only WiiPort

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  #Pirate Ship Survive                                                                                                   //
//      & Author MatiasRN - Alias: MatRN                                                                                   //
//                                                                                                                         //
//  Description: This is a simple game or Engine of Ships and Waves, make in Raylib, a C++ and C library.                            //
//  I publish this code so that anyone can modify the game for learning purposes.                                          //
//  Recommendation: analyze the Code to understand the operation of the engine.                                            //
//                                                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///===MAIN====//
int main(){
//--------------------------------------------------------------------------------------//
    InitWindow(LV.ScreenWidth, LV.ScreenHeight, "PirateShip Survive");
    SetTargetFPS(30);
    Intro();
//--------------------------------------------------------------------------------------//

///===LOOP===///
while (!WindowShouldClose()){
    ///=======ALL STATE GAMES========///
        ///==State of Game -SPLASH IMAGE- ==///
            if(LV.StateGame==0){
                LV.TimmerGame--;
                    if(LV.TimmerGame<0){
                        LV.TimmerGame=0;
                        SM.Menu();
                    }
                    SM.ALLDraw();
            }
        ///==State of Game -MENU- ==//
            if(LV.StateGame==1){
                SM.ALLDraw();
                Controls();
            }
        ///==State of Game -GAMEPLAY- ==//
        if(LV.StateGame==2){
            SM.ALLDraw();
            if(!LV.GameOver){
                Bullets();
                EnemyUpdate();
            }
            Controls();
        }
    }
//=================================//
    CloseWindow();
    UnloadTexture(playerobj.PlayerBoat);
    return 0;
//=================================//
}
