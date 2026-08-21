#ifndef GUARD_FORK_GIFT_POKEMON_RANDOMIZER_H
#define GUARD_FORK_GIFT_POKEMON_RANDOMIZER_H

#include "global.h"

enum Species GetForkRandomizedStarterSpecies(u8 slot);
enum Species GetForkRandomizedStevenGiftSpecies(void);
void ApplyForkStarterPerfectIvs(struct Pokemon *mon, u8 starterSlot);

#endif // GUARD_FORK_GIFT_POKEMON_RANDOMIZER_H
