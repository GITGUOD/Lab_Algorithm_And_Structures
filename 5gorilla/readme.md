# Result
```
admins@sandbox:~/Desktop/Algoritm_lab/5gorilla$ g++ -std=c++11 -g -o main main.cpp 
admins@sandbox:~/Desktop/Algoritm_lab/5gorilla$ time ./check_solution.sh ./main
data/sample/1.in
Checking solution...
Correct!
data/secret/0mini.in
Checking solution...
Correct!
data/secret/1small.in
Checking solution...
Correct!
data/secret/2med.in
Checking solution...
Correct!
data/secret/3large.in
Checking solution...
Correct!
data/secret/4huge.in
Checking solution...
Correct!

real	0m41.813s
user	0m40.072s
sys	0m0.286s
admins@sandbox:~/Desktop/Algoritm_lab/5gorilla$ time ./main < ./data/secret/4huge.in > /dev/null

real	0m47.142s
user	0m38.243s
sys	0m0.536s

```
# 15.7 Examination and Points of Discussion
1. Have successfully implemented the algorithm with the correct time complexity.
   1. Yes. Wit time complixity of **O(nxm)**
2. Have neat and understandable code
   1. Checked
3. Have reasonable variable names.
   1. Checked
4. Have filled in the blanks in the report.
   1. Checked
5. Have run the check_solution.sh script to validate your solution.
   1. checked
   
---
# QUESTIONS
1. Is your solution recursive or iterative?
   1. My solution is iterative. Using table in **Needleman-Wunsch Sequence Alignment**
2. What is the time complexity, and more importantly why?
   1. **DP TAble** fill with time complexity **O(n x m)**
   2. **Backtracking** with time complexity **O(n x m)**
   3. **Overall** the time **complexity is O(n x m)**
3. What would the time complexity of a recursive solution without cache be?
   1. O(3^(n+m)) or O(3^n) Exponential!
   2. Why ? Without memoization, a recursive solution would have exponential time complexity O(3^(n+m)) because each recursive call branches into 3 subproblems with no overlap reuse, making it infeasible for strings longer than ~20 characters.
   ```
   At each step, you have 3 choices:
   3. Align char1 with char2 (diagonal)
   4. Insert gap in string1 (left)
   5. Insert gap in string2 (up)

    Recurrence: T(n,m) = T(n-1,m-1) + T(n-1,m) + T(n,m-1)

    This grows exponentially!
   ```
4. Can you think of any applications of this type of string alignment?
   1. Bioinformatic --> Compare DNA och RNA
   2. Plagiarism detection --> Comparing student submissions to din copied content
   3. Spell checking --> Finding closest matching word in dictionary.
   4. Speech recognition --> Aligning spoken words with transcirbed text
5. What could the costs represent in the applications?
   1. Different costs represetn different bioloical or linguistic properties like:
      1. Match (positive) --> Evolutionary conservation – same letter means no mutation
      2. MisMatch (negative) --> Mutation cost – different letters mean a substitution occurred
      3. Gap --> Insertion or deletion event (indel) – adding/removing a letter
---
# Result
1. Briefly comment the results, did the script say all your solutions were correct?
   1. Yes, all tests passed.
2. Approximately how long time does it take for the program to run on the largest input?
```
admins@sandbox:~/Desktop/Algoritm_lab/5gorilla$ time ./main < ./data/secret/4huge.in > /dev/null

real	0m47.142s
user	0m38.243s
sys	0m0.536s
admins@sandbox:~/Desktop/Algoritm_lab/5gorilla$ 
```

3. What takes the majority of the time?
   1. Filling the DP table (O(n x m)) operations

# Implementation details
1. How did you implement the solution?
   1. I need Needleman-Wunsch algorithm (Iterative DP)
2. Which data structures were used?
   1. 2D array with vector< vector< int >> for DP table, map< char, int > for letter indexing, string for sequences.
3. Which modifications to these data structures were used?
   1. None needed - standard Needleman-Wunsch
4. What is the overall running time? Why?
   1. O(n x m) - because we fill a 2D table with constant work per cell.