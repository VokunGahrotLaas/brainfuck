// C++ std
#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <stdexcept>

// C std
#include <cstdlib>

// project
#include "my_args_parser.hpp"


void transcompile(const MyArgsParser& parser, const std::string& bf_filename, const std::string& cpp_filename);


int main(int argc, const char* argv[]) {
	MyArgsParser parser(argc, argv);

	for (const auto& bf_filename: parser.files) {
		std::string exe_filename = bf_filename.substr(0, bf_filename.rfind(".")) + parser.exe_extension;
		std::string cpp_filename = bf_filename.substr(0, bf_filename.rfind(".")) + ".cpp";
		transcompile(parser, bf_filename, cpp_filename);
		std::string compile_string = parser.compiler + " " + cpp_filename + " -o " + exe_filename + " " + parser.compiler_options;
		if (std::system(compile_string.c_str()) == EXIT_SUCCESS) {
			if (parser.verbose)
				std::cout << "Compiled '" << cpp_filename << "' successfully." << std::endl << std::endl;
		} else {
			throw std::invalid_argument("Could not compile '" + cpp_filename + "' successfully.");
		}
	}

	return EXIT_SUCCESS;
}


void transcompile(const MyArgsParser& parser, const std::string& bf_filename, const std::string& cpp_filename) {
	std::fstream bf_file(bf_filename, std::ios_base::in);
	if (!bf_file.is_open())
		throw std::invalid_argument("File '" + bf_filename + "' could not be oppened.");

	std::fstream cpp_file(cpp_filename, std::ios_base::out | std::ios_base::trunc);
	if (!cpp_file.is_open())
		throw std::invalid_argument("File '" + cpp_filename + "' could not be oppened.");
	
	if (parser.verbose)
		std::cout << "File '" + bf_filename + "' and '" << cpp_filename << "' oppened successfully." << std::endl;
	
	cpp_file
		<< "#include <iostream>" << std::endl
		<< "#include <cstdint>" << std::endl
		<< "using namespace std;" << std::endl
		<< "int main(void) {" << std::endl
		<< "\tuint" << parser.reg_size * 8 << "_t* p = new uint" << parser.reg_size * 8 << "_t[" << parser.mem_size << "];" << std::endl
		<< "\tfor (size_t i = 0; i < " << parser.mem_size << "; ++i) p[i] = 0;" << std::endl
	;

	char last = '\0';
	std::size_t rep = 0;
	std::size_t tabs = 1;
	while (!bf_file.eof()) {
		char c = bf_file.get();
		if (c == last) {
			++rep;
		} else {
			if (last == '+')
				cpp_file << std::string(tabs, '\t') << "*p += " << rep << ";" << std::endl;
			else if (last == '-')
				cpp_file << std::string(tabs, '\t') << "*p -= " << rep << ";" << std::endl;
			else if (last == '>')
				cpp_file << std::string(tabs, '\t') << "p += " << rep << ";" << std::endl;
			else if (last == '<')
				cpp_file << std::string(tabs, '\t') << "p -= " << rep << ";" << std::endl;
			rep = 1;
		}
		if (c == '[') {
			cpp_file << std::string(tabs, '\t') << "while (*p != 0) {" << std::endl;
			++tabs;
		} else if (c == ']') {
			if (tabs == 1)
				throw std::invalid_argument("missing ']' in '" + bf_filename + "'");
			--tabs;
			cpp_file << std::string(tabs, '\t') << "}" << std::endl;
		} else if (c == '.') {
			if (parser.ascii)
				cpp_file << std::string(tabs, '\t') << "cout << static_cast<char>(*p);" << std::endl;
			else
				cpp_file << std::string(tabs, '\t') << "cout << *p << endl;" << std::endl;
		} else if (c == ',') {
			if (parser.ascii)
				cpp_file << std::string(tabs, '\t') << "*p = static_cast<uint" << parser.reg_size * 8 << "_t>(cin.get());" << std::endl;
			else
				cpp_file << std::string(tabs, '\t') << "cin >> *p;" << std::endl;
		}
		last = c;
	}
	if (tabs > 1)
		throw std::invalid_argument("missing '[' in '" + bf_filename + "'");

	cpp_file << "}" << std::endl;

	if (parser.verbose)
		std::cout << "Transcompiled '" << bf_filename << "' from brainfuck to C++ successfully." << std::endl;
}
