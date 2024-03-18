![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
# GET NEXT LINE

> **Note:** This is a project from **42 learning cursus**.

## Description
This projects consists of a simple function to code: `get_next_line()`.<br>
This function takes a file descriptor as parameter and returns a string (as define by C language, a `char *`) with the next line to read from the file pointed by the file descriptor.<br>
We can read the file with various BUFFER_SIZE which forces us to learn a new concept: static variables.<br>
Actually, the content of the file is read and a line is returned while the rest of the content is stored into a static variable.<br><br>
Here are the bonus part requirements:
- `get_next_line()` is developed using only one static variable.
- `get_next_line()` can manage multiple file descriptors at the same time.
For example, if you can read from the file descriptors 3, 4 and 5, you should be
able to read from a different fd per call without losing the reading thread of each
file descriptor or returning a line from another fd.
It means that you should be able to call get_next_line() to read from fd 3, then
fd 4, then 5, then once again 3, once again 4, and so forth.

## Pinciples
- The function reads form the file descriptor until it encounters a new line character `\n`
- When a new line character is found, the reading process stops
- If there is some content read after the new line character, it is stored into a chained list with the corresponding file descriptor (using a structure)
- The whole line is returned (an allocated string containing the new line)
- The only static variable is a pointer to the chained list, this list being updated at each get_next_line() call

The custom structure:
```
typedef struct s_buffer_save
{
	int		fd;
	char	*buffer;
}	t_buffer_save;
```
It enables to store (into the list) a file descriptor and its corresponding buffer.

## Setup instructions
> This is not a program but a function.
1. Clone the repo: `git clone https://github.com/code-kiwi/42_GET_NEXT_LINE` and feel free to use it the way you want.
> **Note:** The bonus part is included into the mandatory part.

## Testing
In order to test the project, I made a little program into GNL_TESTER folder.<br>
For testing:
- copy the files `get_next_line.c`, `get_next_line_utils.c` and `get_next_line.h` into `GNL_TESTER/`
- use the command `make` (you can use `make BUFFER_SIZE=<SIZE>` in order to test the project with a custom buffer size)
- the executable `prog` should be created:

|COMMAND              |DESCRIPTION                                                                                              |
|---------------------|---------------------------------------------------------------------------------------------------------|
|`./prog`             |With no parameter, the program will read from STDIN an print the content line by line                    |
|`./prog file1`       |With one parameter, the program will try to open the given file and display its content line by line     |
|`./prog file1 file2` |With two parameters, the program will display both file contents, line by line, by alternating the files |

I also provided some test files into `GNL_TESTER/test_files/`.

## Grade
![GNL](https://github.com/ayogun/42-project-badges/blob/main/badges/get_next_linee.png)<br><br>
`112/125`<br>
> I still have to retry the project. To be honest, I have been forced to retry it because a student thought I made a mistake.
> He was wrong and the correction he suggested me made the project wrong for the 42's moulinette (the school testing tool for some of our projects).

## Credits
The badge comes from [this repo](https://github.com/ayogun/42-project-badges/tree/main), by [@ayogun](https://github.com/ayogun) which proposes a lot of amazing badges for 42 projects.
