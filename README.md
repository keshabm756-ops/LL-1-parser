# LL(1) Predictive Parser Generator

An interactive web version of the Compiler Design LL(1) project. Enter a grammar and the page computes:

- FIRST and FOLLOW sets
- The LL(1) parsing table (conflicts are highlighted)
- A step-by-step predictive parse of any input string

## Grammar format

- One character per symbol
- `=` separates the left and right sides, `|` separates alternatives
- `#` is epsilon, `$` is the end marker
- The left side of the first line is the start symbol

Example:

```
E=TQ
Q=+TQ|#
T=FR
R=*FR|#
F=(E)|i
```

## Run it

Open `index.html` in any browser. No build step or dependencies.

## Original C version

The command-line version (`main.c`, `grammar.c`, `first_follow.c`, `parse_table.c`, `predictive_parser.c`) can live alongside this page in the same repository.
