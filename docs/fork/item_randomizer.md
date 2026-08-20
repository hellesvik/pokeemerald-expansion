# Fork Item Randomizer

This page documents the planned item randomizer behavior for this fork.
It is a rules/specification document only. It does not imply that the feature is already implemented in code.

## Goal

Randomize non-progression item rewards and pickups so that each new playthrough gets a different item spread, while preserving story access and keeping the item pool focused on useful battle and evolution rewards.

## Seed Behavior

The item randomizer should be seeded once at the start of a new game.

That means:
- each new save file gets its own randomized item layout
- the layout stays stable inside that save file
- reloading, saving, and revisiting a map should not reshuffle locations
- starting a fresh playthrough should produce a different spread

The randomization should be location-stable, not call-order-stable.
In practice, each eligible location should resolve from:
- the per-save randomizer seed
- a stable identifier for that location or scripted reward

This avoids desync if scripts run in a different order during play.

## Duplicate Policy

The planned randomizer does not allow duplicate drops.

That means:
- once an item has been assigned to one randomized source in a save, it should not be assigned again to another randomized source in that same save
- the item pool is consumed without replacement for the purpose of location assignment
- if there are more randomized sources than allowed-pool items, the implementation will need an explicit overflow rule before shipping

## Discovery Policy

The player should infer randomized items only by pickup.

That means:
- no spoiler log is assumed
- no up-front preview is assumed
- the game should not reveal the randomized result before the item is actually obtained or exposed by normal pickup behavior

## Sources That Should Be Randomized

The intended scope is:
- normal item balls
- hidden items
- non-progression scripted direct item rewards from NPCs or sidequest scripts

Hidden items and item-ball drops are handled the same way.
They draw from the same randomized pool and follow the same protection rules.

Scripted direct item rewards that should be randomized when they are not protected include:
- optional TM rewards from NPCs
- optional held-item rewards
- sidequest reward items such as `DeepSeaTooth` / `DeepSeaScale`
- direct gift rewards such as `Exp. Share` or `Amulet Coin`, if they are not on the protected-source list

More specifically, the intended scripted-reward scope includes one-time scripts that directly place an item into the bag through normal reward flow, such as:
- optional NPC gift items
- optional sidequest completion rewards
- one-time optional dialogue rewards
- optional reward exchanges that hand the player an item directly

## Sources That Should Not Be Randomized

The following should remain fixed:
- shops and marts
- berry patches / berry tree yields
- progression-required item sources
- all HM sources
- sidequest gate-item sources in the same category as `Basement Key`

Berry trees should remain fully vanilla.
Shop inventories should remain fully vanilla.

## Protected Sources

Protection should be source-based, not just item-based.
That means the implementation should maintain an explicit protected-source list for:
- progression-critical story rewards
- progression-critical map pickups
- HM gift locations
- HM item-ball locations
- sidequest gate-item rewards and placements

At minimum, the protected source set should include sources for:
- `Letter`
- `Devon Goods`
- `Meteorite`
- `Go Goggles`
- `Devon Scope`
- `Basement Key`
- `Magma Emblem`
- `Storage Key`
- `HM01` through `HM08`

This same protection rule should also be used for progression-adjacent fixed utilities if they function as access gates in practice.
For example, bike- or ferry-related access items should be reviewed source-by-source and protected if removing or randomizing them can strand story or sidequest progression.

The starter Poké Balls given immediately after the first rival battle should also remain fixed.
In Emerald, this means the specific gift source after the first battle with May/Brendan on Route 103:
- return to Professor Birch's Lab in Littleroot Town
- Professor Birch gives the player the Pokédex
- May/Brendan gives the player 5 Poké Balls

Only this early scripted 5-Poké-Ball gift is explicitly protected by this rule.
This is the Poké Ball source at `data/maps/LittlerootTown_ProfessorBirchsLab/scripts.inc` where May/Brendan gives `ITEM_POKE_BALL, 5` after the Route 103 rival battle.

## Items That Should Never Be Found From Randomized Locations

