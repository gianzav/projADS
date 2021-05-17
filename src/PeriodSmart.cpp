#include "period.h"
#include <iostream>
using namespace std;

int PeriodSmart(string s) {  //calcolo bordo
    int n = s.length();
    int r[n+1];
    r[1] = 0;           

    for (int i = 1; i < n; i++) {
        //cout<<s.substr(i+1,1)<<endl; 
        int z = r[i];

        while((z > 0) && (s.substr(i,1) != s.substr(z,1))) {
            z = r[z];
        }      

        if (s.substr(i,1) == s.substr(z,1)) {
            r[i+1] = z+1;
        } else {
            r[i+1] = 0;
        }            
    }           
    return n-r[n]; // r[n] bordo max di S (n-r[n] = periodo minimo)
}


/* int main() { */
/*     string stringa = "abcabcabca"; */
/* 	//std::cin>> stringa; */
/* 	int freq = PeriodSmart(stringa); */
/* 	cout << freq; */
/* 	return 0; */
/* } */
