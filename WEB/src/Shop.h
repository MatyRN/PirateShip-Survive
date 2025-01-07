#define OBJ_SIZE_BIG 64
#define OBJ_COUNT_LITLE 3
class Shop {
    public:
    //=== SHOP ===//
        void InitShop();
        void AparaceShop();
        void BuyInShop();
        void Difficult();

    //=== ITEMS ===//
        int SelectItem;
        bool FinishBuy;
        int PointerY = 85;

};Shop shop;
