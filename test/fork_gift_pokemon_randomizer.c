#include "global.h"
#include "pokemon.h"
#include "test/test.h"

enum Species GetForkRandomizedStarterSpecies(u8 slot);
enum Species GetForkRandomizedStevenGiftSpecies(void);

static bool8 IsPseudoLegendaryFirstStage(enum Species species)
{
    switch (species)
    {
    case SPECIES_DRATINI:
    case SPECIES_LARVITAR:
    case SPECIES_BAGON:
    case SPECIES_GIBLE:
    case SPECIES_DEINO:
    case SPECIES_GOOMY:
    case SPECIES_JANGMO_O:
    case SPECIES_DREEPY:
    case SPECIES_FRIGIBAX:
        return TRUE;
    default:
        return FALSE;
    }
}

static bool8 IsOfficialStarterSpecies(enum Species species)
{
    switch (species)
    {
    case SPECIES_BULBASAUR: case SPECIES_CHARMANDER: case SPECIES_SQUIRTLE:
    case SPECIES_CHIKORITA: case SPECIES_CYNDAQUIL: case SPECIES_TOTODILE:
    case SPECIES_TREECKO: case SPECIES_TORCHIC: case SPECIES_MUDKIP:
    case SPECIES_TURTWIG: case SPECIES_CHIMCHAR: case SPECIES_PIPLUP:
    case SPECIES_SNIVY: case SPECIES_TEPIG: case SPECIES_OSHAWOTT:
    case SPECIES_CHESPIN: case SPECIES_FENNEKIN: case SPECIES_FROAKIE:
    case SPECIES_ROWLET: case SPECIES_LITTEN: case SPECIES_POPPLIO:
    case SPECIES_GROOKEY: case SPECIES_SCORBUNNY: case SPECIES_SOBBLE:
    case SPECIES_SPRIGATITO: case SPECIES_FUECOCO: case SPECIES_QUAXLY:
        return TRUE;
    default:
        return FALSE;
    }
}

TEST("Fork starter choices use distinct Generation 3 Pokémon at or below 325 BST")
{
    enum Species starters[3];

    gSaveBlock3Ptr->forkItemRandomizerSeed = 0x12345678;
    for (u8 i = 0; i < ARRAY_COUNT(starters); i++)
    {
        starters[i] = GetForkRandomizedStarterSpecies(i);
        EXPECT_LE((u16)gSpeciesInfo[starters[i]].natDexNum, NATIONAL_DEX_DEOXYS);
        EXPECT_LE(GetSpeciesBaseStatTotal(starters[i]), 325);
    }
    EXPECT_NE(starters[0], starters[1]);
    EXPECT_NE(starters[0], starters[2]);
    EXPECT_NE(starters[1], starters[2]);
}

TEST("Fork starter randomizer can choose non-starter Pokémon")
{
    bool8 foundNonStarter = FALSE;

    for (u32 seed = 1; seed <= 32; seed++)
    {
        gSaveBlock3Ptr->forkItemRandomizerSeed = seed;
        for (u8 slot = 0; slot < 3; slot++)
            if (!IsOfficialStarterSpecies(GetForkRandomizedStarterSpecies(slot)))
                foundNonStarter = TRUE;
    }

    EXPECT(foundNonStarter);
}

TEST("Steven's gift is a Generation-compatible pseudo-legendary first stage")
{
    enum Species species;

    gSaveBlock3Ptr->forkItemRandomizerSeed = 0x87654321;
    species = GetForkRandomizedStevenGiftSpecies();

    EXPECT_LE((u16)gSpeciesInfo[species].natDexNum, NATIONAL_DEX_DEOXYS);
    EXPECT(IsPseudoLegendaryFirstStage(species));
}
