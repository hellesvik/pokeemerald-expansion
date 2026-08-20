# Fork Item Randomizer

This page documents the item randomizer currently implemented in this fork.

## Behavior

The randomizer is initialized once for each new save. Its seed is derived from the
game RNG, Trainer ID, and daily seed. Item assignments are stored in `SaveBlock3`,
so they remain stable after saving, reloading, and revisiting a source.

Each eligible source is assigned an item from one shared pool. The first 313
assigned sources receive unique pool items. Once the pool is exhausted, later
sources use a deterministic repeat based on their source ID.

Assignments are deterministic for a given save seed and source ID. They are not
precomputed into map data and are resolved when the reward is received.

## Randomized sources

The implementation handles these source types:

- Item balls, using their event-template ID as the source ID.
- Hidden items, using their hidden-item flag.
- Eligible direct scripted item rewards, using a source ID derived from the script
  address.

All three source types draw from the same pool. The implementation reserves 429
source IDs: item-ball IDs, hidden-item IDs, and 155 scripted-reward IDs.

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
- Item-ball source ID 26 when it contains Poké Balls.

Scripted rewards additionally remain vanilla for Poké Balls, progression and
utility items (including bicycles, rods, Scanner, Wailmer Pail, and Powder Jar),
and the explicitly listed berry rewards. The exact scripted exclusions are in
`ResolveForkRandomizedScriptItem` in `src/item_ball.c`.

Shops and berry-tree yields are not routed through the item-randomizer code.

## Replacement pool

The pool contains 313 items. It consists of:

- Mega Stones.
- Evolution items and fossils.
- Form- and species-specific items, such as Memories, Drives, Orbs, Masks, and
  Nectars.
- Battle held items.
- `ITEM_TM01` through `ITEM_TM50`.

The pool deliberately excludes all Plates and Incenses. It also excludes HMs,
Key Items, consumable medicine and ball items, vendor-value filler, Tera Orb,
and Dynamax Band.

`sForkRandomizedItemPool` in `src/item_ball.c` is the authoritative, explicit
item list. A compile-time assertion keeps the declared pool size synchronized
with that list.

## Save compatibility

The saved state has a randomizer version. When this version changes, the game
clears saved source assignments and pool-claim state while retaining the save's
seed. This safely regenerates the layout when the pool or assignment algorithm
changes. The current implementation version is 3.

## Implementation and tests

- `src/item_ball.c` resolves item-ball, hidden-item, and scripted rewards.
- `src/scrcmd.c` consumes item-ball and hidden-item one-use guards before
  ordinary scripted item randomization.
- `data/scripts/obtain_item.inc` clears that guard at the end of an item-ball
  pickup flow.
- `test/fork_item_randomizer.c` verifies stability, protections, uniqueness
  before overflow, valid TMs, item-ball message/bag agreement, and the absence
  of Plates and Incenses.