These should be removed from the randomized world pool entirely:
- consumables such as potions, balls, ethers, revives, repels, flutes, and similar utility stock
- vendor junk such as nuggets, stardust, pearls, mushrooms, and similar sell-value filler

Their original locations may still be randomized, but the replacements should come from the allowed pool rather than from those excluded categories.

## Allowed Replacement Pool

The replacement pool should include:
- all non-HM TMs
- held items
- Mega Stones
- form-change items
- species-lock items
- evolution items
- `Eviolite`

This means that species-specific or form-specific items are intentionally allowed.
For example, items in the spirit of `Metal Coat` are part of the intended pool.

## Feature Enablers

The item randomizer should assume the following enabler policy:
- the player should start the game with `ITEM_MEGA_RING` so that randomized `Mega Stones` are always usable
- `ITEM_TERA_ORB` is not part of the randomizer plan and should not be included in the pool
- `ITEM_DYNAMAX_BAND` is not part of the randomizer plan and should not be included in the pool

This means `Mega Stones` remain part of the allowed replacement pool, while tera- and dynamax-specific enabler items are explicitly outside the feature scope.

## Complete Planned Randomizer Pool

The following explicit lists define the full intended replacement pool.

### Mega Stones

ITEM_ABOMASITE, ITEM_ABSOLITE, ITEM_AERODACTYLITE, ITEM_AGGRONITE, ITEM_ALAKAZITE, ITEM_ALTARIANITE, ITEM_AMPHAROSITE, ITEM_AUDINITE, ITEM_BANETTITE, ITEM_BARBARACITE, ITEM_BAXCALIBRITE, ITEM_BEEDRILLITE, ITEM_BLASTOISINITE, ITEM_BLAZIKENITE, ITEM_CAMERUPTITE, ITEM_CHANDELURITE, ITEM_CHARIZARDITE_X, ITEM_CHARIZARDITE_Y, ITEM_CHESNAUGHTITE, ITEM_CHIMECHITE, ITEM_CLEFABLITE, ITEM_CRABOMINITE, ITEM_DARKRANITE, ITEM_DELPHOXITE, ITEM_DIANCITE, ITEM_DRAGALGITE, ITEM_DRAGONINITE, ITEM_DRAMPANITE, ITEM_EELEKTROSSITE, ITEM_EMBOARITE, ITEM_EXCADRITE, ITEM_FALINKSITE, ITEM_FERALIGITE, ITEM_FLOETTITE, ITEM_FROSLASSITE, ITEM_GALLADITE, ITEM_GARCHOMPITE, ITEM_GARDEVOIRITE, ITEM_GENGARITE, ITEM_GLALITITE, ITEM_GLIMMORANITE, ITEM_GOLISOPITE, ITEM_GOLURKITE, ITEM_GRENINJITE, ITEM_GYARADOSITE, ITEM_HAWLUCHANITE, ITEM_HEATRANITE, ITEM_HERACRONITE, ITEM_HOUNDOOMINITE, ITEM_KANGASKHANITE, ITEM_LATIASITE, ITEM_LATIOSITE, ITEM_LOPUNNITE, ITEM_LUCARIONITE, ITEM_MAGEARNITE, ITEM_MALAMARITE, ITEM_MANECTITE, ITEM_MAWILITE, ITEM_MEDICHAMITE, ITEM_MEGANIUMITE, ITEM_MEOWSTICITE, ITEM_METAGROSSITE, ITEM_MEWTWONITE_X, ITEM_MEWTWONITE_Y, ITEM_PIDGEOTITE, ITEM_PINSIRITE, ITEM_PYROARITE, ITEM_RAICHUNITE_X, ITEM_RAICHUNITE_Y, ITEM_SABLENITE, ITEM_SALAMENCITE, ITEM_SCEPTILITE, ITEM_SCIZORITE, ITEM_SCOLIPITE, ITEM_SCOVILLAINITE, ITEM_SCRAFTINITE, ITEM_SHARPEDONITE, ITEM_SKARMORITE, ITEM_SLOWBRONITE, ITEM_STARAPTITE, ITEM_STARMINITE, ITEM_STEELIXITE, ITEM_SWAMPERTITE, ITEM_TATSUGIRINITE, ITEM_TYRANITARITE, ITEM_VENUSAURITE, ITEM_VICTREEBELITE, ITEM_ZERAORITE, ITEM_ZYGARDITE

