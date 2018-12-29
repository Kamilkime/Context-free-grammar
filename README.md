# Context-free-grammar
Context-free grammar loader, word generator and word checker

## Purpose
The grammar program was created as a part of **Informatics Basics** laboratories (Warsaw University of Technology, Electrical Faculty, Applied Computer Science, semester I)

## Building
`make clean`

## Usage
`./contextFree`

## Grammar syntax
`{T},{N},{R},S`
* **T** - Terminal symbols, e.g. `a,b`
* **N** - Non-terminal symbols, e.g. `S`
* **R** - Grammar rules, e.g. `S -> aSa|bSb|a|b|E`
* **S** - Start symbol, e.g. `S`

`E` is a reserved symbol - used as an empty word

Example syntaxes:
* `{a,b,c},{S,T},{S -> aSb|aTb|E, T -> cTc|c},S`
* `{a,b},{S},{S -> aSa|bSb|a|b|E},S`
* `{a,b},{S},{S -> aSaSa|b|E},S`

## Example
An example file, to be used as a grammar file, can be found in `test/testGrammar`

## License
The analyser is licensed under **MIT License** - https://choosealicense.com/licenses/mit/
