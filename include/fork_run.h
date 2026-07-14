#ifndef GUARD_FORK_RUN_H
#define GUARD_FORK_RUN_H

#include "global.h"
#include "pokemon.h"

void ForkResetAreaEncounterState(void);
bool32 ForkIsAreaEncounterSpent(mapsec_u8_t mapSecId);
void ForkSetAreaEncounterSpent(mapsec_u8_t mapSecId);
bool32 ForkPlayerOwnsSpeciesFamily(enum Species species);
bool32 ForkIsSoftNuzlockeMon(struct Pokemon *mon);
void ForkEnsureKeyItemsPresent(void);
void ForkInvalidateOwnedFamilyCache(void);
void ForkRecordOwnedSpecies(enum Species species);
void ForkScrubPlayerOwnedMons(void);
void ForkNormalizePlayerMon(struct Pokemon *mon);
void ForkPrepareWildEncounter(void);
void ForkResolveWildEncounter(void);
void ForkFinalizeWildEncounter(void);
bool32 ForkCanCatchCurrentEncounter(void);
bool32 ForkShouldRejectSelectedBall(u16 itemId);
bool32 ForkShouldShowFirstEncounterIndicator(void);
bool32 ForkShouldBlockEggHatchInCurrentArea(void);
void ForkSpendCurrentAreaEncounter(void);
void ForkApplySoftNuzlockeWhiteOutPenalty(void);

#endif
