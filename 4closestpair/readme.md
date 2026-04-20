# Result
### running program
```
admins@sandbox:~/Desktop/Algoritm_lab/4closestpair$ ls
check_solution.sh  data  main.cpp  pair  readme.md  report.tex
admins@sandbox:~/Desktop/Algoritm_lab/4closestpair$ g++ -std=c++11 -o pair main.cpp
admins@sandbox:~/Desktop/Algoritm_lab/4closestpair$ time ./check_solution.sh ./pair 
data/sample/1.in
Correct!
data/sample/2.in
Correct!
data/more/1.in
Correct!
data/more/2.in
Correct!
data/more/3.in
Correct!
data/more/4.in
Correct!
data/more/5.in
Correct!
data/secret/0mini.in
Correct!
data/secret/1small.in
Correct!
data/secret/2med.in
Correct!
data/secret/3large1.in
Correct!
data/secret/4large2.in
Correct!
data/secret/5larger.in
Correct!
data/secret/6huge.in
Correct!
data/secret/7huger.in
Correct!

real	0m4.700s
user	0m4.185s
sys	0m0.220s
admins@sandbox:~/Desktop/Algoritm_lab/4closestpair$ time ./pair < ./data/secret/7huger.in
446.525475

real	0m3.780s
user	0m3.627s
sys	0m0.051s
admins@sandbox:~/Desktop/Algoritm_lab/4closestpair$ 
```
* Briefly comment the results, did the script say all your solutions were correct? Yes
* Approximately how long time does it take for the program to run on the largest input? 3.780 seconds
* What takes the majority of the time? Slowest part are two sort operation: **sort(points.begin(), points.end()) – initial sort by X** and **sort(strip.begin(), strip.end(), by Y) – sorting strip at each recursion level**
---
# Implementation
1. How did you implement the solution?
   1. By making struct Point for each position
   2. Saving all Positions on vector< Point >
   3. Distance function to calculate distance between two point
   4. Finally implement the ClosestPair function recursive:
      1. divide each vector in halv right and left
      2. search for minum distans between two points
      3. return the minimum when reach base cases.

2. Which data structures were used?
   1. **class struct Point to save point x,y**
   2. vector< Point > to save alll struct Point

3. Which modifications to these data structures were used?
   1. Operator overloading for sorting – Added operator< to Point struct to sort by x-coordinate (and y as tie-breaker)
   2. Temporary strip vector – Created a separate vector< Point > to store only points within distance d of the middle line
   3. Custom comparator for sorting strip – Used lambda function [](Point a, Point b) { return a.y < b.y; } to sort strip by y-coordinate
   4. Reserve memory – Used points.reserve(n) to pre-allocate memory and avoid reallocations

4. What is the overall running time? Why?
   1. Over all run time is: O(nlogn)
   2. Why? see pdf
      1. Recursive divide O(logn) levels (split n in half)
      2. Working per level O(n) (building strip, sorting)
      3. total: O(nlogn)

---

# 14.5 Examination and Points of Discussion
1. Have successfully implemented the algorithm with the correct time complexity.
* Yes, see pdf file: closestPairExplanation.pdf.
```
xfun::embed_file("./closestPairExplanation.pdf")
```
2. Have neat and understandable code.
* checked.
3. Have descriptive variable names.
* checked
4. Have filled in the blanks in the report.
* checked
5. Have run the check_solution.sh script to validate your solution.
* see result.
---
6. What is the time complexity, and more importantly why?
* The Time complixity is O(nlogn) more spicific O(nlog2n)
7. Why is it sufficient to check a few points along the mid line?
* You have many points on a map. You want the closest pair.
* d = the shortest distance you have found so far (from left and right sides).
* Think of it like this:

    You already have two points that are d meters apart

    Any new pair must be closer than d to beat the record

    If a point is far from the middle line (more than d meters away), it cannot make a pair closer than d

    So you only look at points that are within d meters of the line

Because any two points closer than d must be within d of the middle line, and in that narrow strip there can only be 6-7 points without being closer than d to each other.

6. Draw a picture and show/describe when each distance is checked in your solution!
* see see pdf file: closestPairExplanation.pdf.
7. When do you break the recursion and use brute force?
* When the critria is not reached. if left-right > 1 or == 2 or == 3.
* If there are point more 1, just calculate the distance between those
* If there is more then 3 point divide more (divide and qonquer) 
















