# ASCIIart

You need to install raylib library at https://github.com/raysan5/raylib from releases and put inside "raylib" folder.
```
(example tree)
ASCIIart
├── CMakeLists.txt
├── main.cpp
├── raylib
│   ├── CHANGELOG
│   ├── include
│   │   ├── raylib.h
│   │   ├── raymath.h
│   │   └── rlgl.h
│   ├── lib
│   │   ├── libraylib.a
│   │   ├── libraylib.so -> libraylib.so.500
│   │   ├── libraylib.so.5.0.0
│   │   └── libraylib.so.500 -> libraylib.so.5.0.0
│   ├── LICENSE
│   └── README.md
├── README.md
└── test.png
```

## Building
```bash
cmake -B build .
cmake --build build/
./build/ASCIIart
```

## Running 
* `./build/ASCIIart --file (file path)` using png photo as a input image
* `./build/ASCIIart --core (number)` number of threads to use (default - number of threads in cpu)
* `./build/ASCIIart --test (number)` number of tests in one run (default - 10)
* `./build/ASCIIart --size (number) (number)` width and height of proccesed image (cannot be used with --file)
* `./build/ASCIIart --output (file name)` name of the file to save generated ASCII art