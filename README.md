# cub3D

A first-person maze project in C with MiniLibX, in the style of Wolfenstein 3D. The raycasting renderer is built in and draws the textured 3D view (see Status).

## Status

The code in this repository does these things today:

- Parses and validates a `.cub` scene file.
- Opens a 800x600 MiniLibX window and loads the four wall textures.
- Renders the textured 3D view every frame (DDA raycaster), with floor and ceiling colours.
- Moves and rotates the player on the map, with a toggleable minimap drawn on top.

The raycasting renderer (`dda.c`, `render.c`, `render_utils.c`) is part of the build and `update_game` calls `render_frame` each frame. Verified on macOS arm64: the window opens, walls are textured with the right face for each direction, and the minimap (`Tab`) draws over the 3D view. Not retested: wall collision and other movement behaviour. The Makefile has no header dependencies, so run `make re` after changing a header.

## What it does

- Reads a `.cub` file: texture paths for `NO`, `SO`, `WE`, `EA` (`.xpm`), floor and ceiling colours as `F r,g,b` and `C r,g,b`, then the map made of `0`, `1`, spaces and one player letter (`N`, `S`, `E`, `W`).
- Validates the scene: file type, missing or duplicate texture and colour lines, invalid RGB values, exactly one player, and a map that must be closed (checked with a flood fill). Errors are printed as `Error: ...`.
- Controls: `W`/`S` or Up/Down to move, `A`/`D` to strafe, Left/Right to rotate, `Tab` to show the minimap, `P` to reset the player, `1`-`4` to change movement speed, `Esc` to quit. Key codes are the macOS ones.
- Includes sample maps in `maps/good/` and deliberately broken ones in `maps/bad/`.

## Build and run

```
make          # builds ./cub3D
make run      # builds and runs ./cub3D a.cub
make clean    # removes objects (libft, get_next_line)
make fclean   # removes objects and the binary
make re       # fclean + all
```

Example:

```
./cub3D maps/good/subject_map.cub
./cub3D maps/bad/player_none.cub     # prints "Error: Wrong Player Count"
```

On first run the Makefile clones `https://github.com/BahaBerkPancar/Libft-42.git` into `libft/` (needs network access). It builds the bundled `minilibx_opengl_20191021` (macOS OpenGL version of MiniLibX), so the Makefile links `-framework OpenGL -framework AppKit` and targets macOS.

## How it works

The renderer uses DDA raycasting. For each screen column the code builds a ray direction from the player direction and a 60 degree field of view. It then steps the ray from one grid line to the next (`side_dist_x` / `side_dist_y`, advanced by `delta_dist_x` / `delta_dist_y`) until it enters a wall cell (`'1'`). The wall side that was hit selects the north, south, east or west texture. The perpendicular distance gives the wall height on screen (`win_height / distance`), and the fractional hit position on the wall gives the texture column. Ceiling and floor colours fill the rest of the column.

The scene loading works in stages: `read_header.c` and `rgbs.c` parse textures and colours, `map_handle/` reads the map and flood-fills it, `checks/` validates the results, and `mlx_files/` plus `player/` run the window and input.

## Project structure

- `main.c`, `read_header.c`, `rgbs.c`: entry point and scene header parsing
- `map_handle/`, `checks/`: map reading and validation
- `mlx_files/`: window, key handling, minimap
- `player/`: movement and rotation
- `utils/`: printing, freeing and helpers
- `dda.c`, `render.c`, `render_utils.c`: the raycasting renderer
- `get_next_line/`: bundled get_next_line
- `minilibx_opengl_20191021/`: bundled MiniLibX for macOS
- `maps/`, `textures/`: sample scenes and texture sets (Wolfenstein 3D textures and a Minecraft-style pack, see the README in each texture folder for credits)

This is a 42 İstanbul project.
