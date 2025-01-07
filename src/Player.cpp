#include "Player.h"

//===== PLAYER =======//
    struct PlayerOBJ{
        Vector2 positionP;
        bool active = true;
        int PosLeftRightBullet;
        int index;
        int rotation;
        int Speed = 2;
        Texture2D PlayerBoat;
    };PlayerOBJ playerobj;

//===== BULLETS =====//
    typedef struct Shoot{
        Vector2 position;
        Vector2 speed;
        int SpeedBullet = 2;
        int DAMAGE = 1;
        float radius;
        float rotation;
        int lifeSpawn;
        bool active;
        Texture2D BulletTex;
    }Shoot;

    static Shoot shoot[PLAYER_MAX_SHOOTS] = { 0 };
    int TimeforBullets;

///==== PLAYER ======///
    void PlayerInit(){
        Rectangle source = (Rectangle){playerobj.index*OBJ_SIZE,0,OBJ_SIZE,OBJ_SIZE};
        Rectangle dest = (Rectangle){GetScreenWidth()/2,GetScreenHeight()/2,OBJ_SIZE*2,OBJ_SIZE*2};
            if(playerobj.active)DrawTexturePro(playerobj.PlayerBoat, source,dest,playerobj.positionP,0, WHITE);
    }

///==== CONTROLES ====///
    void Controls(){
        if(IsKeyDown(KEY_UP) && playerobj.active && !pclass.InShop){
            playerobj.index = 0;
            playerobj.rotation = 0;
            playerobj.positionP.y+= 1 * playerobj.Speed;
            playerobj.PosLeftRightBullet = 6;
        }
        if(IsKeyDown(KEY_DOWN) && playerobj.active && !pclass.InShop){
            playerobj.index = 4;
            playerobj.rotation = 180;
            playerobj.positionP.y-= 1 * playerobj.Speed;
            playerobj.PosLeftRightBullet = 6;
        }
        if(IsKeyDown(KEY_RIGHT) && playerobj.active && !pclass.InShop){
            playerobj.index = 2;
            playerobj.rotation = 90;
            playerobj.positionP.x-= 1 * playerobj.Speed;
            playerobj.PosLeftRightBullet = 20;
        }
        if(IsKeyDown(KEY_LEFT) && playerobj.active && !pclass.InShop){
            playerobj.index = 6;
            playerobj.rotation = 270;
            playerobj.positionP.x+= 1 * playerobj.Speed;
            playerobj.PosLeftRightBullet = -12;
        }
            if(IsKeyDown(KEY_UP) && IsKeyDown(KEY_RIGHT) && playerobj.active && !pclass.InShop){
                playerobj.index = 1;
                playerobj.rotation = 45;
            }
            if(IsKeyDown(KEY_DOWN) && IsKeyDown(KEY_RIGHT)&& playerobj.active && !pclass.InShop){
                playerobj.index = 3;
                playerobj.rotation = 125;
            }
            if(IsKeyDown(KEY_UP) && IsKeyDown(KEY_LEFT)&& playerobj.active && !pclass.InShop){
                playerobj.index = 7;
                playerobj.rotation = 312;
            }
            if(IsKeyDown(KEY_DOWN) && IsKeyDown(KEY_LEFT)&& playerobj.active && !pclass.InShop){
                playerobj.index = 5;
                playerobj.rotation = 220;
            }
            //== START or RESTART GAME ==//
            if(IsKeyDown(KEY_ENTER) && !playerobj.active && !pclass.InShop && LV.StateGame==2){
                        SM.GameOverAndRestart();
            }
            if(IsKeyDown(KEY_ENTER) && LV.StateGame==1){
                        LV.GameplayInit=true;
            }
        }

///==== SHOOT ====///
    void Bullets(){
        TimeforBullets--;
        if(IsKeyPressed(KEY_SPACE)&& playerobj.active && !pclass.InShop && TimeforBullets < 5){
            TimeforBullets = 8;
            for (int i = 0; i < PLAYER_MAX_SHOOTS; i++){
                    if (!shoot[i].active){
                        shoot[i].position = (Vector2){ -playerobj.positionP.x + playerobj.PosLeftRightBullet +(GetScreenWidth()/2 + sin(playerobj.rotation*DEG2RAD)), -playerobj.positionP.y + 8 +(GetScreenHeight()/2 - cos(playerobj.rotation*DEG2RAD)*(16))};
                        shoot[i].active = true;
                        shoot[i].speed.x = shoot[i].SpeedBullet*sin(playerobj.rotation*DEG2RAD)*shoot[i].SpeedBullet;
                        shoot[i].speed.y = shoot[i].SpeedBullet*cos(playerobj.rotation*DEG2RAD)*shoot[i].SpeedBullet;
                        shoot[i].rotation = playerobj.rotation;
                        break;
                    }
                }
            }
            // Shoot life timer //
            for (int i = 0; i < PLAYER_MAX_SHOOTS; i++){
                if (shoot[i].active) shoot[i].lifeSpawn++;
            }

            // Shot Type Bullets //
            for(int i = 0; i < PLAYER_MAX_SHOOTS; i++){
                if(pclass.BulletTipe==0){ //Less DAMAGE
                    shoot[i].DAMAGE = 1;
                    shoot[i].SpeedBullet = 2;
                    shoot[i].radius = 8;
                }else if(pclass.BulletTipe==1){ //More DAMAGE AND MORE RADIUS
                    shoot[i].DAMAGE = 4;
                    shoot[i].SpeedBullet = 2;
                    shoot[i].radius = 12;
                }else if(pclass.BulletTipe==2){ //More SPEED, More RADIUS
                    shoot[i].DAMAGE = 1;
                    shoot[i].SpeedBullet = 3;
                    shoot[i].radius = 12;
                }
            }

            // Shot logic //
            for (int i = 0; i < PLAYER_MAX_SHOOTS; i++){
                if (shoot[i].active){
                    // Movement //
                    shoot[i].position.x += shoot[i].speed.x;
                    shoot[i].position.y -= shoot[i].speed.y;

                    // Collision: shoot vs walls //
                    if  (shoot[i].position.x > GetScreenWidth()+ shoot[i].radius){
                        shoot[i].active = false;
                        shoot[i].lifeSpawn = 0;
                    }
                    else if (shoot[i].position.x < 0 - shoot[i].radius){
                        shoot[i].active = false;
                        shoot[i].lifeSpawn = 0;
                    }
                    if (shoot[i].position.y > GetScreenHeight() + shoot[i].radius){
                        shoot[i].active = false;
                        shoot[i].lifeSpawn = 0;
                    }
                    else if (shoot[i].position.y < 0 - shoot[i].radius){
                        shoot[i].active = false;
                        shoot[i].lifeSpawn = 0;
                    }

                    // Life of shoot //
                    if (shoot[i].lifeSpawn >= 80){
                        shoot[i].position = (Vector2){0, 0};
                        shoot[i].speed = (Vector2){0, 0};
                        shoot[i].lifeSpawn = 0;
                        shoot[i].active = false;
                    }
                }
            }
    }
