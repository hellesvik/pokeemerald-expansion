#include "global.h"
#include "item.h"
#include "test/test.h"
#include "constants/items.h"

extern bool8 HasAllRegiEmeralds(void);

TEST("Sealed Chamber stays locked until all Regi Emeralds are collected")
{
    for (enum Item emerald = ITEM_REGI_EMERALD_RED; emerald <= ITEM_REGI_EMERALD_BLACK; emerald++)
        RemoveBagItem((enum Item)emerald, 1);

    for (enum Item emerald = ITEM_REGI_EMERALD_RED; emerald < ITEM_REGI_EMERALD_BLACK; emerald++)
        AddBagItem((enum Item)emerald, 1);

    EXPECT_EQ(HasAllRegiEmeralds(), FALSE);
    AddBagItem(ITEM_REGI_EMERALD_BLACK, 1);
    EXPECT_EQ(HasAllRegiEmeralds(), TRUE);
}
