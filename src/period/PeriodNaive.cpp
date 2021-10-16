// Period Naive

#include "period.h"
using namespace std;

int PeriodNaive(string s){	//complessità O(n^2)
    int n = s.length();
    for(int p = 1; p <= n; p++){ //primo  ciclo con int p app[1,n]
        string s1 = s.substr(0, n-p);
        string s2 = s.substr(p, n);
        if (s1 == s2) {
            return p;
        }
    }
    return n;
}  
