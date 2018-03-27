#include <limits>
#include <stdexcept>

namespace rational
{

template <class T>
T gcd(T a, T b)
{
	return b == 0 ? a : gcd(b, a % b);
}

template <class T>
simplify(T &numerator, T &denominator)
{
	T gcd = rational::gcd(numerator, denominator);
	numerator = numerator / gcd;
	denominator = denominator / gcd;

	if (denominator < 0)
	{
		denominator = -1 * denominator;
		numerator = -1 * numerator;
	}
}

class Rational
{

  public:
	Rational(int numerator, int denominator);

	int numerator() const
	{
		return _numerator;
	}

	int denominator() const
	{
		return _denominator;
	}

	void simplify()
	{
		rational::simplify(_numerator, _denominator);
	}

	// Overloaded operators (+ - * / < > == !=)

	Rational operator*(const Rational &other) const
	{ //cast to long long to avoid overflow
		long long n1 = this->_numerator;
		long long d1 = this->_denominator;
		long long n2 = other._numerator;
		long long d2 = other._denominator;

		auto numerator = n1 * n2;
		auto denominator = d1 * d2;

		rational::simplify(numerator, denominator);

		if (abs(numerator) > std::numeric_limits<int>::max() || abs(denominator) > std::numeric_limits<int>::max())
		{
			throw std::overflow_error("integer overflow error");
		}

		return Rational(numerator, denominator);
	}

	Rational operator/(const Rational &other) const
	{
		auto n = other.numerator;
		auto d = other.denominator;
		return *this * Rational(d, n);
	}

	Rational operator+(const Rational &other) const
	{ //cast to long long to avoid overflow
		long long n1 = this->_numerator;
		long long d1 = this->_denominator;
		long long n2 = other._numerator;
		long long d2 = other._denominator;

		auto numerator = n1 * d2 + n2 * d1;
		auto denominator = d1 * d2;

		auto gcd = rational::gcd(numerator, denominator);
		numerator = numerator / gcd;
		denominator = denominator / gcd;

		if (abs(numerator) > std::numeric_limits<int>::max() || abs(denominator) > std::numeric_limits<int>::max())
		{
			throw std::overflow_error("integer overflow error");
		}

		return Rational(numerator, denominator);
	}

	Rational operator-(const Rational &other) const
	{
		return *this + other * Rational(-1, 1);
	}

	bool operator==(const Rational &other) const
	{
		auto a = *this;
		auto b = other;
		a.simplify();
		b.simplify();
		return a.numerator == b.numerator && a.denominator == b.denominator;
	}

	bool operator != (const Rational & other) const
	{
		return !(*this==other);
	}

	bool operator<(const Rational &other) const
	{
		auto a = *this;
		auto b = other;
		a.simplify();
		b.simplify();
		return a.numerator < b.numerator;
	}

	bool operator>(const Rational &other) const
	{
		return other<*this;
	}

	bool operator<=(const Rational &other) const
	{
		return !(other<*this);
	}

	bool operator>=(const Rational &other) const
	{
		return !(*this<other);
	}

  private:
	int _numerator;
	int _denominator;
};
}