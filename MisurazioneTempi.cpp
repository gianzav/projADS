#include <chrono>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace std::chrono;

double getResolution() {
    steady_clock::time_point start = steady_clock::now();
    steady_clock::time_point end;
    do {
        end = steady_clock::now();
    } while (start == end);
    typedef duration<double, seconds::period> duration;
    return duration_cast<seconds>(end - start).count();
}

string generazioneStringa(int n) {
    string s = "";
    string p;
    for (int i = 0; i < n; i++) {
        p = 'a' + ((int)rand()) % 2;
        s = s + p;
    }
    return s;
}

// PERIOD SMART
int PeriodSmart(string s) { // calcolo bordo
    int n = s.length();
    int r[n + 1];
    r[1] = 0;
    for (int i = 1; i < n; i++) {
        int z = r[i];
        while ((z > 0) && (s.substr(i, 1) != s.substr(z, 1))) {
            z = r[z];
        }
        if (s.substr(i, 1) == s.substr(z, 1)) {
            r[i + 1] = z + 1;
        } else {
            r[i + 1] = 0;
        }
    }
    return n - r[n]; // r[n] bordo max di S (n-r[n] = periodo minimo)
}

int misurazioneTempiMedi() {
    int nMin = 1000;
    int nMax = 500000;                         // 500'000
    double A = nMin;                           // ricavo A
    double B = exp((log(nMax) - log(A)) / 99); // ricavo B
    double m;
    int n, k, periodo;
    double R;                       // Risoluzione  clock
    double Emax = 0.001;            // Errorre relativo massimo ammesso
    steady_clock::time_point start; // = clock start;
    steady_clock::time_point end;   // = clock end;
    steady_clock::duration diff;
    double tn;
    double conversione;
    double nseconds;

    /* Nuovo seed per cambiare sequenza pseudo-casuale */
    srand(time(0));

    for (int j = 0; j <= 99; j++) {
        R = getResolution();
        m = A * pow(B, j);
        n = (int)m;
        // cout<<n<<endl; //stampa lunghezza n, con distribuzione esponenziale tra
        // 1000 e 500000
        // string StringaGenerata =generazioneStringa(n);   // posso calcolare il
        // tempo medio della generazione
        start = steady_clock::now();
        k = 0;

        do {
            string StringaGenerata = generazioneStringa(n);
            periodo = PeriodSmart(StringaGenerata);
            end = steady_clock::now();
            k = k + 1;
            diff = end - start;
            conversione = double(diff.count());
        } while (conversione < ((R / Emax) + R)); // end-start -> ^kx^   //sottrarre il tempo
        // medio della generazione per
        tn = (conversione) / k; // tn = x^ con errore relativo <= Emax

        /*cout<<tn<<endl;*/     // cout<<tn/pow(10,9)<<" grandezza n: "<<n<<endl;

        nseconds = tn * steady_clock::period::num / steady_clock::period::den; // conversione in secondi

        // //double(diff.count())
        
        cout << "Tempo (sec): " << nseconds << " grandezza: " << n << endl;
    }

    return 0;
}

int main() {
    cout << "---New Test---" << endl;
    // string prova=generazioneStringa(5);// generazione  stringa fatta
    // cout<<prova;
    misurazioneTempiMedi();

    return 0;
}
