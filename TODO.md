#TODO

While the program is nowhere near complete, I will be trying to keep track of my todos through this file. 

##Optimization Passes
* Lazy Moves: Moves wouldn't be evaluated until they absolutly had to, all other operations would operate with an offset. e.g. ```++++>>>+++>[-]``` would be ADD, ADD, MV, CLEAR
* Dead Code Removal: Removes all dead loops, either because they would never be reached because it's inherant ```[...code...][this wouldn't run]``` (or a loop at the beginning of the program) or if the compiler already knows that it starts on a 0 due to Compile Time Evaluation.
* Infinite Loop Removal: Any loop which doesn't effect the starting cell at all should be a compiler error for an infinite loop. Any loop which effects the starting cell by a even number will fail if the starting cell is an infinite loop. This should be an error at runtime, with a warning at compile time
* Clear loops: ```[-]```, ```[+++]```, etc. They all automaticly clear the current cell, with the caviat of ```[--]```. This (or any other loop with an even amount of minuses), if called on a cell with a odd value, would cause an infinite loop, and throw a runtime error. This should warn if compiled.
* Multiplication loops: ```[->+++++>++<<]``` or ```[--->++++>++<<]```. Translate to a multiplication with an optional devision. The amount of minuses on the starting cell is the divisor. If divisor is even, could cause infinite loop, see writeup on clear loops.
* Compile Time Evaluation: A multi-pass optimzation that allows cells to be set at the beginning of a program, releaving stress on run-time. Time that is no longer spent setting things up. This is a multiple pass job, as the influence of any input has to be tracked across the data (and instruction) array. All instructions before an input can be evaluated without second thought. Loops that don't touch a input-influenced cell can be evaluated in full.
* Threading: This is honestly the holy-grail of brainnfuck optimizations in terms of detectability, though I'm not sure how much benefit it would have. The ability to detect that two loops are completly independant, and evaluate them concurently. This will probably never happen ever.

##Front Ends
These will be supported in both input and output. They are directly equivalent to brainf*ck These can be lexed with simple translators.

* [ASCII art](https://esolangs.org/wiki/ASCII_art) Normal brainfuck, but with the symbols as ascii art
* [Blub](https://esolangs.org/wiki/Blub) Fishy brainfuck
* [Braincrash](https://esolangs.org/wiki/Braincrash) Brainfuck with one symbol thanks to a command pointer
* [CompressedFuck](https://esolangs.org/wiki/CompressedFuck)
* [F\*ckF\*ck](https://esolangs.org/wiki/Fuckfuck) Brainfuck with explicit words as symbols
* [GERMAN](https://esolangs.org/wiki/GERMAN) SUBTRAKTION
* [Integral](https://esolangs.org/wiki/Integral) Coefficients of the integral of the program
* [Omam](https://esolangs.org/wiki/Omam) Via indie folk band "Of Monsters and Men"
* [Ook!](https://esolangs.org/wiki/Ook!) Ook! Ook!
* [Pi](https://esolangs.org/wiki/Pi) Commands stored in errors in pi
* [ReverseFuck](https://esolangs.org/wiki/ReverseFuck) All Brainfuck commands are swapped
* [Roadrunner](https://esolangs.org/wiki/Roadrunner) MeeP
* [Tic Tac Toe](https://esolangs.org/wiki/Tic_Tac_Toe) Play a game of tic tac toe to program
* [Unibrane](https://esolangs.org/wiki/Unibrain) 
* [VerboseFuck](https://esolangs.org/wiki/VerboseFuck) Really unnecessarily verbose

##Variations that need ast/optimizer support
* [Brainfork](https://esolangs.org/wiki/Brainfork) Needs support for forking (either simultaneously using multi-threading or sequentially with a stack).
* [Boolfuck](https://esolangs.org/wiki/Boolfuck) Needs custom i/o and binary support
* [Derpcode](https://esolangs.org/wiki/Derpcode) Needs binary support
* [COW](https://esolangs.org/wiki/COW) Needs a register/stack and additional control characters
* [DNA#](https://esolangs.org/wiki/DNA-Sharp) Needs a second pointer
* [TinyBF](https://esolangs.org/wiki/TinyBF) Needs direction variable

##Target languages
These are all of the languages that bfcc will compile to

* [C](https://en.wikipedia.org/wiki/C_(programming_language))
* [Go](https://en.wikipedia.org/wiki/Go_(programming_language))
* [Java](https://en.wikipedia.org/wiki/Java_(programming_language))
* [Python](https://en.wikipedia.org/wiki/Python_(programming_language))
* Support for most of the brainfuck variants above (no promises)
