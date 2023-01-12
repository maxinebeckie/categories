/// chapter 4 - Kheisli categories

// example: logging. Shared global state in imperative/OOP languages like C, and Kheisli categories
// in functional languagess.

string logger;

bool negate(bool b) {
	logger += "Not so! ";
	return !b;
}

// functional approach:

pair<bool, string> negate(bool b, string logger) {
	return make_pair(!b, logger + "Not so! ");
}

// this memoization is problematic because ... idk this book is confusing

// log aggregated between function calls:

pair<bool, string> negate(bool b) {
	return make_pair(!b, "Not so! ");
}
// slightly more realistic example:

string toUpper(string s) {
	string result;
	int (*toupperp)(int) = &toupper; //overload toupper      :( ?
	transform(begin(s), end(s), back_inserter(result), toupperp);
	return result;
}

// toUpper is a function from string to string that maps lowercase characters to uppercase.

vector<string> toWords(string s) {
	return words(s);
}

vector<string> words(string s) {
	vector<string> result{""};
	for (auto i = begin(s); i != end(s); ++i)
	{
		if (isspace(*i))
			result.push_back("");
		else 
			result.back() += i;
	}
	return result;
}

// toWords takes a string and splits it into words. 
/let's embellish the toWords and toUpper functions from notes.c

template<class A>
using Writer = pair<A, string>;

Writer<string> toUpper(string s) {
	string result;
	int (*toupperp)(int) = &toupper;
	transform(begin(s), end(s), back_inserter(result), toupperp);
	return make_pair(result, "toUpper ");
}

Writer<vector<string>> toWords(string s) {
	return make_pair(words(s), "toWords );
}

// we want to compose these functions. how?

Writer<vector<string>> process(string s) {
	auto p1 = toUpper(s);
	auto p2 = toWords(p1.first);
	return make_pair(p2.first, p1.second + p2.second);
}

// so, this works, but it's not great. We must abstract function composition.

// hereforthafter: the Writer category.

pair<bool, string> isEven(int n) {
	return make_pair(n % 2 == 0, "isEven");
}

pair<bool, string> isOdd(int n) {
	pair<bool, string> p1 = isEven(n);
	pair<bool, string> p2 = negate(p1.first);
	return make_pair(p2.first, p1.second + p2.second);
}

// how we compose: 
//
// 	- execute embellished fn corr to first morphism
// 	- extract first component of result, pass to embellished fn corr to second morphism
// 	- concatenate logs of both results
// 	- return new pair, first component of final result with concatenated logs

template<class A, class B, class C>
function<Writer<C>(A)> compose(function<Writer<B>(A)> m1,
		function<Writer<C>(A)> m2)
{
	return [m1, m2](A x) {
		auto p1 = m1(x);
		auto p2 = m2(p1.first);
		return make_pair(p2.first, p1.second + p2.second);
	};
}

Writer<vector<string>> process(string s) {
	return compose<string, string, vector<string>>(toUpper, toWords)(s);
}

// lot of noisy type syntax.

// following code req's C++14-compliant cpp compiler with generalized lambda functions with
// return type deduction

auto const compose = [](auto m1, auto m2) {
	return [m1, m2](auto x) {
		auto p1 = m1(x);
		auto p2 = m2(p1.first);
		return make_pair(p2.first, p1.second + p2.second);
	};
};

// under this new defn process is 

Writer<vector<string>> process(string s) {
	return compose(toUpper, toWords)(s);
}

// now that we have composition, next is identity

Writer<A> identity(A);

template<class A> Writer<A> identity(A x) {
	return make_pair(x, "");
}

//so this is the category. Instead of string concatenation, you can use any monoid. 
