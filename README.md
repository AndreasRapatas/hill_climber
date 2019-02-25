# Hill Climber with SFML
Hill Climbing Algorithm on images with SFML in C++


# Usage
```bash
$ hill_climber "../path/to/image.png"
```
- Left: Original
- Right: Approximation after 30min

![Preview](https://i.imgur.com/6M5fycb.png "Rubik's")

# Installation
## Dependencies
This project uses [SFML (Simple & Fast Multimedia Library)](https://www.sfml-dev.org/index.php). Follow SFML's documentation to install it.

For Ubuntu simply ```apt install libsfml-dev```

## hill_climber
```bash
git clone https://github.com/Rapatas/hill_climber
mkdir -p hill_climber/build
cd hill_climber/build
cmake ..
make install # As root
```
