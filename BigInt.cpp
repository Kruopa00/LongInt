#include <bits/stdc++.h>
#define endl '\n'
#include "BigInt.h"

using namespace std;

typedef long long ll;

const ll base = 1e9;
const int base_digits = 9;


void myVector::init()
{
    arr = NULL;
    sz = alloc = 0;
}

void myVector::push_back (const ll &a)
{
    if (alloc == 0)
    {
        alloc = 10;
        arr = (ll*) calloc(alloc, sizeof (ll));
        if (arr == NULL) cout << "mem leak";
    }
    if (sz == alloc)
    {
        alloc *= 2;
        arr = (ll*) realloc(arr, sizeof (ll) * alloc);
        if (arr == NULL) cout << "mem leak";
    }
    *(arr + sz) = a;
    sz++;
}

void myVector::insert (const ll &a)
{
    if (sz == alloc)
    {
        alloc *= 2;
        arr = (ll*) realloc(arr, sizeof (ll) * alloc);
        if (arr == NULL) cout << "mem leak";
    }
    for (int i = sz - 1; i >= 0; i--)
        *(arr + i + 1) = *(arr + i);
    *arr = a;
    sz++;
}

ll& myVector::operator[] (int i) const
{
    return *(arr + i);
}

ll myVector::back() const
{
    return *(arr + sz - 1);
}

void myVector::pop_back ()
{
    sz--;
}

void myVector::clear ()
{
    free(arr);
    init();
}

int myVector::size() const
{
    return sz;
}

bool myVector::empty() const
{
    return sz == 0;
}

myVector::~myVector()
{
    free(arr);
}

BigInt::BigInt() :
    sign(1)
{
}

BigInt::BigInt(ll v)
{
    *this = v;
}

BigInt::BigInt(const string &s)
{
    read(s);
}

BigInt::BigInt(const BigInt &v)
{
    sign = v.sign;
    z.sz = v.z.sz;
    z.alloc = v.z.alloc;
    z.arr = (ll*) calloc(z.alloc, sizeof (ll));
    memcpy(z.arr, v.z.arr, sizeof (ll) * z.alloc);
}

void BigInt::operator=(const BigInt &v)
{
    sign = v.sign;
    z.sz = v.z.sz;
    z.alloc = v.z.alloc;
    free(z.arr);
    z.arr = (ll*) calloc(z.alloc, sizeof (ll));
    memcpy(z.arr, v.z.arr, sizeof (ll) * z.alloc);
}

void BigInt::operator=(ll v)
{
    sign = 1;
    if (v < 0)
        sign = -1, v = -v;
    z.clear();
    for (; v > 0; v = v / base)
        z.push_back(v % base);
}

BigInt BigInt::operator+(const BigInt &v) const
{
    if (sign == v.sign)
    {
        BigInt res = v;

        for (int i = 0, carry = 0; i < (int) max(z.size(), v.z.size()) || carry; ++i)
        {
            if (i == (int) res.z.size())
                res.z.push_back(0);
            res.z[i] += carry + (i < (int) z.size() ? z[i] : 0);
            carry = res.z[i] >= base;
            if (carry)
                res.z[i] -= base;
        }
        return res;
    }
    return *this - (-v);
}

BigInt BigInt::operator-(const BigInt &v) const
{
    if (sign == v.sign)
    {
        if (abs() >= v.abs())
        {
            BigInt res = *this;
            for (int i = 0, carry = 0; i < (int) v.z.size() || carry; ++i)
            {
                res.z[i] -= carry + (i < (int) v.z.size() ? v.z[i] : 0);
                carry = res.z[i] < 0;
                if (carry)
                    res.z[i] += base;
            }
            res.trim();
            return res;
        }
        return -(v - *this);
    }
    return *this + (-v);
}

void BigInt::operator+=(const BigInt &v)
{
    *this = *this + v;
}
void BigInt::operator-=(const BigInt &v)
{
    *this = *this - v;
}

BigInt BigInt::operator*(const ll &v) const
{
    BigInt res = *this;

    if(v == 0) return 0;
    if(v < 0) res.sign *= -1;
    for(int i = 0; i < res.z.size(); ++i)
    {
        res.z[i] *= v;
    }
    ll carry = 0;
    for(int i = 0; i < res.z.size(); ++i)
    {
        res.z[i] += carry;
        carry = res.z[i] / base;
        res.z[i] %= base;
    }
    if(carry)
    {
        res.z.push_back(carry);
    }
    return res;
}

BigInt BigInt::operator*(const BigInt &v) const
{
    if((*this).z.sz < v.z.sz) return v * (*this);
    BigInt res = 0;
    if(v.z.empty()) return 0;
    if(z.empty()) return 0;
    if(v.z.size() == 1 && v.z[0] == 0) return 0;
    if(z.size() == 1 && z[0] == 0) return 0;

    res += *this * v.z.back();

    for (int i = v.z.size()-2; i >= 0; --i)
    {
        res.z.insert((ll)0);
        //cout << res << endl;
        //cout << *this << " " << v.z[i] << endl;
        res += *this * v.z[i];
    }

    if(sign == v.sign)
    {
        res.sign = 1;
    }
    else res.sign = -1;

    return res;
}


