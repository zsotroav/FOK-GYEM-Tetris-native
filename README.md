# FOK-GYEM Tetris - Arduino native
Multiplatform tetris clone for SZIG-FOK-GYEM controlles and other devices.

This project contains a considerable amount of platform specific code, part of
which are handled automatically via preprocessor statements, but most are split
into different files marked with suffixes. For more info see the
[compiling](#Compiling) section.

## Requirements
- SzIG-FOK-GYEM driver controller board 
- controller keypad with 7 buttons

OR

- Windows/Linux computer with a keyboard and terminal

## Cloning
The driver for the controller is included as a submodule, as such recursive
cloning is required for compiling for Arduino.

### Cloning commands
#### Without sparse checkout
```sh
git clone --recurse-submodules https://github.com/zsotroav/FOK-GYEM-Tetris-native
cd FOk-GYEM-Tetris-native
```

#### With sparse checkout
This is was previously required to avoid conflicting `setup` and `loop`
functions, but is no longer neccesary because of a new layout in 
[main.cpp](./src/main.cpp).

```sh
git clone https://github.com/zsotroav/FOK-GYEM-Tetris-native
cd FOK-GYEM-Tetris-native
git submodule update --init --recursive
cd lib/fgy-driver
git sparse-checkout init --no-cone
git sparse-checkout set /* !src/main.cpp
git sparse-checkout reapply
cd ../..
```

## Compiling
This game can be compiled for both Arduino and PC systems (mainly for debugging
and testing purposes). Platform specific instructions:

| Action                                   | PC | Arduino |
|------------------------------------------|----|---------|
| Define `NONARDUINO` macro                | X  | -       |
| Compile source files with pc suffix      | X  | -       |
| Compile source files with arduino suffix | -  | X       |
| Include `lib/econio` in build            | X  | -       |
| Include `lib/fgy-driver` in build        | -  | X       |

*Note: The `NONARDUINO` macro is planned to be removed to make the code 
completely modular and work based only on which files are compiled and linked.*

### Pre-made compiler settings
- For PC, use the proviced [CMakeLists](./CMakeLists.txt) file.
- For Arduino, usage of [PlatformIO](https://platformio.org/) with
[Visual Stuio Code](https://code.visualstudio.com) is recommended with the
[example pio ini](./platformio.ini.example) file.