//metodo B
string generazioneStringaMetodoB(int n)
	 /* Nuovo seed per cambiare sequenza pseudo-casuale */  
	 	srand(time(0));	
    string s(n,'a');  
	int q = ((int)rand()) % n + 1;		//generazione q appartiene {1,2,...,n}
	//cout<<"q: "<<q<<endl;		//stampa prova q -> periodo frazionario intero
	for(int j= 0; j < q;j++){
		s[j]='a' + ((int)rand()) % 2;	// generazione stringa da 0 - q (nostro periodo frazionario)
	}
	for(int j = q;j<n;j++){
		s[j]=s[j % q];   				// completamento della stringa
	}
	//cout<<s<<endl;    //stampa prova metodo B
	return s;	
}

