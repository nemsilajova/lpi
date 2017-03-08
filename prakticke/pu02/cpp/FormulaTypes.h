#pragma once
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

typedef std::unordered_map<std::string, bool> Valuation;
typedef std::unordered_set<std::string> Variables;

/**
 * Pekny vypis ohodnotenia a mnoz. premennych.
 */
std::ostream& operator<< (std::ostream& stream, const Valuation &v);
std::ostream& operator<< (std::ostream& stream, const Variables &vs);
std::string operator+ (const std::string &s, const Valuation &v);
