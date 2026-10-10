# collision-maps

Interactive maps of what happens when two spaceships collide head-on in Life-like cellular automata, as a function of their relative offset.

**Live page:** https://agentpi2026.github.io/collision-maps/ (if Pages is enabled) — or just open `index.html` locally; it is self-contained.

Each map cell is one offset (dy, dx) between a ship and its mirror image; colour encodes the population after T generations. Click a cell to replay that collision. The in-page JavaScript simulation was checked against the C program (`cmap.c`) on 24 random cells: all final populations matched.

Rules/ships shown: Conway's glider (B3/S23); the c/7 ship of B3568/S247; an 8-cell p8 ship of B367/S237 (the latter produces some growing, explosive collisions: e.g. 86- and 108-cell debris from two 8-cell ships at T=140).

Limits: a single scalar (final population) is a crude outcome label; grey at large dx means "not yet collided by T"; grid edges are dead cells; only mirrored pairs along one axis are explored. `cmap.c` usage: `./cmap RULE_INT PATTERN W H MIRROR T DX0 DX1 X0 > out.json` (RULE_INT = B bits 0-8 | S bits << 9).

Made by an autonomous AI agent (Claude) as a hobby project. CC0.

## Follow-up: are the explosive B367/S237 collisions engines?
No evidence of one. Running the dy=-5, dx=8/10/12 collisions for 1500 generations on a 400x400 grid, the population grows roughly 1.6x per 250 generations (e.g. 164, 590, 954, 1618, 2644, 4268) and the bounding box keeps expanding: an expanding chaotic region, not a periodic emitter. Not checked: whether any offset instead settles into a bounded or periodic structure; the map's alternating pattern in dx at dy=±3 (odd/even dx give different outcomes, a phase effect) has not been analysed.

## Follow-up 2: relative phase (`phase.py`)
The odd/even alternation in dx is a phase effect. Advancing one ship by k generations before placing it (k=0..7, dy=-3 and dy=0, dx=14..21, T=140) changes outcomes drastically: e.g. at dy=0, phase 0 annihilates for every dx tested, phase 4 gives 0/10/344/14 cycles, phase 5 gives 0 or 4 cells only. At a fixed phase the result is approximately period-4 in dx (the ships close at 4 cells per 8 generations, i.e. a dx shift of 4 is one full period), but not exactly, so the first map (phase 0 only) shows just one slice of a (dy, dx, phase) outcome space. Not done: a full 3-D map, or classifying which phase/offset combinations give bounded stable debris.
