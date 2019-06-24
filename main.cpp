#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <vector>
using namespace std;

class Rational {
    public:
    Rational() {
        this->_numerator = 0;
        this->_denominator = 1;
    }

    Rational(long numerator, long denominator) {
        if(denominator == 0){
            throw invalid_argument("mat");
        }
        if((numerator * denominator) < 0){
            denominator = abs(denominator);
            numerator = -abs(numerator);
        }else if(numerator < 0 || denominator < 0){
            denominator = abs(denominator);
            numerator = abs(numerator);
        }else if(numerator == 0){
            this->_numerator = 0;
            this->_denominator = 1;
        }
        long a = abs(numerator);
        long b = abs(denominator);
        while(a > 0 && b > 0){
            if(a > b){
                a = a % b;
            }else{
                b = b % a;
            }
        }
        this->_numerator = numerator / (a + b);
        this->_denominator = denominator / (a + b);
    }

    int Numerator() const {
        return this->_numerator;
    }

    int Denominator() const {
        return this->_denominator;
    }

private:
    int _numerator;
    int _denominator;
};

bool operator==(const Rational& first, const Rational& second){
    return first.Numerator() == second.Numerator() && first.Denominator() == second.Denominator();
}

Rational operator+(const Rational& first, const Rational& second){
    long rezultNumerator = (first.Numerator() * second.Denominator()) + (second.Numerator() * first.Denominator());
    long rezultDenominator = first.Denominator() * second.Denominator();
    return Rational{rezultNumerator,rezultDenominator};
}

Rational operator-(const Rational& first, const Rational& second){
    int rezultNumerator = first.Numerator() * second.Denominator() - second.Numerator() * first.Denominator();
    int rezultDenominator = first.Denominator() * second.Denominator();
    return Rational{rezultNumerator,rezultDenominator};
}

Rational operator*(const Rational& first, const Rational& second){
    return Rational{first.Numerator() * second.Numerator(), first.Denominator() * second.Denominator()};
}

Rational operator/(const Rational& first, const Rational& second){
    if(second.Numerator() == 0){
        throw domain_error("bad");
    }
    return Rational{first.Numerator() * second.Denominator(), second.Numerator() * first.Denominator()};
}

bool operator< (const Rational& first, const Rational& second){
    return first.Numerator() * second.Denominator() < second.Numerator() * first.Denominator();
}

bool operator> (const Rational& first, const Rational& second){
    return first.Numerator() * second.Denominator() < second.Numerator() * first.Denominator();
}


istream& operator>>(istream& is, Rational& rational){
    string rationalString;
    is >> rationalString;
    if(rationalString.empty()){
        return is;
    }
    int index = rationalString.find('/');
    int numerator = stoi(rationalString.substr(0, index));
    int denominator = stoi(rationalString.substr(index + 1));
    rational = Rational{numerator, denominator};
    return is;
}

ostream& operator<<(ostream& os, const Rational rational){
    os << rational.Numerator() << "/" << rational.Denominator();
    return os;
}

int main() {
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;
    return 0;
}
