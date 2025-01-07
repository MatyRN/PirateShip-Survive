int TimeAnimmShop = 30;
int TimeAnimm = 50;
int TimeTextWaves = 50;
float TimeTitle = 50, TimeTextStart =50;

int indexanimText = -300;
int indexTextStart = 300;
int indexTitle = 20;

///===== TITLE ====///
int TitleAnim(){
    TimeTitle--;
        if(TimeTitle>=20 && LV.GameplayInit==false){
            indexTitle--;
        }else if (TimeTitle>=10 && LV.GameplayInit==false){
            indexTitle++;
        }else if (TimeTitle>=0 && LV.GameplayInit==false){
            TimeTitle=30;
        }else if(indexTitle>=-300 && LV.GameplayInit==true){
            indexTitle-= 4;
        }else if (indexTitle<=-300 && LV.GameplayInit==true){
            indexTitle=-300;
            SM.Gameplay();
        }
        return indexTitle;
}

///===== START-TITLE =====///
int StartAnim(){
        if(indexTextStart<=600 && LV.GameplayInit==true){
            indexTextStart+= 4;
        }else if (indexTextStart>=600 && LV.GameplayInit==true){
            indexTextStart=600;
        }
        return indexTextStart;
}

///==== ANIMATIONS-TENDER ====///
int TenderAnimation(){
//== Simple Line Time Tender ==///
    TimeAnimm-=0.5;
    int indexanimTender;
        if(TimeAnimm>=50){
            indexanimTender = 0;
        }else if(TimeAnimm>=40){
            indexanimTender = 1;
        }else if(TimeAnimm >=30){
            indexanimTender = 0;
        }else if(TimeAnimm >=20){
            indexanimTender = 1;
        }else if (TimeAnimm >= 10){
            indexanimTender = 2;
        }else if (TimeAnimm >= 5){
            indexanimTender = 3;
            TimeAnimm = 50;
        }
        return indexanimTender;
    }

///==== ANIMATION-SHOP ====//
int ShopAnimation(){
//== Simple Line Time Tender ==///
    TimeAnimmShop--;
    int indexanimShop;
        if(TimeAnimmShop >= 30){
            indexanimShop = 0;
        }else if(TimeAnimmShop >= 20){
            indexanimShop = 1;
        }else if (TimeAnimmShop >= 10){
            indexanimShop = 2;
            TimeAnimmShop = 30;
        }
        return indexanimShop;
}

///==== TEXT-APPEARANCES ====///
void TextWavesRest(){
        if ((indexanimText >= 800) && LV.TextWaves == true){
            indexanimText = -300;
            LV.TextWaves = false;
            PlaySound(LV.sfxRound);
        }else{
            indexanimText+= 10;
        }

        ///===Type of Wave===///
            if(LV.WavesCount<=1){
                DrawText("-IS BUY TIME-",indexanimText,200,30,WHITE);
            }else{
                DrawText("-NEXT WAVE-",indexanimText,200,30,WHITE);
            }
}
