*This project has been created as part of the 42 curriculum by raulsanc, mmorente.*

# cub3D

## Description

cub3D is a small first-person 3D maze explorer inspired by **Wolfenstein 3D** (id Software, 1992), the game that defined the FPS genre. The goal of the project is to learn and apply **ray-casting**: from a 2D grid map, the program casts one ray per screen column, finds the nearest wall with the DDA algorithm and draws a textured vertical stripe whose height depends on the distance to that wall. The result is a "realistic" 3D view rendered with the **MiniLibX** graphics library.

Main features:

- Parsing and validation of a `.cub` scene file (textures, colors and map).
- Different wall textures depending on the side the wall faces (North, South, East, West).
- Configurable floor and ceiling colors.
- Smooth movement with `W` `A` `S` `D` and camera rotation with the arrow keys.
- Wall collision using a small player hitbox.
- Clean exit with `ESC` or the window's red cross, with all memory freed.
- Any misconfiguration in the scene file prints `Error\n` followed by an explicit message and exits cleanly.

## Instructions

### Requirements

- Linux with X11 (`libx11-dev`, `libxext-dev`, `zlib1g-dev`)
- `cc` and `make`

MiniLibX and libft are included in `libs/` and are compiled automatically by the Makefile.

### Compilation

```sh
make        # builds libft, MiniLibX and the cub3D binary
make clean  # removes object files
make fclean # removes object files, libraries and the binary
make re     # full rebuild
```

### Execution

```sh
./cub3D src/maps/test.cub
```

### Controls

| Key            | Action                    |
| -------------- | ------------------------- |
| `W` / `S`      | Move forward / backward   |
| `A` / `D`      | Strafe left / right       |
| `←` / `→`      | Rotate the view           |
| `ESC`          | Quit                      |
| Red cross      | Quit                      |

### Scene file format (`.cub`)

```
NO ./src/game/assets/ne_texture.xpm
SO ./src/game/assets/so_texture.xpm
WE ./src/game/assets/we_texture.xpm
EA ./src/game/assets/se_texture.xpm

F 150,150,150
C 0,100,200

111111
100101
101001
1100N1
111111
```

- `NO`, `SO`, `WE`, `EA`: paths to the wall textures (`.xpm`).
- `F`, `C`: floor and ceiling colors in `R,G,B` format, each value in `[0,255]`.
- Elements can appear in any order and be separated by empty lines; the map must always be last.
- Map characters: `0` empty space, `1` wall, `N`/`S`/`E`/`W` player start position and orientation (exactly one), spaces are allowed.
- The map must be fully closed by walls.

## Resources

- [Lode's Computer Graphics Tutorial – Raycasting](https://lodev.org/cgtutor/raycasting.html)
- [Ray-Casting Tutorial for Game Development – F. Permadi](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
- [MiniLibX documentation (harm-smits)](https://harm-smits.github.io/42docs/libs/minilibx)
- [Digital Differential Analyzer (DDA) – Wikipedia](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm))
- [Play the original Wolfenstein 3D](http://users.atw.hu/wolf3d/)

### AI usage

AI tools were used as a support resource, never as a replacement for understanding the code:

- Explaining ray-casting and DDA concepts while studying the references above.
- Reviewing parts of the `.cub` parser and map validation to spot edge cases (unclosed maps, invalid colors, duplicated identifiers).
- Helping with debugging, memory leak hunting and writing this README.

All generated suggestions were reviewed, tested and discussed between both team members before being integrated.
