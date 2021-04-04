#include<iostream>

template<bool condition, class L1, class L2>
struct IF
{
    typedef L1 result;
};
template<class L1, class L2>
struct IF<false, L1, L2>
{
    typedef L2 result;
};

template<int numerator_, int denominator_>
struct Double {
    enum {
        numerator = numerator_,
        denominator = denominator_
    };
    operator const double() const
    {
        return (double)numerator_ / (double)denominator_;
    }
};

template<class N1, class N2>
struct ADD {
    enum {
        numerator = N1::numerator * N2::denominator + N1::denominator * N2::numerator,
        denominator = N2::denominator * N1::denominator
    };
    typedef Double<numerator, denominator> result;
    operator const double() const
    {
        return (double)numerator / (double)denominator;
    }
};

template<int n>
struct PI {
private:
    typedef typename IF<n % 2 == 1, Double<-1, 2 * n + 1>, Double<1, 2 * n + 1> >::result An;
    typedef ADD<An, typename PI<n - 1>::result> Sum;
public:
    typedef typename ADD<An, typename PI<n - 1>::result>::result result;
    enum {
        numerator = Sum::numerator,
        denominator = Sum::denominator
    };
    operator const double() const
    {
        return 4 * (double)numerator / (double)denominator;
    }

};

template<>
struct PI<0>
{
    typedef Double<1, 1> result;
    enum {
        numerator = 1,
        denominator = 1
    };
    operator const double() const
    {
        return 4 * (double)numerator / (double)denominator;
    }
};

int main()
{
    typedef PI<9> pi;
    std::cout << pi() << std::endl;
    return 0;
}