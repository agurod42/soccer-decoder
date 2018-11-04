# soccer-decoder

C implementation of the algorithm specified in Alessandro Ferrarini's paper: [A new game theory algorithm simulates soccer matches: Reducing complexity to its irreducible essence](http://www.iaees.org/publications/journals/selforganizology/articles/2014-1(3-4)/a-new-game-theory-algorithm-simulates-soccer-matches.pdf).

## Build & Run

```
gcc -g -o main.o *.c && ./main.o
```

## Results

```
team a wons: 708
team b wons: 122
draws: 170
team a goals: 2280
team b goals: 864
scores:
   2- 0: 116
   6- 0: 7
   3- 4: 3
   ...
```
