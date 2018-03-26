

class Rational {

	public:
		Rational(int numerator, int denominator)
		{
			n= numerator;
			d=denominator;
		}
		
		int numerator() const
		{
			return n;
		}

		int denominator() const
		{
		return d;
		}

		int GCD(int a, int b)
		{
			return b==0?a:GCD(b,a%b);
		}
		
		// Simplify method (reducing rational to simplest form)
		// Overloaded operators (+ - * / < > == !=) 


	private:
		int n, d; // Numerator & Denominator
}