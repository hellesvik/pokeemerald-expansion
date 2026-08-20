#include "global.h"
#include "item_ball.h"
#include "item.h"
#include "random.h"
#include "test/test.h"
#include "constants/items.h"
#include "constants/moves.h"

TEST("Fork item randomizer preserves protected items")
{
    gSaveBlock3Ptr->forkItemRandomizerSeed = 12345;
    ResetForkItemRandomizerState();

    EXPECT_EQ(ResolveForkRandomizedItem(ITEM_HM01, 7), ITEM_HM01);
    EXPECT_EQ(ResolveForkRandomizedItem(ITEM_DEVON_SCOPE, 9), ITEM_DEVON_SCOPE);
}

TEST("Fork item randomizer is stable per source and seed")
{
    enum Item item1;
    enum Item item2;

    gSaveBlock3Ptr->forkItemRandomizerSeed = 54321;
    ResetForkItemRandomizerState();
    item1 = ResolveForkRandomizedItem(ITEM_POTION, 11);
    item2 = ResolveForkRandomizedItem(ITEM_POTION, 11);

    EXPECT_EQ(item1, item2);
}

TEST("Fork item randomizer varies by source")
{
    gSaveBlock3Ptr->forkItemRandomizerSeed = 54321;
    ResetForkItemRandomizerState();

    EXPECT_NE(ResolveForkRandomizedItem(ITEM_POTION, 11), ResolveForkRandomizedItem(ITEM_POTION, 12));
}

TEST("Fork item randomizer hidden items are stable by hidden-item flag")
{
    enum Item item1;
    enum Item item2;

    gSaveBlock3Ptr->forkItemRandomizerSeed = 98765;
    ResetForkItemRandomizerState();
    item1 = ResolveForkRandomizedHiddenItem(ITEM_POTION, FLAG_HIDDEN_ITEMS_START + 3);
    item2 = ResolveForkRandomizedHiddenItem(ITEM_POTION, FLAG_HIDDEN_ITEMS_START + 3);

    EXPECT_EQ(item1, item2);
}

TEST("Fork item randomizer scripted poke balls stay vanilla")
{
    static const u8 sFakeScript[] = {0x00};

    gSaveBlock3Ptr->forkItemRandomizerSeed = 11111;
    ResetForkItemRandomizerState();

    EXPECT_EQ(ResolveForkRandomizedScriptItem(ITEM_POKE_BALL, sFakeScript), ITEM_POKE_BALL);
}

TEST("Fork item randomizer does not duplicate early source assignments")
{
    enum Item items[8];

    gSaveBlock3Ptr->forkItemRandomizerSeed = 22222;
    ResetForkItemRandomizerState();

    for (u32 i = 0; i < ARRAY_COUNT(items); i++)
        items[i] = ResolveForkRandomizedItem(ITEM_POTION, i);

    for (u32 i = 0; i < ARRAY_COUNT(items); i++)
    {
        for (u32 j = i + 1; j < ARRAY_COUNT(items); j++)
            EXPECT_NE(items[i], items[j]);
    }
}

TEST("Fork item randomizer protects hidden progression items")
{
    gSaveBlock3Ptr->forkItemRandomizerSeed = 33333;
    ResetForkItemRandomizerState();

    EXPECT_EQ(ResolveForkRandomizedHiddenItem(ITEM_KEY_TO_ROOM_1, FLAG_HIDDEN_ITEMS_START + 1), ITEM_KEY_TO_ROOM_1);
}

TEST("Fork item randomizer protects scripted HM gifts")
{
    static const u8 sFakeScript[] = {0x00};

    gSaveBlock3Ptr->forkItemRandomizerSeed = 44444;
    ResetForkItemRandomizerState();

    EXPECT_EQ(ResolveForkRandomizedScriptItem(ITEM_HM_FLY, sFakeScript), ITEM_HM_FLY);
}

TEST("Fork item randomizer scripted rewards are location-stable across call order")
{
    static const u8 sScriptA[] = {0x00};
    static const u8 sScriptB[] = {0x00};
    enum Item itemAFirst;
    enum Item itemBSecond;
    enum Item itemBFirst;
    enum Item itemASecond;

    gSaveBlock3Ptr->forkItemRandomizerSeed = 55555;
    ResetForkItemRandomizerState();
    itemAFirst = ResolveForkRandomizedScriptItem(ITEM_POTION, sScriptA);
    itemBSecond = ResolveForkRandomizedScriptItem(ITEM_SUPER_POTION, sScriptB);

    gSaveBlock3Ptr->forkItemRandomizerSeed = 55555;
    ResetForkItemRandomizerState();
    itemBFirst = ResolveForkRandomizedScriptItem(ITEM_SUPER_POTION, sScriptB);
    itemASecond = ResolveForkRandomizedScriptItem(ITEM_POTION, sScriptA);

    EXPECT_EQ(itemAFirst, itemASecond);
    EXPECT_EQ(itemBFirst, itemBSecond);
}

TEST("Fork item randomizer direct item sources are location-stable across call order")
{
    enum Item item0First;
    enum Item item1Second;
    enum Item item1First;
    enum Item item0Second;

    gSaveBlock3Ptr->forkItemRandomizerSeed = 66666;
    ResetForkItemRandomizerState();
    item0First = ResolveForkRandomizedItem(ITEM_POTION, 0);
    item1Second = ResolveForkRandomizedItem(ITEM_SUPER_POTION, 1);

    gSaveBlock3Ptr->forkItemRandomizerSeed = 66666;
    ResetForkItemRandomizerState();
    item1First = ResolveForkRandomizedItem(ITEM_SUPER_POTION, 1);
    item0Second = ResolveForkRandomizedItem(ITEM_POTION, 0);

    EXPECT_EQ(item0First, item0Second);
    EXPECT_EQ(item1First, item1Second);
}

TEST("Fork item randomizer does not yield placeholder TMs")
{
    gSaveBlock3Ptr->forkItemRandomizerSeed = 77777;
    ResetForkItemRandomizerState();

    for (u16 sourceId = 0; sourceId < FORK_ITEM_RANDOMIZER_SOURCE_COUNT; sourceId++)
    {
        enum Item item = ResolveForkRandomizedItem(ITEM_POTION, sourceId);
        if (GetItemPocket(item) == POCKET_TM_HM)
            EXPECT_NE(GetItemTMHMMoveId(item), MOVE_NONE);
    }
}
