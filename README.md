## About The Project
Unscrambler is a command line tool that unshuffles a shuffled word among other things.

![Language](https://img.shields.io/badge/Language-C%2B%2B%0A-success.svg)
[![CodeFactor](https://www.codefactor.io/repository/github/pvzzombs/unscrambler/badge)](https://www.codefactor.io/repository/github/pvzzombs/unscrambler)
[![CircleCI](https://dl.circleci.com/status-badge/img/gh/pvzzombs/unscrambler/tree/main.svg?style=svg)](https://dl.circleci.com/status-badge/redirect/gh/pvzzombs/unscrambler/tree/main)

## Building  

### Instructions: 
1. Clone this repo using git
```
git clone https://github.com/pvzzombs/unscrambler.git
cd unscrambler
```
2. Configure and build using cmake
```
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DLINK_STATIC=0
cmake --build .
```
3. Done!

## How To Use
### Format
```
Unscrambler <OPTIONS> <WORD>
Unscrambler -L <LANGUAGE> <OPTION> <WORD>
```
### Usage
```
Unscrambler -u srtekri
Unscrambler -L Filipino -u putnagnai
```
### Options
```
-h, --help             Show help text
-u, --unscramble       Unscramble the input word into an actual word
-c, --complete         Complete the unfinished input word into an actual word
-s, --substring        Give words that make up the input word
```
### Language
```
-L, --Language         Specify language
```
### Supported Languages
* English
* Filipino





