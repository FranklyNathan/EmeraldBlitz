#ifndef GUARD_SHOP_H
#define GUARD_SHOP_H

extern struct ItemSlot gMartPurchaseHistory[3];

// Max number of mini icons shown for a hovered TM (4 per row, 2 rows).
#define MAX_SHOP_POKEMON_ICONS 8

void CreatePokemartMenu(const u16 *itemsForSale);
void CreateDecorationShop1Menu(const u16 *itemsForSale);
void CreateDecorationShop2Menu(const u16 *itemsForSale);
void CreateScottTmShopMenu(void);
void CB2_ExitSellMenu(void);
void CreateShopPokemonIconSprites(u16 itemId, u8 *spriteIds);
bool8 IsInEliteFourArea(void);

#endif // GUARD_SHOP_H
