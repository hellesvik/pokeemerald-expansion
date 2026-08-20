#include "global.h"
#include "fork_encounter_randomizer.h"
#include "fork_gift_pokemon_randomizer.h"
#include "pokemon.h"
#include "random.h"

#define FORK_STARTER_CHOICE_COUNT 3

static const enum Species sPseudoLegendaryFirstStages[] =
{
    SPECIES_DRATINI, SPECIES_LARVITAR, SPECIES_BAGON,
    SPECIES_GIBLE, SPECIES_DEINO, SPECIES_GOOMY,
    SPECIES_JANGMO_O, SPECIES_DREEPY, SPECIES_FRIGIBAX,
};

static bool8 IsEligibleGiftSpecies(enum Species species)
{
    return IsSpeciesEnabled(species)
        && gSpeciesInfo[species].natDexNum <= GetForkMaxNationalDex();
}

static bool8 IsAlreadySelected(enum Species species, const enum Species *selected, u8 selectedCount)
{
    for (u8 i = 0; i < selectedCount; i++)
        if (selected[i] == species)
            return TRUE;
    return FALSE;
}

static bool8 IsEligibleStarterSpecies(enum Species species)
{
    return IsEligibleGiftSpecies(species)
        && species == GET_BASE_SPECIES_ID(species)
        && GetSpeciesBaseStatTotal(species) <= 325;
}

static enum Species SelectRandomStarterSpecies(u8 selection)
{
    enum Species selected[FORK_STARTER_CHOICE_COUNT];
    rng_value_t rng = LocalRandomSeed(gSaveBlock3Ptr->forkItemRandomizerSeed ^ 0x53544152);

    if (selection >= ARRAY_COUNT(selected))
        return SPECIES_TREECKO;

    for (u8 selectedCount = 0; selectedCount <= selection; selectedCount++)
    {
        u16 candidateCount = 0;
        u16 candidateIndex;

        selected[selectedCount] = SPECIES_TREECKO;
        for (enum Species species = SPECIES_BULBASAUR; species < NUM_SPECIES; species++)
            if (IsEligibleStarterSpecies(species) && !IsAlreadySelected(species, selected, selectedCount))
                candidateCount++;

        if (candidateCount == 0)
            continue;
        candidateIndex = LocalRandom(&rng) % candidateCount;

        for (enum Species species = SPECIES_BULBASAUR; species < NUM_SPECIES; species++)
        {
            if (!IsEligibleStarterSpecies(species) || IsAlreadySelected(species, selected, selectedCount))
                continue;
            if (candidateIndex-- == 0)
            {
                selected[selectedCount] = species;
                break;
            }
        }
    }

    return selected[selection];
}

static enum Species SelectRandomGiftSpecies(const enum Species *candidates, u16 candidateCount, u32 salt, u8 selection, enum Species fallback)
{
    enum Species selected[FORK_STARTER_CHOICE_COUNT];
    rng_value_t rng = LocalRandomSeed(gSaveBlock3Ptr->forkItemRandomizerSeed ^ salt);

    if (selection >= ARRAY_COUNT(selected))
        return fallback;

    for (u8 selectedCount = 0; selectedCount <= selection; selectedCount++)
    {
        u16 start = LocalRandom(&rng) % candidateCount;

        selected[selectedCount] = fallback;

        for (u16 i = 0; i < candidateCount; i++)
        {
            enum Species species = candidates[(start + i) % candidateCount];

            if (IsEligibleGiftSpecies(species) && !IsAlreadySelected(species, selected, selectedCount))
            {
                selected[selectedCount] = species;
                break;
            }
        }
    }

    return selected[selection];
}

enum Species GetForkRandomizedStarterSpecies(u8 slot)
{
    return SelectRandomStarterSpecies(slot);
}

enum Species GetForkRandomizedStevenGiftSpecies(void)
{
    return SelectRandomGiftSpecies(sPseudoLegendaryFirstStages, ARRAY_COUNT(sPseudoLegendaryFirstStages), 0x53544556, 0, SPECIES_BELDUM);
}
