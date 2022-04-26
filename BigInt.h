#ifndef BIGINT_H_INCLUDED
#define BIGINT_H_INCLUDED

#include <bits/stdc++.h>
#define endl '\n'

typedef long long ll;

using namespace std;

struct myVector
{
    ll* arr;
    int sz;
    int alloc;

    void init();

    void push_back (const ll &a);

    void insert (const ll &a);

    ll& operator[] (int i) const;

    ll back() const;

    void pop_back ();

    void clear ();

    int size() const;

    bool empty() const;

    ~myVector();

};

struct BigInt {
    myVector z = {NULL, 0, 0};
    int sign;

    BigInt();

    BigInt(ll v);

    BigInt(const string &s);

    BigInt(const BigInt &v);

    void operator=(const BigInt &v);

    void operator=(ll v);

    BigInt operator+(const BigInt &v) const;

    BigInt operator-(const BigInt &v) const;

    void operator+=(const BigInt &v);
    void operator-=(const BigInt &v);

    BigInt operator*(const ll &v) const;

    BigInt operator*(const BigInt &v) const;


    BigInt operator/(const BigInt &v) const;

    void shift();
    void RShift();

    void operator*=(const BigInt &v);

    void operator/=(const BigInt &v);

    bool operator<(const BigInt &v) const;

    bool operator>(const BigInt &v) const;
    bool operator<=(const BigInt &v) const;
    bool operator>=(const BigInt &v) const;
    bool operator==(const BigInt &v) const;
    bool operator!=(const BigInt &v) const;

    void trim();
    BigInt operator-() const;

    BigInt abs() const;

    void read(const string &s);
};

ostream& operator<<(ostream &stream, const BigInt &v);

BigInt add (const BigInt &a, const BigInt &b);
BigInt subtract (const BigInt &a, const BigInt &b);
BigInt multiply (const BigInt &a, const BigInt &b);
BigInt divide (const BigInt &a, const BigInt &b);
void print (const BigInt &a);

#endif // BIGINT_H_INCLUDED
