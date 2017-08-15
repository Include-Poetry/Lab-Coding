#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define lli long long int

string EGTRevision = "Epigenetics mini-tools v0.1-alpha";

void About(){
	cout << endl
		 << "    Este programa ha sido dise\244ado como una herramienta de apoyo" << endl
		 << "    y de forma temporal para resolver peque\244as necesidades en la" << endl
		 << "    creaci\242n de primers." << endl
		 << endl 
		 << "    Esta versi\242n es una beta, no apta para producci\242n." << endl
		 << endl
		 << "    Elaborada por amor al arte por rivel_co" << endl
		 << endl; 
}

void Cabecera(string Subtitulo){
	system("cls");
	cout << "    ----------           " << EGTRevision << "           ----------" << endl
		 << endl
		 << "                         " << Subtitulo << endl
		 << endl;
}

int ValorParaTM(char c){
	if (c == 'C' || c == 'G' || c == 'c' || c == 'g'){
		return 4;
	}
	if (c == 'A' || c == 'T' || c == 'a' || c == 't'){
		return 2;
	}
	return 0;
}


int CalcularTM(string cadena){
	lli total = 0;
	
	for (int i=0; i < cadena.size(); i++){
		total += ValorParaTM(cadena.at(i));
	}
	
	return total;
}

string ReversoComplementaria(string cadena){
	string final;
	for(int i=cadena.size() - 1; i >= 0; i--){
		switch(cadena.at(i)){
			case 'A':
				final.push_back('T');
				break;
			case 'a':
				final.push_back('t');
				break;
			case 'T':
				final.push_back('A');
				break;
			case 't':
				final.push_back('a');
				break;
			case 'C':
				final.push_back('G');
				break;
			case 'c':
				final.push_back('g');
				break;
			case 'G':
				final.push_back('C');
				break;
			case 'g':
				final.push_back('c');
				break;
		}
	}
	return final;
}

string Reverso(string cadena){
	string final;
	for(int i=cadena.size() - 1; i >= 0; i--){
		final.push_back(cadena.at(i));
	}
	return final;
}

string Complementaria(string cadena){
	string final;
	for(int i=0; i < cadena.size(); i++){
		switch(cadena.at(i)){
			case 'A':
				final.push_back('T');
				break;
			case 'a':
				final.push_back('t');
				break;
			case 'T':
				final.push_back('A');
				break;
			case 't':
				final.push_back('a');
				break;
			case 'C':
				final.push_back('G');
				break;
			case 'c':
				final.push_back('g');
				break;
			case 'G':
				final.push_back('C');
				break;
			case 'g':
				final.push_back('c');
				break;
		}
	}
	return final;
}

int main(){
	string entrada;
	bool menu = true;
	int opc;
	while(menu){
		Cabecera("Menu");
		cout << "    1- Calcular un TM est\240ndar" << endl
			 << "    2- Generar cadena reverso-complementaria" << endl
			 << "    3- Generar cadena reversa" << endl
			 << "    4- Generar cadena complementaria" << endl
			 << "    5- Sobre este programa" << endl
			 << "    6- Salir" << endl
			 << endl
			 << "    N\243mero de tu elecci\242n: ";
		cin >> opc;
		switch(opc){
			case 1:
				cout << "    Ingresa la cadena a evaluar:" << endl << "    ";
				cin >> entrada;
				cout << "    La TM est\240ndar de " << endl
					 << "    " << entrada << " es: " << endl
					 << "    " << CalcularTM(entrada) << endl
					 << endl
					 << "    Presiona cualquier tecla para volver...";
				system("pause>>null");
				break;
			case 2:
				cout << "    Ingresa la cadena a evaluar:" << endl << "    ";
				cin >> entrada;
				cout << "     La cadena reverso-complementaria de:" << endl 
					 << "    " << entrada << " es: " << endl 
					 << "    " << ReversoComplementaria(entrada) << endl
					 << endl
					 << "    Presiona cualquier tecla para volver...";
				system("pause>>null");
				break;
			case 3:
				cout << "    Ingresa la cadena a evaluar:" << endl << "    ";
				cin >> entrada;
				cout << "     La cadena reversa de:" << endl 
					 << "    " << entrada << " es: " << endl 
					 << "    " << Reverso(entrada) << endl
					 << endl
					 << "    Presiona cualquier tecla para volver...";
				system("pause>>null");
				break;
			case 4:
				cout << "    Ingresa la cadena a evaluar:" << endl << "    ";
				cin >> entrada;
				cout << "     La cadena complementaria de:" << endl 
					 << "    " << entrada << " es: " << endl 
					 << "    " << Complementaria(entrada) << endl
					 << endl
					 << "    Presiona cualquier tecla para volver...";
				system("pause>>null");
				break;
			case 5:
				About();
				cout << "    Presiona cualquier tecla para volver...";
				system("pause>>null");
				break;
			case 6:
				menu = false;
				break;
			default:
				cout << "     Ingresa una opción v\240lida" << endl 
					 << endl
					 << "    Presiona cualquier tecla para volver...";
				system("pause>>null");
				break;
		}
	}
	
	return 0;
}
