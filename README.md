Word Sorter

There exist POSIX programs for counting the number of words in a 
file (wc(1)), and for sorting files (sort(1)). However, 
no program exists for sorting words within a file. 
Write such a program.

Given any number of files on the command line, the program should 
extract all words (delimited by whitespace) from the file, 
and print them to stdout, sorted lexicographically, one word per 
line. With no arguments, it should read from stdin. No other 
output during normal operation is permitted.

**** Requirements

When passed a -c <n> flag, the program prints only the first n 
results of the sorted list of words.

When passed a -r flag, the program prints in reverse order.

When passed a -n flag, the program sorts the words as if they were numbers.

When passed a -l flag, the program sorts the words by length.

When passed a -s flag, the program sorts the words by their score in Scrabble®.

When passed a -a flag, the program sorts the words lexicographically (the default).

When passed a -u flag, the program only prints unique words, and does not print 
duplicates.

When passed a -h flag, the program prints a brief help message instead of any 
normal operation.

If flags are specified multiple times, resolve them in the following order:
	Unknown flags should cause the program to exit abnormally.
    	-h takes priority over any other flags.
    	The most recently seen ordering flag takes precedence 
	(i.e., the last one on the command line). 
	Same goes for multiple -c flags.
    	Each pair of -r flags cancels each other out.
    	Multiple -u flags do not affect each other.

Trailing punctuation is considered part of the word, and need not be discarded.

***** Submission

This project is to be submitted via github. The name of the project in github should be called wordsorter.

After checking out the project, it should build via make. The target make debug 
should build a debugging version of the program. The target make profile 
should build a profiling version of the program. The name of the program 
built should be ws.

The assignment will be pulled from what is on Github on NOV10 2359EST

***** Flourishes

    Write a man(1) page for the program.
    Add in a -p flag that strips any non-alphanumeric characters from the ends of words before sorting.
    Challenge: Add a -e which, instead of Unicode lexicographic order, 
    sorts the words by EBCDIC lexicographic order.

***** Rubric
Correct 	30%
Readable 	20%
Clean 		10%
Idiomatic 	30%
Version Control 10%
