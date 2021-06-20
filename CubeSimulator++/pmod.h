#pragma once
inline int pmod(int a, int b)
{
    int ret = a % b; return ret >= 0 ? ret : ret + b;
}