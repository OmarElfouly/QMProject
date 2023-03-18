# Project1

Person A = Ahmed Ali
Person B = Bavly Remon
Person C = Omar Elfouly

## Distribution plan:

### Part (A) split three way:

Person Ahmed will complete 1 and 2
Person Bavly will complete 3
Person Omar will complete 4 and 5

### Part (B), (C), (D) will be evenly split across members

## Plan so far:

- [x] Confirm Distrubition with Professor
- [x] Decide on data structure(s)
- [x] Decide on function headers i.e. input and output
- [x] Plan basic algorithm flow
- [x] Person A, B, C, begin programming
- [x] Test cases

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
####Inputs:

minterms: a vector of integers representing the minterms of a boolean function
var: a vector of characters representing the variables of the boolean function
print: a string that determines whether to print intermediate steps of the function
####Output:

A map that maps prime implicants to their corresponding minterms

#### Functions used
The functions use a structure called implicant that stores the minterms covered by the implicant,
the implicant itself, and whether or not it is combined.

Also several helper functions are used, including count_ones which counts the number of ones in a binary number, 
differ_by_one which checks if two binary numbers differ by exactly one bit, 
and combinestring which combines two binary strings into a new string where '-' is used to represent differing bits.

The to_binary_string function converts a decimal number into a binary string and pads it with leading zeroes to reach a specified length.

The split1 function is a string splitting function that splits .

The printVector function takes in a vector of vectors of implicants and an integer count, and prints out the implicants with their associated minterms and whether or not they are prime.

Then there is two main functions Primeimplicants and Generate groups

primeimplicants is a function that takes in a list of minterms and a list of variables as inputs and returns a map that represents the prime implicants of the Boolean function represented by the minterms.
The third input, print, is a string that determines whether or not the intermediate steps of the algorithm should be printed to the console.

The function first initializes an empty map to store the prime implicants.
It then checks for 2 possible cases that dont need to run the full algorithm to compute 
mainly if all possible minterms are present in the input list, in which case it returns a map with a single entry representing the function being always true.
And If there are no minterms, it returns an empty map.

The function then groups the minterms based on the number of ones in their binary representation, 
creating a set of groups of implicants It then calls the Generate groups function to actually compute the Prime implicants using the qm algorithm

Finally, the function converts the prime implicants into impliacnts using the variable represntation instead of the binary one 
and returns a map with entries representing the prime implicants and the minterms that they cover. 
If the print parameter is set to true, the function also prints the intermediate steps of the algorithm to the console.

The function generate_column takes in a  vector of vectors of implicants called groups, 
a vector of characters called var which represents the variables used in the Boolean expression, and a string variable print to control whether or not to print intermediate steps. 
The function generates a column of prime implicants using the Quine-McCluskey algorithm.

The function first initializes some variables, including vectors for prime implicants and groups of prime implicants, and a hash set to remove duplicates. 
It then loops through each group of implicants and compares each implicant with every implicant in the next group.
If two implicants differ by only one variable, they are combined into a new implicant and added to the appropriate group of prime implicants. 
The function then flags each combined implicant so it is not included in the final list of prime implicants. The function continues this process until no more implicants can be combined.

The function also has an optional printing feature to show the coloumns produced the algorithm. When print is set to "1", the function prints the current column of implicants, followed by a line of dashes to separate the output.

To remove duplicate prime implicants, the function uses a hash set called primes_checker. When a new prime implicant is generated, it is checked against the hash set. 
If the implicant is not in the hash set, it is added to the hash set and to the appropriate group of prime implicants. This ensures that each prime implicant is unique and not repeated in the final output.

Finally, the function returns the list of prime implicants found during the algorithm.

#### Design choices and changes

- Added the implicant struct instead of only using a string for the implicant to be able to store more data about the implicant 
(used struct instead of pair)

-decided to keep track of minterms combined to know the minterms covered by an implicant instead of using the implicant itself and some recursive function (reason why struct was implemented )

-Used an Unordered set instead of a vector to keep track of repeated combined implicants as it is O(1) search

-Used a do while loop instead of for loop to stop whe no more implicants can be combined 

-added extra parameter in the function to add the option to print or not





### Part 4 and 5:
Input:map where key is the PI and the data is a vector of int values to represent the covers of a minterm
Output: Solved SOP

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