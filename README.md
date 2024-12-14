# Emilye 
A Chess Engine Enhanced with Transposition Tables, Killer Heuristic, MVV-LVA, PST, Alpha-Beta Pruning, Quiescence Search.

## Strength
I haven't had a chance to test the chess engine's power using objective measures, but I believe the engine has a power ranging around 1400 to 1500 elo.

## How to use the engine
The Universal Chess Interface (UCI) is a standard protocol used to communicate with a chess engine, and is the recommended way to do so for typical graphical user interfaces (GUI) or chess tools. Emilye implements the majority of its options as described in the UCI protocol.

## Todo List
- Added a 3-move draw rule and fixed the checkmate error
- Bitboard
- UCI
- History Heuristic
- Null Move Prunning
- Open Book
- Late Move Eeduction
- Better Evaluation Function
  
## Acknowledgements
My chess engine would not have been possible without these helpful instructions:

Adam Berent helped me understand how alpha beta pruning and Quiescence search could be implemented:

https://adamberent.com/move-searchingandalphabeta/

https://adamberent.com/quiescencesearch-andextensions/

A book that helped me with moving order and UCI:

https://rustic-chess.org/

Articles on heuristic algorithms and optimization methods: 

https://homepage.iis.sinica.edu.tw/~tshsu/tcg/2017/slides/slide8.pdf

A repository of information about programming computers to play chess:

https://www.chessprogramming.org/Main_Page

The discussion helped me really understand how transposition tables work:

https://www.talkchess.com/forum3/viewtopic.php?t=76887&sid=eba71285510f2a6c8a8dddb683a928b2&start=20
