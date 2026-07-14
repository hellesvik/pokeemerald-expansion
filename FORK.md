# Fork Rules

This file summarizes the gameplay-specific behavior added in this fork on top of upstream `pokeemerald-expansion`.

## One Catch Per Area

This fork allows one normal wild encounter per named area.
Named areas are keyed by region map section, not by individual map file, so places like multi-room caves and the Safari Zone share one encounter slot when they share the same map section.

The first non-shiny encounter that is not blocked by dupes clause spends the area when the battle ends, whether or not that Pokemon is caught.
Gift Pokemon and in-game trades do not spend an area encounter.
Wally's catching tutorial is excluded from the rule.
Roamers still count as normal area encounters.

Dupes clause is checked by evolutionary family, not only by exact species.
Ownership checks include the player's active party, PC boxes, daycare, and caught Pokedex data.
If the encountered family is already owned, that encounter does not spend the area and cannot be caught.

Shiny wild Pokemon are always catchable, even if the area's normal encounter has already been spent.
If a wild encounter is not catchable, the fork blocks ball use before consuming the ball.
The same protection applies to Safari Balls.

Area encounter usage is persisted in save data as a named-area bitset.
Existing saves initialize that state lazily.

## Egg Hatch Interaction

Eggs still make normal hatch progress while walking.
If an egg would hatch in an area whose normal encounter has already been spent, the hatch is deferred and a warning message is shown instead.
The egg can hatch normally once the player enters a named area with an unused encounter.

## Soft Nuzlocke Whiteout Penalty

On a full whiteout, the fork picks one random non-egg Pokemon currently in the player's party.
That Pokemon is permanently marked as a soft-nuzlocke mon, immediately reduced to level 1, and has its stats recalculated.
Soft-nuzlocke mons are not allowed to level up again through battle EXP, daycare EXP, Rare Candy style leveling, or other normal level-up paths.
This penalty is added on top of the game's usual whiteout handling.

## Trainer Battle Item Ban

This fork does not allow bag items to be used during trainer battles.
That includes healing items, revives, X-items, escape items, and balls.
The rule is enforced through the normal in-battle bag validation path, so blocked items fail with the standard small item message instead of consuming the item or entering a special battle script flow.

## Level Caps

The fork uses a hard level cap tied to story progression.
The active cap is the first uncleared milestone in a fixed ladder defined in `src/caps.c`.
The very first Route 103 rival fight does not set a cap.

The ladder advances through required gym battles, story rival fights, villain boss fights, the Elite Four, and Champion Wallace.
The cap is removed after Steven is defeated.
Each milestone uses the highest level present on that story trainer's team.
Some later milestones can therefore have lower ace levels than earlier ones.

Pokemon at or above the current cap do not gain battle EXP.
Daycare EXP is also capped by the same limit.
Normal one-use Rare Candies are still allowed to push a Pokemon above the cap.
Already over-cap Pokemon are not reduced in level; they simply stop gaining normal levels until the cap rises or Steven is defeated.

## Infinite Key Items

The fork adds two reusable key items:

- `Infinite Rare Candy`
  Raises the selected Pokemon by one level at a time through the party menu, but never above the current level cap.

- `Infinite Repel`
  Applies an effectively infinite repel state until it is cleared or overwritten.
  Using Infinite Repel again while it is already active turns it off.
  It can also be registered like other field-use key items.

New games begin with both items.
Existing saves also receive them automatically on continue if they are missing.

## EV and IV Changes

Player-owned Pokemon are kept at 0 EVs.
They do not gain EVs from battle.
Newly obtained player-owned Pokemon are normalized to 0 EVs.
Older saves are scrubbed so player-owned Pokemon in party, boxes, and daycare also end up at 0 EVs after loading.

The summary screen exposes raw IV values directly.
This fork uses the existing summary-screen IV view rather than a fully custom page.

## Related Docs

- [docs/tutorials/one_catch_per_area.md](docs/tutorials/one_catch_per_area.md)
- [docs/tutorials/level_limits.md](docs/tutorials/level_limits.md)
- [ai-remake-summary.txt](ai-remake-summary.txt)