BigInt BigInt::operator/(const BigInt &v) const
{
    BigInt ret = BigInt(0);
    ret.sign = (sign == v.sign) ? 1 : -1;
    BigInt p = abs(); //2
    BigInt q = v.abs(); //1

    if (p < q) return 0;
    assert(v != 0);

    BigInt res = q;
    int diff = 0;
    while (p > res) res.shift(), diff++;
    for (int i = diff; i >= 0; i--)
    {
        res = q;
        for (int j = 0; j < i; j++) res.shift();

        //cout << q.z.arr << " " << res.z.arr << " " << endl;

        int cnt = 0;
        //cout << p << " " << res << endl;
        while (p - res >= 0)
        {
            cnt++;
            p -= res;
        }
        ret.shift();
        ret += BigInt(cnt);

        res.RShift();
    }

    if(sign == v.sign)
    {
        res.sign = 1;
    }
    else res.sign = -1;

    return ret;
}

void BigInt::shift()
{
    int carry = 0;
    for (int i = 0; i < z.size(); i++)
    {
        if (i == z.size() - 1)
        {
            if (z[i] < 100000000)
                z[i] = z[i] * 10 + carry;
            else
            {
                z.push_back(0);
                int new_carry = z[i] / 100000000;
                z[i] = (z[i] % 100000000) * 10 + carry;
                carry = new_carry;
            }
        }
        else
        {
            int new_carry = z[i] / 100000000;
            z[i] = (z[i] % 100000000) * 10 + carry;
            carry = new_carry;
        }
    }
}

void BigInt::RShift()
{
    int carry = 0;
    if (z.empty()) return;

    if (z.back() < 10) carry = z.back(), z.pop_back();
    for (int i = z.size() - 1; i >= 0; i--)
    {
        int new_carry = z[i] % 10;
        z[i] = (z[i] / 10) + carry * 100000000;
        carry = new_carry;
    }
}

void BigInt::operator*=(const BigInt &v)
{
    return *this = *this * v;
}

void BigInt::operator/=(const BigInt &v)
{
    return *this = *this / v;
}

bool BigInt::operator<(const BigInt &v) const
{
    if (sign != v.sign)
        return sign < v.sign;
    if (z.size() != v.z.size())
        return z.size() * sign < v.z.size() * v.sign;
    for (int i = z.size() - 1; i >= 0; i--)
        if (z[i] != v.z[i])
            return z[i] * sign < v.z[i] * sign;
    return false;
}

bool BigInt::operator>(const BigInt &v) const
{
    return v < *this;
}
bool BigInt::operator<=(const BigInt &v) const
{
    return !(v < *this);
}
bool BigInt::operator>=(const BigInt &v) const
{
    return !(*this < v);
}
bool BigInt::operator==(const BigInt &v) const
{
    return !(*this < v) && !(v < *this);
}
bool BigInt::operator!=(const BigInt &v) const
{
    return *this < v || v < *this;
}

void BigInt::trim()
{
    while (!z.empty() && z.back() == 0)
        z.pop_back();
    if (z.empty())
        sign = 1;
}

BigInt BigInt::operator-() const
{
    BigInt res = *this;
    res.sign = -sign;
    return res;
}

BigInt BigInt::abs() const
{
    BigInt res = *this;
    res.sign *= res.sign;
    return res;
}

void BigInt::read(const string &s)
{
    sign = 1;
    z.clear();
    int pos = 0;
    while (pos < (int) s.size() && (s[pos] == '-' || s[pos] == '+'))
    {
        if (s[pos] == '-')
            sign = -sign;
        ++pos;
    }
    for (int i = s.size() - 1; i >= pos; i -= base_digits)
    {
        int x = 0;
        for (int j = max(pos, i - base_digits + 1); j <= i; j++)
            x = x * 10 + s[j] - '0';
        z.push_back(x);
    }
    trim();
}

ostream& operator<<(ostream &stream, const BigInt &v)
{
    if (v.sign == -1)
        stream << '-';
    stream << (v.z.empty() ? 0 : v.z.back());
    for (int i = (int) v.z.size() - 2; i >= 0; --i)
        stream << setw(base_digits) << setfill('0') << v.z[i];
    return stream;
}

BigInt add (const BigInt &a, const BigInt &b)
{
    return a + b;
}

BigInt subtract (const BigInt &a, const BigInt &b)
{
    return a - b;
}

BigInt multiply (const BigInt &a, const BigInt &b)
{
    return a * b;
}

BigInt divide (const BigInt &a, const BigInt &b)
{
    return a / b;
}

void print (const BigInt &a)
{
    if (a.sign == -1)
        cout << '-';
    cout << (a.z.empty() ? 0 : a.z.back());
    for (int i = (int) a.z.size() - 2; i >= 0; --i)
        cout << setw(base_digits) << setfill('0') << a.z[i];
    cout << endl;
}
