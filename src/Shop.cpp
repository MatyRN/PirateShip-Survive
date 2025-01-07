#include "SHOP.h"
#include "Animations.cpp"

int MovePannel = 1;

Enemy En;
Texture2D PointerShop;

//====UIShop====//
struct ShopUI{
    Texture2D UIShop;
    Vector2 position;
    Rectangle shopuisrc;
};ShopUI shopui;

//===STRUCT TENDER SHOP===//
struct ShopTENDER{
    Texture2D TenderShop;
    Vector2 position;
    Rectangle shoptendersource;
    Rectangle shoptenderdest;
    int State = 1;
};ShopTENDER shoptender;

//===STRUCT OBJECT SHOP===//
struct ShopOBJ{
    Texture2D ShopTex;
    Vector2 position;
    Rectangle shopbasesource;
    Rectangle shopbasedest;
    int State=1;
    float radius = 50;
};ShopOBJ shopobj;

///=======INITIALIZER_SHOP=====///
void Shop::InitShop(){
    //Init the sprite of Base Shop
    PointerShop = LoadTexture("res/Pointer.png");
    shopobj.ShopTex = LoadTexture("res/Shop.png");
    shopobj.position = (Vector2){0,0};
    shopobj.shopbasedest = (Rectangle){310,160,OBJ_SIZE_BIG*2,OBJ_SIZE_BIG*2}; //340x 180y

    //Init the sprite of Tender
    shoptender.TenderShop = LoadTexture("res/ShopTender.png");
    shoptender.position = (Vector2){-135,-60};
    shoptender.shoptenderdest = (Rectangle){0,0,150,150};

    //Init the sprite of UI
    shopui.UIShop = LoadTexture("res/UITender.png");
    shopui.position = (Vector2){100,30};
    shopui.shopuisrc = (Rectangle){0,0,600,400};
}

///===== APPEARS_THE_SHOP =====///
void Shop::AparaceShop(){
    if(!LV.WavesCount==true){
            shopobj.State = ShopAnimation();
            shopobj.shopbasesource = (Rectangle){shopobj.State*OBJ_SIZE_BIG,0,64,OBJ_SIZE_BIG};
            DrawTexturePro(shopobj.ShopTex,shopobj.shopbasesource,shopobj.shopbasedest,shopobj.position,0,WHITE);
        //If your boat colision to shop, open the box shop//
        if(pclass.InShop==true){
        shop.BuyInShop();
    }
    ///======COLISION======///
        if(CheckCollisionCircles(playerobj.positionP,20,shopobj.position,shopobj.radius)){
            pclass.InShop=true;
        }
    }
}

///===== BUY_IN_THE_SHOP ====///
void Shop::BuyInShop(){
            ///=== ANIM Tender ==//
            shoptender.State = TenderAnimation();
            shoptender.shoptendersource = (Rectangle){shoptender.State*OBJ_SIZE_BIG,0,64,OBJ_SIZE_BIG};

            ///=== ANIM Shop ==//
            shopobj.State = ShopAnimation();
            shopobj.shopbasesource = (Rectangle){shopobj.State*OBJ_SIZE_BIG,0,OBJ_SIZE_BIG,OBJ_SIZE_BIG};

            DrawTextureRec(shopui.UIShop,shopui.shopuisrc,shopui.position,WHITE);
            DrawTexturePro(shoptender.TenderShop,shoptender.shoptendersource,shoptender.shoptenderdest,shoptender.position,0,WHITE);
            DrawTexture(PointerShop,370,shop.PointerY,WHITE);
                DrawText(TextFormat("More Damage+"),400,80,30,BLACK);//Increment Damage
                DrawText(TextFormat("More Speed+"),400,130,30,BLACK);//Increment Speed
                DrawText(TextFormat("Normal Bullets"),400,180,30,BLACK);//More Damage, Minus Speed
                DrawText(TextFormat("Fragment Bullets"),400,230,30,BLACK);//More Radius Minus Damage
                DrawText(TextFormat("Shuriken Bullets"),400,280,30,BLACK);//More Radius Minus Damage

//==== Movement to Pointer ====//
if(IsKeyDown(KEY_UP)&& shop.PointerY>=105){
                    PlaySound(LV.sfxSelectASound);
                    PointerY-=50;
}else if (IsKeyDown(KEY_DOWN)&& shop.PointerY<=245){
                    PlaySound(LV.sfxSelectBSound);
                    PointerY+=50;
        }else if (IsKeyDown(KEY_SPACE)){
                    PlaySound(LV.sfxBuy);
                    //=== Items Select ===//
                    switch(shop.PointerY){
                        case 85://Upgrade Damage
                            for(int i = 0; i < PLAYER_MAX_SHOOTS; i++){
                                shoot[i].DAMAGE+=1;
                            }
                            playerobj.positionP = (Vector2){50,50};
                            pclass.InShop=false;
                            Difficult();
                            break;
                        case 135://Speed Upgrade
                            if(playerobj.Speed<6){
                                playerobj.Speed+=1;
                            }
                            playerobj.positionP= (Vector2){50,50};
                            pclass.InShop=false;
                            Difficult();
                            break;
                        case 185://BulletTipe
                            pclass.BulletTipe = 0;
                            playerobj.positionP= (Vector2){50,50};
                            pclass.InShop=false;
                            Difficult();
                            break;
                        case 235://Bullet Tipe 1
                            pclass.BulletTipe = 2;
                            playerobj.positionP = (Vector2){50,50};
                            pclass.InShop=false;
                            Difficult();
                            break;
                        case 285://Bullet Tipe 2
                            pclass.BulletTipe = 3;
                            playerobj.positionP = (Vector2){50,50};
                            pclass.InShop = false;
                            Difficult();
                            break;
                    }
                }

}

///==== DIFICULT OF GAME ====///
void Shop::Difficult(){
    LV.DifficultLevel++;
        if(LV.DifficultLevel % 1 == 1){ //More Speed to Enemy Ships
            for(LV.EnemysActives=0; LV.EnemysActives<ENEMY_MAX; LV.EnemysActives++){
                enemy[LV.EnemysActives].speed += 0.5;
                enemy[LV.EnemysActives].life += 0.5;
            }
        }else if(LV.DifficultLevel % 3 == 1){//More Waves
                LV.NumberWaves++;
        }
            LV.WavesCount = LV.NumberWaves;
            LV.PauseWaves = false;
            EnemyInit(-80);
}
