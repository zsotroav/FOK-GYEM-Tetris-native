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
git sparse-checkout set /* !src/main.cpp !src/serialCom.cpp 
git sparse-checkout reapply
cd ../..
```