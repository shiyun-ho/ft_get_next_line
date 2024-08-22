# Table of Contents

- [Table of Contents](#table-of-contents)
	- [Description](#description)
	- [To Do](#to-do)
	- [Useful commands](#useful-commands)
	- [Documentation](#documentation)
	- [Test cases](#test-cases)

## Description
get_next_line is a project which is intended to explore the use of*static variables* in C.

- Requirements: 
   - Repeated calls to get_next_line() function should let the text file pointed by file descriptor read the text one line at a time. 
      - Repeated calls to get_next_line() can be done using a loop. 
   - Function should return the line that was read. 
      - Return NULL when: 
         - Nothing else to read
         - If error occurred
   - Function should work when reading a file and when reading from standard input
   - Returned line should include terminating \n character
      - Except if end of file was reached and does not end with a \n character
   - Header file must contain the prototype of get_next_line() function 
   - Add all helper functions to the get_next_line_utils.c file
   - Add this option to compiler call: -D BUFFER_SIZE=N
      - To read files in get_next_line()
      - Define the buffer size to read
      - Buffer size value to be modified by evaluators and Moulinette
   - Project should be possible to be compiled with and without the -D BUFFER_SIZE flag on top of the usual flags. Default value can be chosen by coder. 
   - Compile the code with: cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c
   - get_next_line() has an undefined behaviour if the file pointed by file descriptor changed since last call whereas read() didn't reach the end of file.
   - get_next_line() has undefined behaviour too when reading binary file. Handling for this behaviour is up to the user. 
   - Forbidden function: 
      - libft
      - lseek()
      - global variables

## To Do
- [ ] Update [headerfile](get_next_line.h) to include functions whenever appropriate
- [ ] Write [function](ft_printf.c) 
- [ ] Implement the following conversions:
   - [ ] 
   - [ ] 
   - [ ] 
 - [ ] Write unit tests:
   - [ ] Positive cases
   - [ ] Negative cases
   - [ ] Edge cases
 - [ ] Check for memory leaks using valgrind (requires main() in test.c)
	- Compile output file
		>> gcc -Wall -Werror -Wextra test.c -L. -lftprintf
	- Run valgrind on output for main function
		>> valgrind ./a.out
	- Run checks on memory leaks using valgrind if mem leaks happen
		>> valgrind --leak-checks=yes ./a.out

## Useful commands
	- Ensure that libftprintf.a has been archived
		>> make

	- To link .c file with library
		>> gcc test.c -L. -lftprintf

	- To link .c file with library in debug mode on Visual Studio code
    	-Ensure that test.c has main function before running
		>> Modify .vscode/tasks.json
		>> Modify "args" attribute:

		"args": [
                "-fdiagnostics-color=always",
                "-g",
                "${file}",
                "-o",
                "${fileDirname}/${fileBasenameNoExtension}",
				"-L.",
				"-lftprintf"
            ],

		>> Run debugger

## Documentation

1. Format argument is reused whenever necessary to convert all given arguments.
   > printf %s a b

   > 'ab'

2. Missing arguments are treated as null strings or as zeros.
   - This depends on whether context expects string or a number
	> printf %sx%d

	> 'x0'

3. Additional escape '\c' results in no further output.
	> printf ("A%sC\cD%sF", B, E)

	> 'ABC'


## Test cases

1. Positive cases
   - %c single character
   - %s string (as defined by common C convention)
   - %p void * pointer argument (in hexadecimal format)
   - %d decimal (base 10) number
   - %i integer in base 10
   - %u unsigned decimal (base 10) number
   - %x number in hexadecimal lowercase
   - %X number in hexadecimal uppercase
   - %% prints percent sign

2. Negative cases
   - %c single character
   - %s string (as defined by common C convention)
   - %p void * pointer argument (in hexadecimal format)
   - %d decimal (base 10) number
   - %i integer in base 10
   - %u unsigned decimal (base 10) number
   - %x number in hexadecimal lowercase
   - %X number in hexadecimal uppercase
   - %% prints percent sign

3. Edge cases
   - Dealing with format specifiers out of scope within printf
   - Dealing with spaces in between % and format specifier
   - Printing words after format specifier
