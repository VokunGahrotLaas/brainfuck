#ifndef MY_ARGS_PARSER_HPP
#define MY_ARGS_PARSER_HPP

// C++ std
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <stdexcept>

// C std
#include <cstdlib>

// project
#include "args_parser.hpp"


class MyArgsParser: public ArgsParser {
public:
	MyArgsParser(int argc = 0, const char* argv[] = nullptr);
	~MyArgsParser(void) override = default;

	std::vector<std::string> files;
	bool debug;
	bool verbose;
	bool ascii;
	std::size_t mem_size;
	std::size_t reg_size;
	std::string compiler;
	std::string compiler_options;
	std::string exe_extension;
};


MyArgsParser::MyArgsParser(int argc, const char* argv[]):
	ArgsParser(argc, argv),
	files(),
	debug(false),
	verbose(false),
	ascii(false),
	mem_size(30'000),
	reg_size(1),
	compiler("g++"),
	compiler_options("-std=c++14 -Ofast"),
#ifdef _WIN32	// windows
	exe_extension(".exe")
#else	// normal (linux or mac)
	exe_extension("")
#endif
{
	if (m_args_map.count("h") == 1 || m_args_map.count("help") == 1) {
		std::cout
			<< "Usage:" << std::endl
			<< "  <files> strings: list of files to compile." << std::endl
			<< "  [-h --help]: display this help messages and quit." << std::endl
			<< "  [-v --verbose]: display info on compilation progress." << std::endl
			<< "  [-d --debug]: display debug info (about args parser)." << std::endl
			<< "  [-a --ascii]: output and input are in characters not in numbers." << std::endl
			<< "  [-m <mem_size=30000> {1:}]: size of the program's array." << std::endl
			<< "  [-r <reg_size=1> {1,2,4,8}]: size of the array's cells (in bytes)." << std::endl
			<< "  [-c <compiler='g++'> string]: C++ compiler." << std::endl
			<< "  [-o <compiler_options='-std=c++14 -Ofast'> string]: compiler options." << std::endl
#ifdef _WIN32	// windows
			<< "  [-e <exe_extension='.exe'> string]: extension for resulting executable files." << std::endl
#else	// normal (linux or mac)
			<< "  [-e <exe_extension=''> string]: extension for resulting executable files." << std::endl
#endif
			<< std::endl
			<< "Argument structure explanation:" << std::endl
			<< "  bool: -{short name} --{long name}" << std::endl
			<< "  other: -{short name} --{long name} <{internal name}={default value}> {possible values}" << std::endl
			<< "  optional: [{argument structure}]" << std::endl
			<< std::endl
			<< "Example:" << std::endl
			<< "  brainfuck *.bf -va -m 1024 -r 4" << std::endl
			<< "Compiles all .bf files with an array of 1024 cells of 32bits, using ascii I/O and with verbose." << std::endl
			<< std::endl
		;
		std::exit(EXIT_SUCCESS);
	}

	if (m_args_map.count("d") == 1 || m_args_map.count("debug") == 1)
		debug = true;

	if (m_args_map.count("v") == 1 || m_args_map.count("verbose") == 1)
		verbose = true;

	if (m_args_map.count("a") == 1 || m_args_map.count("ascii") == 1)
		ascii = true;

	if (m_args_map.count("m") == 1) {
		mem_size = parse_size_t("m", "mem_size");
		if (mem_size == 0)
			throw std::invalid_argument("-m: mem_size cannot be 0");
	}

	if (m_args_map.count("r") == 1) {
		reg_size = parse_size_t("r", "reg_size");
		if (std::unordered_set<std::size_t>({1, 2, 4, 8}).count(reg_size) != 1)
			throw std::invalid_argument("-r: reg_size must be 1, 2, 4 or 8");
	}

	if (m_args_map.count("c") == 1)
		compiler = m_args_map["c"];

	if (m_args_map.count("o") == 1)
		compiler_options = m_args_map["o"];

	if (m_args_map.count("e") == 1)
		exe_extension = m_args_map["e"];

	files.reserve(m_args_set.size());
	for (const auto& arg: m_args_set)
		files.push_back(arg);

	if (verbose && files.size() > 0)
		std::cout << std::endl;

	if (debug) {
		std::cout << "m_args_map: {" << std::endl;
		for (const auto& arg: m_args_map)
			std::cout << "'" << arg.first << "': '" << arg.second << "'," << std::endl;
		std::cout << "}" << std::endl << std::endl;

		std::cout << "m_args_set: { ";
		for (const auto& arg: m_args_set)
			std::cout << "'" << arg << "', ";
		std::cout << "}" << std::endl << std::endl;

		std::cout << "files: [ ";
		for (const auto& file: files)
			std::cout << "'" << file << "', ";
		std::cout << "]" << std::endl;

		std::cout
			<< "debug: " << (debug ? "true" : "false") << std::endl
			<< "verbose: " << (verbose ? "true" : "false") << std::endl
			<< "ascii: " << (ascii ? "true" : "false") << std::endl
			<< "mem_size: " << mem_size << std::endl
			<< "reg_size: " << reg_size << std::endl
			<< "compiler: '" << compiler << "'" << std::endl
			<< "compiler_options: '" << compiler_options << "'" << std::endl
			<< "exe_extension: '" << exe_extension << "'" << std::endl
			<< std::endl
		;
	}
}


#endif // MY_ARGS_PARSER_HPP