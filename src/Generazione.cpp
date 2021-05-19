#include "Generazione.h"
#include <iostream>

//generazione std::stringa metodo A rimodernizzato
//metodo A
std::string generazioneStringaA(int n){

	std::string s(n,'a');  

	for (int i=0; i<n ; i++) {
		s[i] = 'a' + ((int)rand()) % 2;
	}

    return s;
}

//Metodo B
std::string generazioneStringaB(int n){

    std::string s(n,'a');  
	int q = ((int)rand()) % n + 1;		//generazione q appartiene {1,2,...,n}
	//std::cout<<"q: "<<q<<std::endl;		//stampa prova q -> periodo frazionario intero
    
	for(int j=0; j<q; j++){
		s[j] = 'a' + ((int)rand()) % 2;	// generazione std::stringa da 0 - q (nostro periodo frazionario)
	}
	for(int j=q; j<n; j++){
		s[j] = s[j % q];   				// completamento della std::stringa
	}

	//std::cout<<s<<std::endl;    //stampa prova metodo B
	return s;	
}
