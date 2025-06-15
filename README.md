# Runoff Voting System

This C program implements a **ranked-choice voting system**, also known as a **runoff voting algorithm**

In a runoff election, voters rank candidates in order of preference. The election continues in rounds until one candidate has a majority (>50%) of votes, or a tie is declared.

---

## 📋 How It Works

1. **Input**:
   - Candidate names are passed via command-line arguments.
   - The user is prompted to enter the number of voters.
   - Each voter ranks the candidates by preference.

2. **Vote Recording**:
   - Voter preferences are stored in a 2D array: `preferences[i][j]`
     - `i` = voter index
     - `j` = rank (e.g. 0 = 1st choice)
   - Each preference is validated and recorded with `vote()`.

3. **Tabulation**:
   - In each round, votes are counted for each voter's highest-ranked non-eliminated candidate.

4. **Elimination**:
   - If no candidate has a majority:
     - The candidate(s) with the fewest votes are eliminated.
     - Their votes are redistributed to the next preferred non-eliminated candidate.

5. **End Conditions**:
   - A candidate with >50% wins.
   - If all remaining candidates are tied, the election ends in a tie.

---

## 📃 Instructions
https://cs50.harvard.edu/x/2025/psets/3/runoff/

---

## 📁 File Overview

```c
preferences[MAX_VOTERS][MAX_CANDIDATES]; // stores ranked votes
candidate { string name; int votes; bool eliminated; } // candidate struct

vote()        // Records a voter's preference if valid
tabulate()    // Counts votes for non-eliminated candidates
print_winner()// Checks if any candidate has >50%
find_min()    // Finds the fewest number of votes
is_tie()      // Checks for a tie between remaining candidates
eliminate()   // Eliminates candidate(s) with the fewest votes
```

---

## ⚙️ How to compile
clang -o runoff runoff.c -lcs50
./runoff Alice Bob Charlie
