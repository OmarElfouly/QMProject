# Project1

Person A = Ahmed Ali
Person B = Bavly Remon
Person C = Omar Elfouly

## Distribution plan:

### Part (A) split three way:

Person A will complete 1 and 2
Person B will complete 3
Person C will complete 4 and 5

### Part (B), (C), (D) will be evenly split across members

## Plan so far:

- [ ] Confirm Distrubition with Professor
- [ ] Decide on data structure(s)
- [ ] Decide on function headers i.e. input and output
- [ ] Plan basic algorithm flow
- [ ] Person A, B, C, begin programming
- [ ] Test cases

## Overview
### Part 1:
Takes input validates SoP:
- latin letters a to z
- if there are no brackets then it is SoP
- Unclosed bracket is an automatic fail
- Operator at start or finish is a fail
- Cannot be (ab)' or (a+b)' i.e. no multi input not operations or not that acts on a sum
- any ( SUM ) must be preceded and followed by a "+" or nothing at all 
- we will consider " AA+AA' " to be valid sop
- must be products with only sums between them
- must return a list or vector of the variables in the input for other functions to use

Input: User input
Output: Clean input

### Part 2:
Input: clean user input
Output: Vector of min terms (x = {1,5,9}), and string of variables ("ACF")

### Part 3:
Input: Vector of min terms (x = {1,5,9}), and string of variables ("ACF")
Output: map where key is the PI and the data is a vector of bool values such that a True in position x means this PI covers minterm x

### Part 4 and 5:
Input:map where key is the PI and the data is a vector of bool values such that a True in position x means this PI covers minterm x
Output: Solved sop

