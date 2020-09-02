#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>

void parse_args(int argc, char* argv[], std::unordered_map<std::string, std::string>& args_map, std::unordered_set<std::string>& args_set) {
	std::vector<std::string> args_raw;
	args_raw.reserve(argc);
	for (int i = 1; i < argc; ++i)
		args_raw.push_back(argv[i]);
	std::string last = "";
	std::string group = "";
	for (const std::string& arg: args_raw) {
		if (group.size() > 0) {
			group += arg;
			if (group.size() >= 2 && group[0] == group[group.size() - 1]) {
				group = group.substr(1, group.size() - 2);
				if (last == "")
					args_set.insert(group);
				else
					args_map[last] = group;
				group = "";
				last = "";
			}
		} else if (arg.size() > 0 && (arg[0] == '"' || arg[0] == '\'')) {
			group += arg;
		} else if (arg.size() > 2 && arg.substr(0, 2) == "--") {
			std::string sub = arg.substr(2);
			if (args_map.count(sub) == 1)
				args_map.insert({sub, ""});
			else
				args_map[sub] = "";
			last = sub;
		} else if (arg.size() > 1 && arg[0] == '-') {
			for (std::string::size_type i = 1; i < arg.size(); ++i) {
				std::string sub = arg.substr(i, 1);
				if (args_map.count(sub) == 1)
					args_map.insert({sub, ""});
				else
					args_map[sub] = "";
				last = sub;
			}
		} else {
			if (last == "")
				args_set.insert(arg);
			else
				args_map[last] = arg;
			last = "";
		}
	}
	if (group.size() > 0) {
		group = group.substr(1);
		if (last == "")
			args_set.insert(group);
		else
			args_map[last] = group;
		group = "";
		last = "";
	}
}

int main(int argc, char* argv[]) {
	std::unordered_map<std::string, std::string> args_map;
	std::unordered_set<std::string> args_set;
	parse_args(argc, argv, args_map, args_set);

	if (args_map.count("h") == 1 || args_map.count("help") == 1) {
		std::cout
			<< "Help:" << std::endl
			<< "usage: brainfuck [-h --help] [-v --verbose] [-d --debug] [-m <mem_size=30000> {1:}] [-r <reg_size=1> {1,2,4,8}] [-c <compiler=g++>]" << std::endl
		;
		return EXIT_SUCCESS;
	}

	bool debug = false;
	if (args_map.count("d") == 1 || args_map.count("debug") == 1) {
		debug = true;

		std::cout << "args_map: {" << std::endl;
		for (const auto& arg: args_map)
			std::cout << "'" << arg.first << "': '" << arg.second << "'," << std::endl;
		std::cout << "}" << std::endl << std::endl;

		std::cout << "args_set: { ";
		for (const auto& arg: args_set)
			std::cout << "'" << arg << "', ";
		std::cout << "}" << std::endl << std::endl;
	}

	bool verbose = false;
	if (args_map.count("v") == 1 || args_map.count("verbose") == 1)
		verbose = true;

	size_t mem_size = 30'000;
	if (args_map.count("m") == 1) {
		try {
			mem_size = std::stoull(args_map["m"]);
		} catch (const std::invalid_argument& e) {
			throw std::invalid_argument("-m: invalid mem_size");
		} catch (const std::out_of_range& e) {
			throw std::invalid_argument("-m: out of range mem_size");
		}
		if (mem_size == 0)
			throw std::invalid_argument("-m: mem_size cannot be 0");
	}

	size_t reg_size = 1;
	if (args_map.count("r") == 1) {
		try {
			reg_size = std::stoul(args_map["r"]);
		} catch (const std::invalid_argument& e) {
			throw std::invalid_argument("-r: invalid reg_size");
		} catch (const std::out_of_range& e) {
			throw std::invalid_argument("-r: out of range reg_size");
		}
		if (std::unordered_set({1, 2, 4, 8}).count(reg_size) != 1)
			throw std::invalid_argument("-r: reg_size must be 1, 2, 4 or 8");
	}

	std::string compiler = "g++";
	if (args_map.count("c") == 1)
		compiler = args_map["c"];

	if (debug) {
		std::cout
			<< "debug: " << debug << std::endl
			<< "verbose: " << verbose << std::endl
			<< "mem_size: " << mem_size << std::endl
			<< "reg_size: " << reg_size << std::endl
			<< "compiler: " << compiler << std::endl
		;
	}

	return EXIT_SUCCESS;
}
