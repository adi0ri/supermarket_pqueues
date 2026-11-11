# Supermarket Checkout Simulation

A C++11 simulation of a supermarket with multiple checkers. A simulated clock drives customer arrivals, shopping, checkout, and checker breaks. The program writes a timestamped event log, final register balances, and total elapsed time.

## Build and run

On Linux or macOS with Make and a C++ compiler:

```sh
make
./sim 2 0 tests/t01.in checkout.log
```

On Windows with a C++ compiler available as `g++`:

```powershell
g++ -std=c++11 -Wall -pedantic sim.cpp cust.cpp pqueue.cpp -o sim.exe
.\sim.exe 2 0 tests/t01.in checkout.log
```

The arguments are the number of checkers, break duration in clock ticks, input path, and output path. Each input row contains a customer name without spaces, the role `shopper` or `robber`, an arrival tick starting at 1, and a positive item count.

The example runs with two checkers and no break. It ends at tick 75 with register balances of $69 and $286. See the [sample input](tests/t01.in) and [expected output](tests/t01.out).

## How the queues work

A linked-list priority queue orders arrivals by arrival tick and active shoppers by the time they finish shopping. A separate queue gives waiting customers a stable checkout order. Each checker tracks their own finish tick and cash balance. The fixtures under [tests](tests/) cover timestamped checkout logs and invalid command-line arguments.

Originally developed for CSCI 211.
