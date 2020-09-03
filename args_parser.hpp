#ifndef ARGS_PARSER_HPP
#define ARGS_PARSER_HPP

// C++ std
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>


class ArgsParser {
public:
	ArgsParser(int argc = 0, const char* argv[] = nullptr);
	virtual ~ArgsParser(void) = default;
protected:
	std::unordered_set<std::string> m_args_set;
	std::unordered_map<std::string, std::string> m_args_map;

	std::size_t parse_size_t(const std::string& key, const std::string& name);
};


ArgsParser::ArgsParser(int argc, const char* argv[]) {
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
					m_args_set.insert(group);
				else
					m_args_map[last] = group;
				group = "";
				last = "";
			}
		} else if (arg.size() > 0 && (arg[0] == '"' || arg[0] == '\'')) {
			group += arg;
		} else if (arg.size() > 2 && arg.substr(0, 2) == "--") {
			std::string sub = arg.substr(2);
			if (m_args_map.count(sub) == 1)
				m_args_map.insert({sub, ""});
			else
				m_args_map[sub] = "";
			last = sub;
		} else if (arg.size() > 1 && arg[0] == '-') {
			for (std::string::size_type i = 1; i < arg.size(); ++i) {
				std::string sub = arg.substr(i, 1);
				if (m_args_map.count(sub) == 1)
					m_args_map.insert({sub, ""});
				else
					m_args_map[sub] = "";
				last = sub;
			}
		} else {
			if (last == "")
				m_args_set.insert(arg);
			else
				m_args_map[last] = arg;
			last = "";
		}
	}
	if (group.size() > 0) {
		group = group.substr(1);
		if (last == "")
			m_args_set.insert(group);
		else
			m_args_map[last] = group;
		group = "";
		last = "";
	}
}


std::size_t ArgsParser::parse_size_t(const std::string& key, const std::string& name) {
	std::string what;
	try {
		return std::stoull(m_args_map[key]);
	} catch (const std::invalid_argument& e) {
		if (key.size() == 1)
			what = "-" + key + ": invalid size_t for " + name;
		else
			what = "--" + key + ": invalid size_t for " + name;
	} catch (const std::out_of_range& e) {
		if (key.size() == 1)
			what = "-" + key + ": out of range size_t for " + name;
		else
			what = "--" + key + ": out of range size_t for " + name;
	}
	throw std::invalid_argument(what);
}


#endif // ARGS_PARSER_HPP