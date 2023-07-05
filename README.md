## About The Project
Unscrambler is a command line tool that unshuffles a shuffled word among other things.

![Language](https://img.shields.io/badge/Language-C%2B%2B%0A-success.svg)
[![CodeFactor](https://www.codefactor.io/repository/github/pvzzombs/unscrambler/badge)](https://www.codefactor.io/repository/github/pvzzombs/unscrambler)
[![CircleCI](https://dl.circleci.com/status-badge/img/gh/pvzzombs/unscrambler/tree/main.svg?style=svg)](https://dl.circleci.com/status-badge/redirect/gh/pvzzombs/unscrambler/tree/main)
[![Build status](https://ci.appveyor.com/api/projects/status/89l84c8uaj9ei7q3?svg=true)](https://ci.appveyor.com/project/pvzzombs/unscrambler)

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
unscrambler <options> <word> [-L <language>]
```
### Usage
```
Unscrambler -u srtekri
Unscrambler -u putnagnai -L Filipino
```
### Options
```
-h, --help             Show help text
-u, --unscramble       Unscramble the input word into an actual word
-c, --complete         Complete the unfinished input word into an actual word
-s, --substring        Give words that make up the input word
-L, --Language         Set language
--set-config-path      Set where to look for the config file
--set-dictionary-path  Set the path where unscrambler will look for dictionaries
--set-default-language Set the default language
```
### Supported Languages
* English
* Filipino
### Configuration Options
* DictionaryPath
* DefaultLanguage





