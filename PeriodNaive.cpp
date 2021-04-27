// Period Naive
/*import java.util.Scanner;

public class PeriodNaive
{  
   public static int PeriodNaive(String s){   // complessità O(n^2)       
    int n =  s.length();
    for(int  p = 1;p< = n;p++){    // primo ciclo con int p app[1,n] 
        //System.out.println("ciclo "+p);
        for(int i = 0;i< = n-p;i++){ 
           String s1 =  s.substring(0,n-p);
           //System.out.println("s1: "+s1);
           String s2 = s.substring(p+i,n);
           //System.out.println("s2: "+s2);
           if(s2.equals(s1)){
               System.out.println("Trovato: "+s1);           
            return p;
            }
        }
       // System.out.println("----------------");
    }  
    return n;
    }

    public static void main(String args[]){
        Scanner in = new Scanner(System.in);
        String stringa =  in.nextLine();       
        int numero = PeriodNaive(stringa);
        System.out.println(numero);

        System.out.println("---New Test---"); 
        System.out.println(PeriodNaive("abca"));         
    }
}*/
#include <iostream>
using namespace std;


int PeriodNaive(string s){	//complessità O(n^2)
    int n = s.length();
    for(int p = 1; p <= n; p++){ //primo  ciclo con int p app[1,n]
        for(int i = 0; i <= n-p; i++){ 
            string  s1 = s.substr(0,n-p);
            string s2 = s.substr(p+i,n);
            if(s1 == s2){
                return p;
            }
        }	
    }
    return n;
}  

int main(){
    int c = PeriodNaive("abcabcabc");
    /*	string stringa;
    std::cin>> stringa;*/
    cout << c << endl;
    return 0;
}
