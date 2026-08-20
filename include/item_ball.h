#ifndef GUARD_ITEM_BALL_H
#define GUARD_ITEM_BALL_H

void GetItemBallIdAndAmountFromTemplate(void);
enum Item ResolveForkRandomizedItem(enum Item itemId, u16 sourceId);
enum Item ResolveForkRandomizedHiddenItem(enum Item itemId, u16 hiddenItemFlag);
enum Item ResolveForkRandomizedScriptItem(enum Item itemId, const u8 *scriptPtr);
void InitForkItemRandomizerSeed(void);
void ResetForkItemRandomizerState(void);

#endif //GUARD_ITEM_BALL_H
