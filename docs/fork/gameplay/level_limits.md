# Fork Level Limits

This fork uses the built-in hard level cap system.

## Current Behavior

- Battle EXP is blocked once a Pokemon is at or above the current cap.
- Daycare EXP is capped by the same limit.
- Normal one-use Rare Candies are still allowed to push a Pokemon above the cap.
- EV gain is disabled separately through the EV cap configuration.

## Current Cap Ladder

The active cap is chosen from the first uncleared story battle milestone in `src/caps.c`. Rival variants share the same milestone, and boss fights use the highest level present in that battle.

The ladder currently starts at the Route 103 rival battle, advances through every required rival, gym, villain boss, Elite Four, and Champion fight, then removes the cap after postgame Steven.

Because the rule is tied to each story battle's actual ace level, some later battles can set a lower cap than the previous milestone. Overleveled Pokemon are not reduced in level; they just stop gaining EXP until the active cap rises again or Steven is cleared.
