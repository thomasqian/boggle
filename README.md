# Boggle
U C S D C S E 1 0 0 Assignment, skeleton code was provided by authors listed in files.

Implemented the back-end functionality of boggle, which is mainly focused on finding all legal words 
as defined in the lexicon, boglex.txt. My implementation uses a multiway trie for speed when finding
words, and includes some optimization regarding skipping sequences that aren't prefixes.

To create a simple n x n boggle solver, useful for cheating at games such as Ruzzle, execute:  
```
make boggle n
```
##### Note that only a board size of 4 is currently supported.

The resulting executable does not perform user input checks, and simply takes 4 letters, separated
by spaces, at each newline. After 4 lines, the program spits out all found words.

An optional user interface is also included so that a human player can compete against the computer,
but this requires using qMake for compilation.