### Evolution Items

ITEM_ARMOR_FOSSIL, ITEM_AUSPICIOUS_ARMOR, ITEM_BLACK_AUGURITE, ITEM_CHIPPED_POT, ITEM_CLAW_FOSSIL, ITEM_COVER_FOSSIL, ITEM_CRACKED_POT, ITEM_DAWN_STONE, ITEM_DEEP_SEA_SCALE, ITEM_DEEP_SEA_TOOTH, ITEM_DOME_FOSSIL, ITEM_DRAGON_SCALE, ITEM_DUBIOUS_DISC, ITEM_DUSK_STONE, ITEM_ELECTIRIZER, ITEM_FIRE_STONE, ITEM_GALARICA_CUFF, ITEM_GALARICA_WREATH, ITEM_HELIX_FOSSIL, ITEM_ICE_STONE, ITEM_JAW_FOSSIL, ITEM_LEAF_STONE, ITEM_LINKING_CORD, ITEM_MAGMARIZER, ITEM_MALICIOUS_ARMOR, ITEM_METAL_COAT, ITEM_MOON_STONE, ITEM_OLD_AMBER, ITEM_OVAL_STONE, ITEM_PEAT_BLOCK, ITEM_PLUME_FOSSIL, ITEM_PRISM_SCALE, ITEM_PROTECTOR, ITEM_RAZOR_CLAW, ITEM_RAZOR_FANG, ITEM_REAPER_CLOTH, ITEM_ROOT_FOSSIL, ITEM_SACHET, ITEM_SAIL_FOSSIL, ITEM_SHINY_STONE, ITEM_SKULL_FOSSIL, ITEM_SUN_STONE, ITEM_SWEET_APPLE, ITEM_TART_APPLE, ITEM_THUNDER_STONE, ITEM_UPGRADE, ITEM_WATER_STONE, ITEM_WHIPPED_DREAM, ITEM_FOSSILIZED_BIRD, ITEM_FOSSILIZED_DINO, ITEM_FOSSILIZED_DRAKE, ITEM_FOSSILIZED_FISH

### Form and Species Items

The planned pool intentionally excludes `ITEM_TERA_ORB` and `ITEM_DYNAMAX_BAND`.

ITEM_ADAMANT_CRYSTAL, ITEM_ADAMANT_ORB, ITEM_BLUE_ORB, ITEM_BUG_MEMORY, ITEM_BURN_DRIVE, ITEM_CHILL_DRIVE, ITEM_CORNERSTONE_MASK, ITEM_DARK_MEMORY, ITEM_DNA_SPLICERS, ITEM_DOUSE_DRIVE, ITEM_DRACO_PLATE, ITEM_DRAGON_MEMORY, ITEM_DREAD_PLATE, ITEM_EARTH_PLATE, ITEM_ELECTRIC_MEMORY, ITEM_FAIRY_MEMORY, ITEM_FIGHTING_MEMORY, ITEM_FIRE_MEMORY, ITEM_FIST_PLATE, ITEM_FLAME_PLATE, ITEM_FLYING_MEMORY, ITEM_GHOST_MEMORY, ITEM_GRACIDEA, ITEM_GRASS_MEMORY, ITEM_GRISEOUS_CORE, ITEM_GRISEOUS_ORB, ITEM_GROUND_MEMORY, ITEM_HEARTHFLAME_MASK, ITEM_ICE_MEMORY, ITEM_ICICLE_PLATE, ITEM_INSECT_PLATE, ITEM_IRON_PLATE, ITEM_LUSTROUS_GLOBE, ITEM_LUSTROUS_ORB, ITEM_MEADOW_PLATE, ITEM_MIND_PLATE, ITEM_PINK_NECTAR, ITEM_PIXIE_PLATE, ITEM_POISON_MEMORY, ITEM_PRISON_BOTTLE, ITEM_PSYCHIC_MEMORY, ITEM_PURPLE_NECTAR, ITEM_RED_NECTAR, ITEM_RED_ORB, ITEM_REINS_OF_UNITY, ITEM_REVEAL_GLASS, ITEM_ROCK_MEMORY, ITEM_ROTOM_CATALOG, ITEM_RUSTED_SHIELD, ITEM_RUSTED_SWORD, ITEM_SHOCK_DRIVE, ITEM_SKY_PLATE, ITEM_SOUL_DEW, ITEM_SPLASH_PLATE, ITEM_SPOOKY_PLATE, ITEM_STEEL_MEMORY, ITEM_TOXIC_PLATE, ITEM_WATER_MEMORY, ITEM_WELLSPRING_MASK, ITEM_YELLOW_NECTAR, ITEM_ZAP_PLATE, ITEM_ZYGARDE_CUBE

