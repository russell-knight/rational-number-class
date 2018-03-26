
namespace rational
{

int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}

class Rational
{

  public:
	Rational(int numerator, int denominator)
	{
		n = numerator;
		d = denominator;
	}

	int numerator() const
	{
		return n;
	}

	int denominator() const
	{
		return d;
	}

	void simplify()
	{
		int gcd = this->gcd();
		n = n / gcd;
		d = d / gcd;

		if (d < 0)
		{
			d = -1 * d;
			n = -1 * n;
		}
	}
	// Overloaded operators (+ - * / < > == !=)

  private:
	int n, d; // Numerator & Denominator

	int gcd()
	{
		return rational::gcd(n, d);
	}
};
}