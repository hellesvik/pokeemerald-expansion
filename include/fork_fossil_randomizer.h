#ifndef GUARD_FORK_FOSSIL_RANDOMIZER_H
#define GUARD_FORK_FOSSIL_RANDOMIZER_H

#include "global.h"

enum Item GetForkMirageTowerFossil(u8 choice);
enum Species GetForkFossilRevivalSpecies(enum Item item);
enum Item GetForkFirstRevivableFossil(void);
void GetForkMirageTowerFossilSpecial(void);
void GetForkFossilRevivalSpeciesSpecial(void);
void GetForkFirstRevivableFossilSpecial(void);

#endif // GUARD_FORK_FOSSIL_RANDOMIZER_H
