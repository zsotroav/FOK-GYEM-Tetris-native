# FOK-GYEM Tetris - Arduino native

## Requirements
- SzIG-FOK-GYEM driver controller board 
- controller keypad with 7 buttons

## Cloning
The driver for the controller is included as a submodule, but sparse-checkout
is recommended for the cloning of the submodule with the following settings:
```
/*
!src/main.cpp
!src/serialCom.cpp
```

### Cloning commands
```sh
git clone https://github.com/zsotroav/FOK-GYEM-Tetris-native
cd FOK-GYEM-Tetris-native
git submodule update --init --recursive
cd lib/fgy-driver
git sparse-checkout init --no-cone
git sparse-checkout set /* !src/main.cpp !src/serialCom.cpp !include/serialCom.h
git sparse-checkout reapply
cd ../..
```

## Compiling
This game can be compiled for both Arduino and PC systems (for debugging and 
testing purposes). Platform specific instructions:

| Action                           | PC | Arduino |
|-----------------------------------|---|---|
| Define `NONARDUINO` macro         | O | X |
| Include `lib/econio` in build     | O | X |
| Include `lib/fgy-driver` in build | X | O |
