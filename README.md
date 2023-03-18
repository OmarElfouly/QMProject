# Project1

Person A = Ahmed Ali
Person B = Bavly Remon
Person C = Omar Elfouly

## Distribution plan:

### Part (A) split three way:

- Ahmed will complete 1 and 2
- Bavly will complete 3
- Omar will complete 4 and 5

### Part (B), (C), (D) will be evenly split across members

## Plan so far:

- [x] Confirm Distrubition with Professor
- [x] Decide on data structure(s)
- [x] Decide on function headers i.e. input and output
- [x] Plan basic algorithm flow
- [x] Person A, B, C, begin programming
- [x] Test cases

## Algorithim Requirments

Part 1:  Read in (and validate) a Boolean function given as a SoP (for example: abc + a’b’c).
Assume that the variable name is a single Latin letter starting from “a”. Think about the checkers
needed to validate the input and list them in your report.

Part 2: Print the truth table of the function as well as the canonical SoP and PoS.

Part 3: Generate and print all prime implicants (PIs). For each PI show the minterms it covers as
well as its binary representation.

Part 4:  Using the PIs generated in part 2, obtain and print all the essential prime implicants EPIs
(as Boolean expressions). Also, print the minterms that are not covered by the essential PIs.

Part 5:  Solve the PI table and print the minimized Boolean expression of the Boolean
function using the 3 step heuristic discussed in the lecture.

## Program Design
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

#### Functions used
The function uses a structure called implicant that stores the minterms covered by the implicant,
the implicant itself, and whether or not it is combined.

The program also defines several helper functions, including count_ones which counts the number of ones in a binary number, 
differ_by_one which checks if two binary numbers differ by exactly one bit, 
and combinestring which combines two binary strings into a new string where '-' is used to represent differing bits.

The to_binary_string function converts a decimal number into a binary string and pads it with leading zeroes to reach a specified length.

The generate_column function generates a column of prime implicants from a table of minterms or implicants.
It takes in a vector of vectors of implicants, 
a vector of characters representing the variables in the function, and a string to know whether to print the output or not.

The split1 function is a string splitting function that splits .

The printVector function takes in a vector of vectors of implicants and an integer count, and prints out the implicants with their associated minterms and whether or not they are prime.

#### Design choices and changes

- Added the implicant struct instead of only using a string for the implicant to be able to store more data about the implicant 
(used struct instead of pair)

-decided to keep track of minterms combined to know the minterms covered by an implicant instead of using the implicant itself and some recursive function (reason why struct was implemented )

-Used an Unordered set instead of a vector to keep track of repeated combined implicants as it is O(1) search

-Used a do while loop instead of for loop to stop whe no more implicants can be combined 

-added extra parameter in the function to add the option to print or not


### Part 4 and 5:

Since part 4 can be considered an essential subsection of part 5 we will be discussing them together.

Input: Map where key is the PI and the data is a vector of int values to represent the covers of a minterm
Output: Final answer in the form of minimum covers 

This part of the algorithim is controlled and accomplished by the function named part4and5() in part4_5.h

The trivial solutions to this part of the algorithim occur whenever there are no prime implicants i.e. function = 0
and when the function = 1. We account for these using if conditions at the start of the algorithim.

For the sake of clarity we can imagine our data as a table with our rows being the PIs and our columns being minterms.

The program requires us to find essential prime implicants, dominating columns and dominated rows. This immeadily will
require us iterate through the data in terms of columns and rows. Unfortunatly there exists no singular data structure
in c++ that has the ability to interpret the data in terms of rows and columns in reasonable time. Therefore, a reflected
map will be used to allow for effecient access of both columns and rows.

To create the reflected map we only need to iterate through the first map to find every minterm and create a list of the prime implicants that cover it.

Part 4 requires us to find all essential prime implicants, which are prime implicants that are the only covers for one or more minterms.
This will require us to iterate through each minterm and check to see whether it is covered by a single minterm. The advantage of the
reflected map is made clear here since it it reduces the time complexity of this section from n^3 to n^2 by sacrificing some extra storage.

Next we will iterate through each minterm (column) and insert all prime implicants that uniquely cover a single minterm
into a vector of strings named EPIS.

The algortithim then prints these essential prime implicants, satisfying the first section of part 4.

The remaining minterms can then be found by removing the essential prime implicants from the table such that all their minterms
are deleted from both data structures (i.e. removed from both rows and columns).

To modularise the algorithim a function with the purpose of deleting a term from the reflected data structure was created
for both rows and columns to simplify the deletion process.

The remaining minterms are the keys left over in the minterm map after we have removed all the minterms present in the
essential prime implicants.

This completes part 4 which can be described as finding essential prime implicants and updating the table.

Part 5 is completed by the remaining code which can be simplified to the following algorithim:

While there are still uncovered minterms

 - Find the current essential prime implicants and then add them to final answer while removing them from table
 - Remove dominating columns
 - Remove dominated rows

 A dominating column is removed since this minterm is covered by another minterm. This means that we need to delete any
 column that is a superset of another column.

 Similarly a dominated row is removed since its a prime implicant that is fully covered by another prime implicant. This will
 involve deleting any row that is a subset of another row.

 To detect subset and superset relationships we will be using the IsSubset function which returns true if the first argument
 is a subset of the second argument.

 We will then iterate through the rows and columns, while deleting rows and columns as neccessary.

 From the table we are left with we can select the new articial essential prime implicants just as we did in Part 4, adding
 every one of them to our final answer.
 
 This will repeat until there are no minterms left uncovered, at that point the function prints the final answer.

## Testing:
### Test 1:
3 variable input, with f = 0. The test input is: aa'+bb'+cc', which is evaluated to 0.

### Test 2:
3 variable input, with f = 1. The test input is a'+a+b+c, which is evaluated to 1.

### Test 3:
Demonstrating variables repeated multiple times in the same term: aaaa+b'b'b', which evaluates to a + b'.

### Test 4:
Demonstarting processing of dominance: a'b'c'd'+a'bc'd'+a'bc'd+a'bcd'+a'bcd+ab'c'd'+ab'c'd+ab'cd'+abc'd+abcd.

### Test 5:
Demonstrating how multiple negations and multiple additions are simplified. a’’b ++ c becomes ab + c.

### Test 6:
Demonstrating an inavlid PoS term, which shows bracket handling. ((abbbc)(ac+d)) would be invalid since we are multiplying a sum.

### Test 7:
Demonstrating using multiple negations on the same term, along with handling brackets. (((abbbc’’’’’))+cdd) becomes abc’ + cd

### Test 8:
Demonstrating a multiple variable negation, which would be invalid. This also includes bracket handling. (a+b)' would be invalid.

### Test 9:
Demonstrating how the program identifies lowercase and uppercase variables to be identical. ac + Ac would be ac + ad

### Test 10:
A final all encompassing input, which contains multiple nested brackets, repeated variables in the same term, multile negations, and multiple additions, all at once. ((((abcd’’’’ef’’’ghij)) + ghi’’’) ++++ abbbbc) would be evaluated as abcdef’ghij + ghi’ + abc.