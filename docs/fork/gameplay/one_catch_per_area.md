# One Catch Per Area

This fork enforces one normal encounter per named area. Named areas use the region map section, not the raw map file, so shared places like the Safari Zone count as one area.

The first non-shiny wild encounter that is not covered by dupes clause spends the area's encounter when the battle ends, whether or not it is caught. Dupes are checked by evolutionary family across party, boxes, daycare, and caught Pokedex data, and they do not spend the area. Shiny encounters are always catchable and never blocked by a spent area.

Egg hatching also respects the area rule. If an egg is ready to hatch in an area that has already spent its encounter, the hatch is deferred until you enter an unused area.
