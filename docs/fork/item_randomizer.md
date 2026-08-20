# Fork Item Randomizer

This page documents the item randomizer currently implemented in this fork.

## Behavior

The randomizer is initialized once for each new save. Its seed is derived from the
game RNG, Trainer ID, and daily seed. Item assignments are stored in `SaveBlock3`,
so they remain stable after saving, reloading, and revisiting a source.

Each eligible visible item ball is assigned an item from one shared pool. The
pool contains 393 candidates, and replacements are unique until that pool is
exhausted. Any later visible item-ball sources retain their original item.

Assignments are deterministic for a given save seed and source ID. They are not
precomputed into map data and are resolved when the reward is received.

## Randomized sources

The implementation handles these source types:

- Visible item balls draw from the main pool. Their unique item-ball flags are
  used as source IDs, so pickups on different maps cannot collide.
- Hidden items draw independently from a separate repeatable pool.
- Direct scripted item rewards remain vanilla.

For item balls and hidden items, the item shown in the pickup message is the
exact item added to the bag. A one-use guard prevents the ordinary `additem`
script command from randomizing that same pickup a second time.

## Protected rewards

The following are never randomized:

- `ITEM_NONE`.
- All HMs (`ITEM_HM01` through `ITEM_HM08`).
- Any item in the Key Items pocket.
- `ITEM_LETTER`, `ITEM_DEVON_GOODS`, `ITEM_METEORITE`, `ITEM_GO_GOGGLES`,
  `ITEM_DEVON_SCOPE`, `ITEM_BASEMENT_KEY`, `ITEM_MAGMA_EMBLEM`, and
  `ITEM_STORAGE_KEY`.

All direct scripted rewards remain vanilla, including item gifts and progression
rewards.

Shops and berry-tree yields are not routed through the item-randomizer code,
with one deliberate exception: Mauville Game Corner's prize counter offers
items from the randomizer pool.

## Mauville Game Corner catalog

The Mauville Game Corner has five randomized prize entries, each costing 4,000
coins. The catalog is generated the first time it is needed and then saved, so
the same five named items are shown on every later visit. Each catalog item is
reserved from the main item pool when the catalog is generated; it therefore
cannot also be assigned to a visible item ball. Prizes remain repeatable
purchases, allowing the player to decide which, if any, of the offered items to
buy.

## Replacement pool

The pool contains 393 items. It consists of:

- Mega Stones.
- Evolution items and fossils.
- Form- and species-specific items, such as Memories, Drives, Orbs, Masks, and
  Nectars.
- Battle held items.
- `ITEM_TM01` through `ITEM_TM130`.

The pool deliberately excludes all Plates and Incenses. It also excludes HMs,
Key Items, consumable medicine and ball items, vendor-value filler, Tera Orb,
and Dynamax Band.

## Hidden-item pool

Hidden items are deterministic per hidden-item flag, but draw with replacement
from a separate pool. They may repeat and contain ordinary Poké Balls (excluding
Master Balls) or money-giving treasures such as Nuggets, Pearls, Stardust, and
Mushrooms. Protected progression and Key Item hidden pickups remain vanilla.

`sForkRandomizedItemPool` in `src/item_ball.c` is the authoritative, explicit
item list. A compile-time assertion keeps the declared pool size synchronized
with that list.

## Save compatibility

The saved state has a randomizer version. When this version changes, the game
clears saved source assignments, pool claims, and the Game Corner catalog while
retaining the save's seed. This safely regenerates the layout when the pool or
assignment algorithm changes. The current implementation version is 7.

## Implementation and tests

- `src/item_ball.c` resolves item-ball, hidden-item, and scripted rewards.
- `data/maps/MauvilleCity_GameCorner/scripts.inc` displays and sells the saved
  randomized Game Corner catalog.
- `src/scrcmd.c` consumes item-ball and hidden-item one-use guards before
  ordinary scripted item randomization.
- `data/scripts/obtain_item.inc` clears that guard at the end of an item-ball
  pickup flow.
- `test/fork_item_randomizer.c` verifies stability, protections, uniqueness
  before overflow, valid TMs, item-ball message/bag agreement, Game Corner
  reservations, and the absence of Plates and Incenses.