### Held Items

ITEM_ABSORB_BULB, ITEM_ADRENALINE_ORB, ITEM_AIR_BALLOON, ITEM_AMULET_COIN, ITEM_ASSAULT_VEST, ITEM_BERSERK_GENE, ITEM_BIG_ROOT, ITEM_BINDING_BAND, ITEM_BLACK_BELT, ITEM_BLACK_SLUDGE, ITEM_BOOSTER_ENERGY, ITEM_BRIGHT_POWDER, ITEM_CELL_BATTERY, ITEM_CHARCOAL, ITEM_CHOICE_BAND, ITEM_CHOICE_SCARF, ITEM_CHOICE_SPECS, ITEM_CLEAR_AMULET, ITEM_COVERT_CLOAK, ITEM_DESTINY_KNOT, ITEM_DRAGON_FANG, ITEM_EJECT_BUTTON, ITEM_EJECT_PACK, ITEM_EVERSTONE, ITEM_EVIOLITE, ITEM_EXPERT_BELT, ITEM_FLAME_ORB, ITEM_FOCUS_BAND, ITEM_FOCUS_SASH, ITEM_FULL_INCENSE, ITEM_GRASSY_SEED, ITEM_GRIP_CLAW, ITEM_HEAVY_DUTY_BOOTS, ITEM_IRON_BALL, ITEM_KINGS_ROCK, ITEM_LAX_INCENSE, ITEM_LEFTOVERS, ITEM_LIFE_ORB, ITEM_LIGHT_BALL, ITEM_LOADED_DICE, ITEM_LUCK_INCENSE, ITEM_MAGNET, ITEM_MENTAL_HERB, ITEM_MIRACLE_SEED, ITEM_MIRROR_HERB, ITEM_MISTY_SEED, ITEM_MUSCLE_BAND, ITEM_MYSTIC_WATER, ITEM_NEVER_MELT_ICE, ITEM_ODD_INCENSE, ITEM_POISON_BARB, ITEM_POWER_HERB, ITEM_PROTECTIVE_PADS, ITEM_PSYCHIC_SEED, ITEM_PUNCHING_GLOVE, ITEM_PURE_INCENSE, ITEM_QUICK_CLAW, ITEM_RING_TARGET, ITEM_ROCKY_HELMET, ITEM_ROCK_INCENSE, ITEM_ROOM_SERVICE, ITEM_ROSE_INCENSE, ITEM_SAFETY_GOGGLES, ITEM_SCOPE_LENS, ITEM_SEA_INCENSE, ITEM_SHARP_BEAK, ITEM_SHELL_BELL, ITEM_SILK_SCARF, ITEM_SILVER_POWDER, ITEM_SOFT_SAND, ITEM_SOOTHE_BELL, ITEM_SPELL_TAG, ITEM_STICKY_BARB, ITEM_TERRAIN_EXTENDER, ITEM_THICK_CLUB, ITEM_THROAT_SPRAY, ITEM_TOXIC_ORB, ITEM_TWISTED_SPOON, ITEM_UTILITY_UMBRELLA, ITEM_WAVE_INCENSE, ITEM_WEAKNESS_POLICY, ITEM_WHITE_HERB, ITEM_WIDE_LENS, ITEM_WISE_GLASSES, ITEM_ZOOM_LENS

