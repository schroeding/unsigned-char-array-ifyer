# unsigned-char-array-ifyer

A simple helper tool for transforming any binary file to a C-style unsigned char array.
Output can be printed to STDOUT or (with the -o flag) to a file that can be included in any C/C++ project.
Use it in your compiler toolchain to statically include binary data at build time.

## Building & Installation
For Linux

```bash
make && make install
```

For Windows (manual installation required)

```bash
make windows
```

## Usage

```bash
uca <input filename> [<name of array>] [-o <output filename>]
```

## License

[The Unlicense](https://choosealicense.com/licenses/unlicense/)