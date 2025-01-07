//===ENGINE LIBRARIES===//
#include "raylib.h"
#include "math.h"
#include <stdlib.h>

//===DEFINES IN GAME===//
#define PLAYER_MAX_SHOOTS  20
#define ENEMY_MAX 15
#define OBJ_SIZE 16
#define OBJ_COUNT 5
#define PLAYER_MAX_SHOOTS  15

///==== LIBRARIES ====///
class LibreriasYVariables{
    public:
        ///==== VARIABLES-GLOBALS ====///
        const int ScreenWidth = 800;
        const int ScreenHeight = 450;
        int StateGame = 0;//0 Splash Image, 1 Menu , 2 Game .
        bool GameplayInit = false;
        int TimmerGame = 100;

        ///=== VARIABLE-OF-TEXTURES ===//
        int MyScore;
        int Score;

        ///=== DIFICULT-AND-WAVES ===///
        int DifficultLevel = 0; /*If Difficult is equals to 0
                                1 = More Speed Enemy Ships
                                2 = More Speed Enemy Ships
                                3 = 3 Waves
                                4 = More Speed Enemy Ships
                                5 = Other Enemy Maybe
                                6 = 4 Waves
                                7 = And is*/
        bool TextWaves = false;
        int NumberWaves = 2;
        bool PauseWaves = false;
        int WavesCount = 2;//Waves 2 Standard
        int EnemysActives = 0;
        int EnemysActivesNOW = 0;
        bool GameOver = false;

        ///===== SOUNDS =====///
        Sound sfxDestroyBoats;
        Sound sfxDefeat;
        Sound sfxBuy;
        Sound sfxSelectASound;
        Sound sfxSelectBSound;
        Sound sfxSelectCSound;
        Sound sfxRound;
        Sound sfxOtherSound;

        ///===== MUSIC =====///
        Music Menu_theme;
        Music Gameplay_theme;

};LibreriasYVariables LV;
