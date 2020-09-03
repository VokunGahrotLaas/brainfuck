# Brainfuck
Brainfuck compiler written in C++.\
Tanscompiles brainfuck to C++ then compiles C++ with a C++ compiler.

## Usage:
 * `<files> strings`: list of files to compile.
 * `[-h --help]`: display this help messages and quit.
 * `[-v --verbose]`: display info on compilation progress.
 * `[-d --debug]`: display debug info (about args parser).
 * `[-a --ascii]`: output and input are in characters not in numbers.
 * `[-m <mem_size=30000> {1:}]`: size of the program's array.
 * `[-r <reg_size=1> {1,2,4,8}]`: size of the array's cells (in bytes).
 * `[-c <compiler='g++'> string]`: C++ compiler.
 * `[-o <compiler_options='-std=c++14 -Ofast'> string]`: compiler options.
 * `[-e <exe_extension=''> string]`: extension for resulting executable files (default is '.exe' for Windows and none otherwise).

## Argument structure explanation:
 * bool: `-{short name} --{long name}`
 * other: `-{short name} --{long name} <{internal name}={default value}> {possible values}`
 * optional: `[{argument structure}]`

## Example:
 * brainfuck *.bf -va -m 1024 -r 4
Compiles all .bf files with an array of 1024 cells of 32bits, using ascii I/O and with verbose.