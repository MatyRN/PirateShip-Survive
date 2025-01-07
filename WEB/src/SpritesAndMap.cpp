#include "SpritesAndMap.h"
#include "Player.cpp"
#include "Enemy.cpp"
#include "Shop.cpp"

    ///==== INTRO ====/// -StateGame 0-
    void Intro(){
        SM.InitTexture();
        SM.SoundsInit();
        EnemyInit(-120);
    }

    ///==== MENU ====/// -StateGame 1-
    void SpritesAndMap::Menu(){
        PlayMusicStream(LV.Menu_theme);
        LV.StateGame=1;
    }

    ///==== GAMEPLAY ====/// -StateGame 2-
    void SpritesAndMap::Gameplay(){
        StopMusicStream(LV.Menu_theme);
        PlayMusicStream(LV.Gameplay_theme);
        LV.StateGame=2;
    }

    ///===== INITTEXTURE ===///
    void SpritesAndMap::InitTexture(){
        playerobj.PlayerBoat = LoadTexture("res/Boat.png");
        SM.Water = LoadTexture("res/Water.png");
        SM.Title = LoadTexture("res/Title.png");
        SM.AutorSplashImage = LoadTexture("res/SplashImage.png");
        shop.InitShop();

        //Inititilize the BULETS textures and position//
            for(int i=0;i < PLAYER_MAX_SHOOTS;i++){
                shoot[i].position = (Vector2){0,0};
                shoot[i].speed = (Vector2){0,0};
                shoot[i].radius = 8;
                shoot[i].active = false;
                shoot[i].lifeSpawn = 0;
                shoot[i].BulletTex = LoadTexture("res/Bullet.png");
            }
    }

    ///=== UPDATE THE DRAWS ===//
    void SpritesAndMap::ALLDraw(){
        BeginDrawing();
            ClearBackground(RAYWHITE);
                if(!LV.StateGame==0){
                    MAP();
                }
                if(LV.StateGame==2){
                    if(!LV.GameOver){
                        PlayerInit();
                        shop.AparaceShop();
                }
            }
            Update();
            EndDrawing();
    }

    //====== MAP ======//
    void SpritesAndMap::MAP(){
        //===DRAW THE WATER===//
            for(int iX=-10;iX<120;iX++){
                for(int iY=-10;iY<75;iY++){
                DrawTexture(Water, iX*16, iY*16, WHITE);
            }
        }
    }

    ///=== SFX ===///
    void SpritesAndMap::SoundsInit(){
        InitAudioDevice();

        //FILE SOUND//
            LV.Menu_theme = LoadMusicStream("res/music/PirateGameMenu.mp3");
            LV.Gameplay_theme = LoadMusicStream("res/music/PirateGameGameplay.mp3");
            LV.sfxDestroyBoats = LoadSound("res/sfx/DestroyBoats.wav");
            LV.sfxDefeat = LoadSound("res/sfx/GameoverSFX.wav");
            LV.sfxBuy = LoadSound("res/sfx/BuySFX.wav");
            LV.sfxSelectASound = LoadSound("res/sfx/SelectSFX_A.wav");
            LV.sfxSelectBSound = LoadSound("res/sfx/SelectSFX_B.wav");
            LV.sfxSelectCSound = LoadSound("res/sfx/SelectSFX_C.wav");
            LV.sfxRound = LoadSound("res/sfx/RoundSFX.wav");
            LV.sfxOtherSound = LoadSound("res/sfx/SoundSFX.wav");
    }

    ///==== UPDATE =====///
    void SpritesAndMap::Update(){
        //Update In State Game 0
        if(LV.StateGame==0){
            Rectangle sourceAutor;
            sourceAutor = (Rectangle){0,0,250,240};
            DrawTextureRec(SM.AutorSplashImage,sourceAutor,(Vector2){static_cast<float>(GetScreenWidth() / 3),static_cast<float>(TitleAnim() + 80)},WHITE);
        }
        //Update In State Game 1//
        if(LV.StateGame==1){
            UpdateMusicStream(LV.Menu_theme);
            Rectangle sourceTitle;
            sourceTitle = (Rectangle){0,0,720,300};
            DrawTextureRec(SM.Title,sourceTitle,(Vector2){static_cast<float>(GetScreenWidth() / 18), static_cast<float>(TitleAnim())},WHITE);
            DrawText("Press START",static_cast<float>(GetScreenWidth() / 2.5),static_cast<float>(StartAnim()),20,WHITE);
        }

        //Update In State Game 2//
        if(LV.StateGame==2){
            //Update Music//
            UpdateMusicStream(LV.Gameplay_theme);

            //Enemy -others-//
            Rectangle sourceEnemy;
            Rectangle sourceSHOTS;

        //=====Draw shoot=====//
            for (int i = 0; i < PLAYER_MAX_SHOOTS; i++){
                    sourceSHOTS = (Rectangle){static_cast<float>(pclass.BulletTipe*OBJ_SIZE),0,OBJ_SIZE,OBJ_SIZE};
                if (shoot[i].active)DrawTextureRec(shoot[i].BulletTex,sourceSHOTS,shoot[i].position, WHITE);
            }

        //====Draw Enemy====//
        if(!LV.PauseWaves){
            for(LV.EnemysActives = 0; LV.EnemysActives < ENEMY_MAX; LV.EnemysActives++){
                if(enemy[LV.EnemysActives].active){
                        if(enemy[LV.EnemysActives].life < 1){
                                PlaySound(LV.sfxDestroyBoats);
                                enemy[LV.EnemysActives].active=false; LV.MyScore = LV.MyScore + 10;
                                LV.EnemysActivesNOW = LV.EnemysActivesNOW - 1;
                        }
                         sourceEnemy = (Rectangle){static_cast<float>(enemy[LV.EnemysActives].index*8),0,OBJ_SIZE,OBJ_SIZE};
                         DrawTextureRec(enemy[LV.EnemysActives].Enemy,sourceEnemy,enemy[LV.EnemysActives].position,WHITE);
                }
            }
        }

        ///DRAWUI
        DrawText(TextFormat("SCORE: %i",LV.MyScore),GetScreenWidth() / 2.25,14,20,WHITE);
        //DrawText(TextFormat("Dificultad: %i",LV.DifficultLevel),10,400,20,WHITE);
        //DrawText(TextFormat("Bullet: %i",TimeforBullets),10,370,20,WHITE);
        //DrawText(TextFormat("Bullet Type: %i",pclass.BulletTipe),10,330,20,WHITE);

        ///STOPWAVES
            if((LV.EnemysActivesNOW == 0) && !LV.PauseWaves){
                    int RandInt;
                    LV.TextWaves = true;
                    TextWavesRest();

                //==Wave UP or DOWN==//
                if(LV.TextWaves == false){
                        RandInt = rand() % 2;
                        LV.WavesCount--;
                        if(RandInt==0){
                            EnemyInit(GetRenderHeight() + 60);
                        }else if(RandInt==1){
                            EnemyInit(-140);
                        }

                    //==Desactivate Waves==//
                        if(LV.WavesCount<=0){
                            LV.PauseWaves=true;
                        }
                    }
            }

        ////=====GAMEOVER=====////
            if(LV.GameOver){
                DrawText("GAMEOVER",GetScreenWidth() / 3.15,GetScreenHeight() / 2.60,50,WHITE);
                DrawText("Press START to Restart",GetScreenWidth() / 3,GetScreenHeight() / 2,20,WHITE);
            }
        }
    }

    ///==== RESTART GAME ====///
    void SpritesAndMap::GameOverAndRestart(){
        for (int i = 0;i < PLAYER_MAX_SHOOTS;i++){
            shoot[i].active=false;
        }
            for (LV.EnemysActives = 0;LV.EnemysActives < ENEMY_MAX;LV.EnemysActives++){
                enemy[LV.EnemysActives].active=false;
            }
                LV.GameOver=false;
                LV.WavesCount=2;
                LV.PauseWaves=false;
                LV.MyScore=0;
                LV.DifficultLevel=0;

                    //Player Respawn//
                    playerobj.active=true;
                    playerobj.positionP.x = GetScreenWidth()/18;
                    playerobj.positionP.y = GetScreenHeight()/8;
                    pclass.BulletTipe=0;

                    //Enemys Respawn//
                    EnemyInit(-150);
    }