### TMs

ITEM_TM01, ITEM_TM02, ITEM_TM03, ITEM_TM04, ITEM_TM05, ITEM_TM06, ITEM_TM07, ITEM_TM08, ITEM_TM09, ITEM_TM10, ITEM_TM11, ITEM_TM12, ITEM_TM13, ITEM_TM14, ITEM_TM15, ITEM_TM16, ITEM_TM17, ITEM_TM18, ITEM_TM19, ITEM_TM20, ITEM_TM21, ITEM_TM22, ITEM_TM23, ITEM_TM24, ITEM_TM25, ITEM_TM26, ITEM_TM27, ITEM_TM28, ITEM_TM29, ITEM_TM30, ITEM_TM31, ITEM_TM32, ITEM_TM33, ITEM_TM34, ITEM_TM35, ITEM_TM36, ITEM_TM37, ITEM_TM38, ITEM_TM39, ITEM_TM40, ITEM_TM41, ITEM_TM42, ITEM_TM43, ITEM_TM44, ITEM_TM45, ITEM_TM46, ITEM_TM47, ITEM_TM48, ITEM_TM49, ITEM_TM50, ITEM_TM51, ITEM_TM52, ITEM_TM53, ITEM_TM54, ITEM_TM55, ITEM_TM56, ITEM_TM57, ITEM_TM58, ITEM_TM59, ITEM_TM60, ITEM_TM61, ITEM_TM62, ITEM_TM63, ITEM_TM64, ITEM_TM65, ITEM_TM66, ITEM_TM67, ITEM_TM68, ITEM_TM69, ITEM_TM70, ITEM_TM71, ITEM_TM72, ITEM_TM73, ITEM_TM74, ITEM_TM75, ITEM_TM76, ITEM_TM77, ITEM_TM78, ITEM_TM79, ITEM_TM80, ITEM_TM81, ITEM_TM82, ITEM_TM83, ITEM_TM84, ITEM_TM85, ITEM_TM86, ITEM_TM87, ITEM_TM88, ITEM_TM89, ITEM_TM90, ITEM_TM91, ITEM_TM92, ITEM_TM93, ITEM_TM94, ITEM_TM95, ITEM_TM96, ITEM_TM97, ITEM_TM98, ITEM_TM99, ITEM_TM100

## Protected Items

The protected list should include at least:
- progression-required story items
- all HMs
- `Basement Key`-style gate items used to unlock sidequest areas or scripted access checks

At minimum, the story-protected list currently discussed includes:
- `Letter`
- `Devon Goods`
- `Meteorite`
- `Go Goggles`
- `Devon Scope`
- `Basement Key`
- `Magma Emblem`
- `Storage Key`
- `HM01` through `HM08`

The final implementation should treat the protected list as explicit data, not as a heuristic.

## Design Intent

The design goal is not to produce a pure chaos randomizer.
It is meant to:
- preserve progression
- remove low-value pickup clutter
- replace filler with battle-relevant or evolution-relevant rewards
- create different pickup value curves across different saves

## Recommended Implementation Shape

The preferred implementation is dynamic per-save resolution, not compile-time shuffling.

That means:
- the original map/script locations stay the same
- eligible pickups and rewards are replaced at receive-time
- the result is derived from the save's seed plus the location/reward identity

This is preferable because it:
- keeps progression logic untouched for protected items and protected sources
- avoids touching berry trees and shop data
- avoids rebuilding all static map item definitions into a shuffled table
- makes the randomization stable within a save and different across playthroughs

## Current Status

As of August 20, 2026, this item randomizer is implemented in the fork as a per-save, receive-time randomizer for item balls, hidden items, and eligible scripted item rewards.

The implementation keeps protected items fixed, shares one replacement pool across randomized source types, and keeps assignments stable within a save while varying across playthroughs.
