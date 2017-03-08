#include "FormulaTypes.h"
#include "Formula.h"

struct ValCase {
	Valuation valuation;
	bool result;
};

struct Case {
	Formula *formula;
	std::string string;
	int deg;
	Variables vars;
	std::vector<ValCase> vals;
};

class Tester {
	int m_tested = 0;
	int m_passed = 0;
public:
	template<typename T>
	void compare(const T &result, const T &expected, const std::string &msg)
	{
		m_tested++;
		if (result == expected) {
			m_passed++;
		}
		else {
			std::cerr << "    Failed: " << msg << ":" << std::endl;
			std::cerr << "      got " << result << " expected: " << expected << std::endl;
		}
	}

	void compareF(const Formula *result, const Formula *expected, const std::string &msg)
	{
		m_tested++;
		if (result->equals(expected)) {
			m_passed++;
		}
		else {
			std::cerr << "    Failed: " << msg << ":" << std::endl;
			std::cerr << "      got " << result->toString() << " expected: " << expected->toString() << std::endl;
		}
	}

	void testToString(const Case &c) {
		compare(c.formula->toString(), c.string, "toString " + c.string);
	}

	void testDeg(const Case &c) {
		compare(c.formula->deg(), c.deg, "deg " + c.string);
	}

	void testVars(const Case &c) {
		compare(c.formula->vars(), c.vars, "vars " + c.string);
	}

	void testIsSatisfied(const Case &c)
	{
		for (const auto &vc : c.vals) {
			compare(c.formula->isSatisfied(vc.valuation), vc.result,
				"isSatisfied " + c.string + " in " + vc.valuation);
		}
	}

	void test(Formula *f, std::string str, const std::vector<ValCase> &cases)
	{
		std::cerr << "Testing " << str << std::endl;
		compare(f->toString(), str, "toString");
		for (const auto &c : cases) {
			std::cerr << "  Valuation " << c.valuation << std::endl;
			compare(f->isSatisfied(c.valuation), c.result, "isSatisfied");
		}
		delete f;
	}

	void status()
	{
		std::cerr << "TESTED " << m_tested << std::endl;
		std::cerr << "PASSED " << m_passed << std::endl;
		std::cerr << ( m_tested == m_passed ? "OK" : "ERROR" ) << std::endl;
	}
};


