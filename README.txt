
Hello! This is project BlockEditor for seminar C++. I am Martin Benes,
and me and my friend Ondrej Polansky, we are the authors of this program.

Here is a basic layout of files:
./src/*       - source code
./examples/*  - examples (saved schemes)
./doc/        - documentation
./styles/     - graphical style files
./README.txt  - basic introduction
./Makefile    - build system

You can compile the project in main project directory with command
    $ make

It will create a file blockeditor in main directory. You can run the
program with
    $ ./blockeditor
or simply
    $ make run

*----------------------------------------*
|               CONTROLS                 |
|                                        |
| left-click       select button         |
|                  place item            |
| double-left      set value (on input)  |
| right-click      remove item           |
| mouse hover      show info             |
| space            step during debug     |
| esc              end debug / edit mode | 
*----------------------------------------*

Evaluate:
Run > Compute

Debug:
Run > Debug

For more information, read the documentation.
It must be generated first:
    $ make doxygen
After that, open doc/html/index.hml in any browser.

