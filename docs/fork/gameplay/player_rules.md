# Player rules and quality-of-life items

## Battle items

When the setting is disabled, bag items cannot be used during trainer
battles. Healing items, revives, X-items, escape items, and balls are blocked
through the normal battle-item validation path without consuming the item.

## Infinite key items

When enabled, new games receive two reusable key items:

- **Infinite Rare Candy** raises a selected Pokémon one level at a time, but
  never above the current level cap.
- **Infinite Repel** toggles an effectively infinite repel state on or off and
  can be registered like other field-use key items.

Existing saves receive missing items when they are continued.

## EVs and IVs

With player EV gain disabled, player-owned Pokémon are normalized to 0 EVs.
This applies to new Pokémon and to party, box, and daycare Pokémon when an
older save is loaded. The summary screen exposes raw IV values directly.

See [New-Game Feature Options](../configuration/new_game_options.md) for the
available presets.
