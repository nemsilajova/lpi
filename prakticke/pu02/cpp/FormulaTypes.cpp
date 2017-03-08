#include "FormulaTypes.h"
#include <sstream>

/**
 * Pekny vypis ohodnotenia a mnoz. premennych.
 */
std::ostream& operator<< (std::ostream& stream, const Valuation &v)
{
	stream << "{ ";
	for(auto p : v) {
		stream << p.first << ": " << p.second << " ";
	}
	stream << "}";
	return stream;
}

std::ostream& operator<< (std::ostream& stream, const Variables &vs)
{
	stream << "{ ";
	for(const auto &v : vs) {
		stream << v << ", ";
	}
	stream << "}";
	return stream;
}

std::string operator+ (const std::string &s, const Valuation &v)
{
	std::stringstream ss;
	ss << s << v;
	return ss.str();
}
