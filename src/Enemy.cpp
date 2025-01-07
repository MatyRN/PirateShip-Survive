#include "Enemy.h"

//==== ENEMY ====//
typedef struct EnemyOBJ{
    Texture2D Enemy;
    Texture2D OtherEnemy;
    Vector2 position;
    int speed;
    float rotation;
    float radius;
    int life;
    int index;
    bool active;
} EnemyOBJ;

static EnemyOBJ enemy[ENEMY_MAX] = { 0 };

///====== ENEMY-INIT ======///
    void EnemyInit(int PositionWaves){
            int OtherRoy;
        if(!LV.PauseWaves){
            for(LV.EnemysActives= 0 ; LV.EnemysActives < ENEMY_MAX; LV.EnemysActives++){
                OtherRoy = rand() % 59 - 60;
                        enemy[LV.EnemysActives].position = (Vector2){90 * LV.EnemysActives,(10 * LV.EnemysActives) + PositionWaves - OtherRoy};
                        enemy[LV.EnemysActives].speed = 0;
                        enemy[LV.EnemysActives].radius = 5;
                        enemy[LV.EnemysActives].life= 4;
                        enemy[LV.EnemysActives].active=true;
                        enemy[LV.EnemysActives].Enemy = LoadTexture("res/BoatEnemyDificult.png");
                        LV.EnemysActivesNOW= LV.EnemysActives + 1;
                    }
            }
    }

///====== ENEMY-UPDATE =====///
    void EnemyUpdate(){
        Vector2 TruepositionPlayer =(Vector2){-playerobj.positionP.x + 6 + GetScreenWidth()/2 + sin(playerobj.rotation*DEG2RAD),-playerobj.positionP.y + 6 + GetScreenHeight()/2 - cos(playerobj.rotation*DEG2RAD)*(16)};

    //Conditional of Waves//
    if(!LV.PauseWaves){
        for(LV.EnemysActives=0;LV.EnemysActives<ENEMY_MAX;LV.EnemysActives++){
            if(enemy[LV.EnemysActives].active){
                if((TruepositionPlayer.x > enemy[LV.EnemysActives].position.x)){//DERECHA
                    enemy[LV.EnemysActives].position.x +=1 + enemy[LV.EnemysActives].speed;
                    enemy[LV.EnemysActives].index = 4;
                }
                if((TruepositionPlayer.x < enemy[LV.EnemysActives].position.x)){//IZQUIERDA
                    enemy[LV.EnemysActives].position.x -=1 + enemy[LV.EnemysActives].speed;
                    enemy[LV.EnemysActives].index = 12;
                }
                if((TruepositionPlayer.y > enemy[LV.EnemysActives].position.y)){//ABAJO
                    enemy[LV.EnemysActives].position.y +=1 + enemy[LV.EnemysActives].speed;
                    enemy[LV.EnemysActives].index = 8;
                }
                if((TruepositionPlayer.y < enemy[LV.EnemysActives].position.y)){//ARRIBA
                    enemy[LV.EnemysActives].position.y -=1 + enemy[LV.EnemysActives].speed;
                    enemy[LV.EnemysActives].index = 0;
                }
                    if((TruepositionPlayer.x > enemy[LV.EnemysActives].position.x)&& TruepositionPlayer.y < enemy[LV.EnemysActives].position.y){//ARRIBA Y DERECHA
                        enemy[LV.EnemysActives].index = 2;
                    }
                    else if((TruepositionPlayer.x > enemy[LV.EnemysActives].position.x)&& TruepositionPlayer.y > enemy[LV.EnemysActives].position.y){//ABAJO y DERECHA
                        enemy[LV.EnemysActives].index = 6;
                    }
                    else if((TruepositionPlayer.y < enemy[LV.EnemysActives].position.y)&& TruepositionPlayer.x < enemy[LV.EnemysActives].position.x ){//ARRIBA y IZQUIERDA
                        enemy[LV.EnemysActives].index = 14;
                    }
                    else if((TruepositionPlayer.y > enemy[LV.EnemysActives].position.y)&& TruepositionPlayer.x < enemy[LV.EnemysActives].position.x ){//ABAJO Y IZQUIERDA
                        enemy[LV.EnemysActives].index = 10;
                    }
                }
        }
    }

    //COLISION LOGIC//
    if(!LV.PauseWaves){
    for(LV.EnemysActives=0;LV.EnemysActives<ENEMY_MAX;LV.EnemysActives++){
            for(int j=0;j<PLAYER_MAX_SHOOTS;j++){
        //COLISION con la BALA//
            if (CheckCollisionCircles(enemy[LV.EnemysActives].position, enemy[LV.EnemysActives].radius, shoot[j].position, shoot[j].radius) && enemy[LV.EnemysActives].active==true && shoot[j].active==true){
                    enemy[LV.EnemysActives].life-= shoot[j].DAMAGE;
                    shoot[j].lifeSpawn=0;
                    shoot[j].active=false;
            }
        }
        if(enemy[LV.EnemysActives].active){
            if(CheckCollisionCircles((Vector2){enemy[LV.EnemysActives].position.x,0},enemy[LV.EnemysActives].radius,(Vector2){enemy[LV.EnemysActives].position.x,0},enemy[LV.EnemysActives].radius)){
                enemy[LV.EnemysActives].position.x--;
            }
            if(CheckCollisionCircles((Vector2){-enemy[LV.EnemysActives].position.x,0},enemy[LV.EnemysActives].radius,(Vector2){-enemy[LV.EnemysActives].position.x,0},enemy[LV.EnemysActives].radius)){
                enemy[LV.EnemysActives].position.x++;
            }
        }

        //Colision de Enemigos con el jugador.
        if(CheckCollisionCircles(enemy[LV.EnemysActives].position,enemy[LV.EnemysActives].radius,TruepositionPlayer,10)&& enemy[LV.EnemysActives].active==true){
            PlaySound(LV.sfxDefeat);
            playerobj.active=false;
            LV.GameOver=true;
        }
    }
}
}

