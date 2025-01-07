#include "Librerias_Y_Variables.h"
class SpritesAndMap{
    public:
        void InitTexture(); //ALL TEXTURES//
        void MAP(); //BACKGROUND//
        void ALLDraw(); //Draw All Object In Map//
        void Update();
        void SoundsInit(); //Initt Sounds//
        void GameOverAndRestart(); //Gameover//
        void Menu();  //MENU//
        void Intro(); //SPLASH IMAGE//
        void Gameplay(); //GAMEPLAY//

    //Sprites For Maps//
        Vector2 WaterPos;
        Rectangle WaterSRC;
        Texture2D Water;
        Texture2D Title;
        Texture2D AutorSplashImage;
};SpritesAndMap SM;

