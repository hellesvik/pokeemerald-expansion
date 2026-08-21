#include "global.h"
#include "fork_gift_pokemon_randomizer.h"
#include "pokemon.h"
#include "test/test.h"

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

TEST("Fork starter receives at least two perfect IVs")
{
    struct Pokemon mon;
    u8 perfectIvs = 0;

    gSaveBlock3Ptr->forkItemRandomizerSeed = 0x13572468;
    CreateMon(&mon, SPECIES_TREECKO, 5, 0, OTID_STRUCT_PRESET(0));
    ApplyForkStarterPerfectIvs(&mon, 0);

    for (u8 stat = 0; stat < NUM_STATS; stat++)
        if (GetMonData(&mon, MON_DATA_HP_IV + stat) == MAX_PER_STAT_IVS)
            perfectIvs++;
    EXPECT_GE(perfectIvs, 2);
}

TEST("Fork starter's other IVs can also roll perfect")
{
    struct Pokemon mon;
    bool8 foundExtraPerfectIv = FALSE;

    for (u32 seed = 1; seed <= 128; seed++)
    {
        u8 perfectIvs = 0;

        gSaveBlock3Ptr->forkItemRandomizerSeed = seed;
        CreateMon(&mon, SPECIES_TREECKO, 5, 0, OTID_STRUCT_PRESET(0));
        ApplyForkStarterPerfectIvs(&mon, 0);
        for (u8 stat = 0; stat < NUM_STATS; stat++)
            if (GetMonData(&mon, MON_DATA_HP_IV + stat) == MAX_PER_STAT_IVS)
                perfectIvs++;
        if (perfectIvs > 2)
            foundExtraPerfectIv = TRUE;
    }

    EXPECT(foundExtraPerfectIv);
}

TEST("Fork starter perfect IV stats vary between saves")
{
    struct Pokemon mon;
    u8 firstPair = 0;
    bool8 foundDifferentPair = FALSE;

    for (u32 seed = 1; seed <= 32; seed++)
    {
        u8 pair = 0;

        gSaveBlock3Ptr->forkItemRandomizerSeed = seed;
        CreateMon(&mon, SPECIES_TREECKO, 5, 0, OTID_STRUCT_PRESET(0));
        ApplyForkStarterPerfectIvs(&mon, 0);
        for (u8 stat = 0; stat < NUM_STATS; stat++)
            if (GetMonData(&mon, MON_DATA_HP_IV + stat) == MAX_PER_STAT_IVS)
                pair |= 1 << stat;
        if (seed == 1)
            firstPair = pair;
        else if (pair != firstPair)
            foundDifferentPair = TRUE;
    }

    EXPECT(foundDifferentPair);
}