int main()
{
	Tester t;

	Valuation va1, va2;
	va1["a"] = true;  va2["a"] = false;

	std::vector<Valuation> valuations2;
	{ Valuation v; v["a"] = false; v["b"] = false ; valuations2.push_back(v); }
	{ Valuation v; v["a"] = false; v["b"] = true  ; valuations2.push_back(v); }
	{ Valuation v; v["a"] = true ; v["b"] = false ; valuations2.push_back(v); }
	{ Valuation v; v["a"] = true ; v["b"] = true  ; valuations2.push_back(v); }

	std::vector<Valuation> valuations3;
	{ Valuation v; v["a"] = false; v["b"] = false, v["c"] = false ; valuations3.push_back(v); }
	{ Valuation v; v["a"] = true ; v["b"] = false, v["c"] = false ; valuations3.push_back(v); }
	{ Valuation v; v["a"] = false; v["b"] = true , v["c"] = false ; valuations3.push_back(v); }
	{ Valuation v; v["a"] = true ; v["b"] = true , v["c"] = false ; valuations3.push_back(v); }
	{ Valuation v; v["a"] = false; v["b"] = false, v["c"] = true  ; valuations3.push_back(v); }
	{ Valuation v; v["a"] = true ; v["b"] = false, v["c"] = true  ; valuations3.push_back(v); }
	{ Valuation v; v["a"] = false; v["b"] = true , v["c"] = true  ; valuations3.push_back(v); }
	{ Valuation v; v["a"] = true ; v["b"] = true , v["c"] = true  ; valuations3.push_back(v); }


	std::vector<Case> cases{
		{ new Variable("a"), "a", 0, {"a"},
			{{va1,true}, {va2, false}}
		},
		{ new Negation(new Variable("a")), "-a", 1, {"a"},
			{
				ValCase{va1, false},
				ValCase{va2, true},
			}
		},
		{ new Conjunction( { new Variable("a"), new Variable("b") } ),
			"(a&b)", 1, {"a", "b"},
			{
				ValCase{valuations2[0], false},
				ValCase{valuations2[1], false},
				ValCase{valuations2[2], false},
				ValCase{valuations2[3], true},
			}
		},

		{ new Disjunction( { new Variable("a"), new Variable("b") } ),
			"(a|b)", 1, {"a", "b"},
			{
				ValCase{valuations2[0], false},
				ValCase{valuations2[1], true},
				ValCase{valuations2[2], true},
				ValCase{valuations2[3], true},
			}
		},
		{ new Implication( new Variable("a"), new Variable("b") ),
			"(a->b)", 1, {"a", "b"},
			{
				ValCase{valuations2[0], true},
				ValCase{valuations2[1], true},
				ValCase{valuations2[2], false},
				ValCase{valuations2[3], true},
			}
		},
		{ new Equivalence( new Variable("a"), new Variable("b") ),
			"(a<->b)", 1, {"a", "b"},
			{
				ValCase{valuations2[0], true},
				ValCase{valuations2[1], false},
				ValCase{valuations2[2], false},
				ValCase{valuations2[3], true},
			}
		},
		{ new Disjunction({
				new Negation(new Implication(new Variable("a"),new Variable("b"))),
				new Negation(new Implication(new Variable("b"),new Variable("a")))
			}),
			"(-(a->b)|-(b->a))", 5, {"a", "b"},
			{
				ValCase{valuations2[0], false},
				ValCase{valuations2[1], true},
				ValCase{valuations2[2], true},
				ValCase{valuations2[3], false},
			}
		},
		{ new Conjunction({
				new Implication(new Variable("a"),new Variable("b")),
				new Implication(new Negation(new Variable("a")),new Variable("c"))
			}),
			"((a->b)&(-a->c))", 4, {"a", "b", "c"},
			{
				ValCase{valuations3[0], false},
				ValCase{valuations3[1], false},
				ValCase{valuations3[2], false},
				ValCase{valuations3[3], true},
				ValCase{valuations3[4], true},
				ValCase{valuations3[5], false},
				ValCase{valuations3[6], true},
				ValCase{valuations3[7], true},
			}
		},
		{ new Equivalence(
				new Conjunction({
					new Variable("a"),
					new Negation(new Variable("b"))
				}),
				new Disjunction({
					new Variable("a"),
					new Implication(
						new Variable("b"),
						new Variable("a")
					)
				})
			),
			"((a&-b)<->(a|(b->a)))", 5, {"a", "b"},
			{
				ValCase{valuations2[0], false},
				ValCase{valuations2[1], true},
				ValCase{valuations2[2], true},
				ValCase{valuations2[3], false},
			}
		},
	};

	std::cerr << "Testing toString\n";
	for (const auto &c : cases)
		t.testToString(c);

	std::cerr << "Testing deg\n";
	for (const auto &c : cases)
		t.testDeg(c);

	std::cerr << "Testing vars\n";
	for (const auto &c : cases)
		t.testVars(c);

	std::cerr << "Testing isSatisfied\n";
	for (const auto &c : cases)
		t.testIsSatisfied(c);

	{
		std::cerr << "Testing Negation.originalFormula" << std::endl;
		Formula *a = new Variable("a");
		Formula *na = new Negation(a);
		Negation *nna = new Negation(na);
		t.compare(nna->originalFormula(), na, "Negation.originalFormula");
		delete nna;
	}

	{
		std::cerr << "Testing Implication rightSide / leftSide" << std::endl;
		Formula *a = new Variable("a");
		Formula *b = new Variable("b");
		Formula *na = new Negation(a);
		Implication *nab = new Implication(na, b);
		t.compare(nab->leftSide(), na, "Implication.leftSide");
		t.compare(nab->rightSide(), b, "Implication.rightSide");
		delete nab;
	}

	{
		std::cerr <<  "Testing Equivalence rightSide / leftSide" << std::endl;
		Formula *a = new Variable("a");
		Formula *b = new Variable("b");
		Formula *na = new Negation(a);
		Equivalence *nab = new Equivalence(na, b);
		t.compare(nab->leftSide(), na, "Equivalence.leftSide");
		t.compare(nab->rightSide(), b, "Equivalence.rightSide");
		delete nab;
	}

	t.status();
	return 0;
}
