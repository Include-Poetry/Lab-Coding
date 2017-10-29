#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>

#define lli long long int
using namespace std;

string EGTRevision = "Epigenetics mini-tools v0.1";
string CadenaOligos;
vector<int> valores;
vector<pair <int, int>> OligosRaw, OligosFinal;
// TM exacta para el oligo
int ExactTM;
// Tamaño del oligo como rango
int ntMin, ntMax;
// Grado de libertad en número
int RangoLib;
// Dirección del oligo, 1 para downstream, -1 para upstream, 0 para doble
int Direccion;

bool ValidarBooleano(){
	string ans;

	while (true){
		cin >> ans;

		if (ans == "S" || ans == "s"){	// Repuesta positiva (Sí)
			cout << endl;
			return true;
		}
		if (ans == "N" || ans == "n"){ // Respuesta negativa (No)
			cout << endl;
			return false;
		}
		// Otras respuestas no válidas
		cout << endl 
			 << "    Ingresa 'S' o 's' para indicar 'S\241' " << endl
			 << "    Ingresa 'N' o 'n' para indicar 'No'" << endl
			 << "    Tu respuesta: ";
	}
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

void PrintOligosRaw(){
	cout << "    Cantidad de oligos que cumplen el TM y tama\244o: " << OligosRaw.size() << endl
		 << "    Los oligos encontrados son:" << endl
		 << endl
		 << "    | Ubicaci\242n | Tama\244o | Oligo |" << endl;
	for (int i=0; i<OligosRaw.size(); i++){
		int start = OligosRaw.at(i).first;
		int end = OligosRaw.at(i).second;
		cout << "| " << start+1 << " - " << end << " | " << (start+1) - end << " | ";
		for (int j=start; j<end; j++){
			cout << CadenaOligos.at(j) << " |";
		}
		cout << endl;
	}
	return;
}

void GuardarOligos(){
	string NombreArch, NombreIntern;
	cout << "    Ingresa el nombre (sin espacios) del nuevo archivo: ";
	cin >> NombreArch;
	NombreIntern = NombreArch;
	NombreArch += ".txt";
	cout << "    Guardando " << NombreArch << " ..." << endl;
	// Creamos la variable que será nuestro archivo
	ofstream archivo;
	// Abrimos nuestro archivo, está listo para escribir en él
	archivo.open(NombreArch);

	archivo << "Búsqueda de oligos - archivo " << NombreIntern << endl
			<< endl
			<< "Secuencia procesada:" << endl
			<< CadenaOligos << endl
			<< endl
			<< "Parámetros de la búsqueda:" << endl
			<< "TM: " << ExactTM << endl
			<< "Rango de tamaño: " << ntMin << "-" << ntMax << endl
			<< "Grado de libertad: " << RangoLib << endl
			<< "Dirección de búsqueda: ";
	if (Direccion == 1){
		archivo << "Downstream - CGXXXXXXXXXXXXXXXXXXXX" << endl;
	} else if (Direccion == 0){
		archivo << "Doble - CGXXXXXXXXXXXXXXXXXXGC" << endl;
	} else if (Direccion == -1){
		archivo << "Upstream - XXXXXXXXXXXXXXXXXXXXGC" << endl;
	}
	archivo	<< endl
			<< "Cantidad de oligos encontrados: " << OligosFinal.size() << endl;
	if (OligosFinal.size()){
		archivo << "| Ubicación | Tamaño | Oligo |" << endl;
		for (int i=0; i<OligosFinal.size(); i++){
			int start = OligosFinal.at(i).first;
			int end = OligosFinal.at(i).second;
			archivo << "| " << start+1 << " - " << end << " | " << end - start << " | ";
			for (int j=start; j<end; j++){
				archivo << CadenaOligos.at(j);
			}
			archivo << " |" << endl;
		}
		archivo << endl;
	}

	archivo << endl
			<< "Datos sin formato: " << endl
			<< endl
			<< ExactTM << endl
			<< ntMin << " " << ntMax << endl
			<< RangoLib << endl
			<< Direccion << endl
			<< OligosFinal.size() << endl;
	if (OligosFinal.size()){
		for (int i=0; i<OligosFinal.size(); i++){
			int start = OligosFinal.at(i).first;
			int end = OligosFinal.at(i).second;
			archivo << start+1 << " " << end << " "<< end - start << " ";
			for (int j=start; j<end; j++){
				archivo << CadenaOligos.at(j);
			}
			archivo << endl;
		}
		archivo << endl;
	}
	archivo << "Análisis realizado con " << EGTRevision << " - rivel_co" << endl
			<< "Fin del reporte";
	archivo.close();
	cout << "    Guardado finalizado" << endl;
	return;
}

void PrintOligosFinales(){
	cout << "    Cantidad de oligos que cumplen los par\240metros dados: " << OligosFinal.size() << endl
		 << endl;
	if (OligosFinal.size()){
		cout << "    | Ubicaci\242n | Tama\244o | Oligo |" << endl;
		for (int i=0; i<OligosFinal.size(); i++){
			int start = OligosFinal.at(i).first;
			int end = OligosFinal.at(i).second;
			cout << "    | " << start+1 << " - " << end << " | " << end - start << " | ";
			for (int j=start; j<end; j++){
				cout << CadenaOligos.at(j);
			}
			cout << " |" << endl;
		}
		cout << endl;
	}
	return;
}

void ProcesarFinales(){
	OligosFinal.clear();
	do{
		cout << "    Indica el grado de libertad (n\243mero entero): ";
		cin >> RangoLib;
	} while (RangoLib < 0);

	do{
		cout << "    Indica la direcci\242n del oligo:" << endl
			 << "       1 para downstream, -1 para upstream, 0 para doble: ";
		cin >> Direccion;
	} while (Direccion < -1 || Direccion > 1);
	
	// Para ingresar una nueva pareja, de uso común
	pair<int, int> nuevo;

	// Dirección downstream - CGXXXXXXXXXXXXXXXXXXXX
	if (Direccion == 1){
		for (int i=0; i < OligosRaw.size(); i++){
			// Extraemos un oligo del RAW
			int ini = OligosRaw.at(i).first;
			int fin = OligosRaw.at(i).second;
			// Procesaremos para todos los grados de libertad
			for (int k=0; k <= RangoLib; k++){
				int ini2 = ini;
				// Iteramos para revisar el nt según el grado de libertad actual
				for (int j=0; j<k; j++){
					ini2++;
				}
				// Revisamos si es un oligo válido
				if (valores.at(ini2) == 4 && valores.at(ini2+1) == 4){
					nuevo.first = ini;
					nuevo.second = fin;
					OligosFinal.push_back(nuevo);
					break; // break para no repetir oligos al cambiar de grado de libertad
				}
			}
		}
	}
	// Dirección upstream - XXXXXXXXXXXXXXXXXXXXGC
	if (Direccion == -1){
		for (int i=0; i < OligosRaw.size(); i++){
			// Extraemos un oligo del RAW
			int ini = OligosRaw.at(i).first;
			int fin = OligosRaw.at(i).second - 1;
			// Procesaremos para todos los grados de libertad
			for (int k=0; k <= RangoLib; k++){
				int fin2 = fin;
				// Iteramos para revisar el nt según el grado de libertad actual
				for (int j=0; j<k; j++){
					fin2--;
				}
				// Revisamos si es un oligo válido
				if (valores.at(fin2) == 4 && valores.at(fin2-1) == 4){
					nuevo.first = ini;
					nuevo.second = fin + 1;
					OligosFinal.push_back(nuevo);
					break;
				}
			}
		}
	}
	// Dirección doble - CGXXXXXXXXXXXXXXXXXXGC
	if (Direccion == 0){
		for (int i=0; i < OligosRaw.size(); i++){
			// Extraemos un oligo del RAW
			int ini = OligosRaw.at(i).first;
			int fin = OligosRaw.at(i).second - 1;
			// Procesaremos para todos los grados de libertad
			for (int k=0; k <= RangoLib; k++){
				int fin2 = fin;
				int ini2 = ini;
				// Iteramos para revisar el nt según el grado de libertad actual
				for (int j=0; j<k; j++){
					fin2--;
					ini2++;
				}
				// Revisamos que cumpla en ambos extremos con el mismo grado de libertad
				if (valores.at(fin2) == 4 && valores.at(fin2-1) == 4 && valores.at(ini2) == 4 && valores.at(ini2+1) == 4){
					nuevo.first = ini;
					nuevo.second = fin + 1;
					OligosFinal.push_back(nuevo);
					break;
				}
				// Revisamos que cumpla con grado de libertad en sólo el primer extremo
				if (valores.at(fin) == 4 && valores.at(fin-1) == 4 && valores.at(ini2) == 4 && valores.at(ini2+1) == 4){
					nuevo.first = ini;
					nuevo.second = fin + 1;
					OligosFinal.push_back(nuevo);
					break;
				}
				// Revisamos que cumpla con grado de libertad en sólo el segundo extremo
				if (valores.at(fin2) == 4 && valores.at(fin2-1) == 4 && valores.at(ini) == 4 && valores.at(ini+1) == 4){
					nuevo.first = ini;
					nuevo.second = fin + 1;
					OligosFinal.push_back(nuevo);
					break;
				}
			}
		}
	}
	return;
}

void GenerarOligosRaw(){
	OligosRaw.clear();
	bool sigue = true;
	do{
		cout << "    Ingresa la TM que deber\240n tener los oligos: ";
		cin >> ExactTM;
	} while (ExactTM < 0);

	do{
		ntMin = ntMax = 0;
		cout << "    Ingresa el tama\244o m\241nimo del oligo: ";
		cin >> ntMin;
		cout << "    Ingresa el tama\244o m\240ximo del oligo: ";
		cin >> ntMax;
	} while (ntMin > ntMax);
	

	int TMnow = 0, ini, fin;
	fin = ini = 0;

	int cantNow;
	pair<int, int> nuevo;
	// Realizamos la suma telescópica
	for (int i=0; fin < CadenaOligos.size() && ini < CadenaOligos.size(); i++){
		// Iteramos sólo el primer oligo y actualizamos después
		while (TMnow < ExactTM && fin < CadenaOligos.size()){
			TMnow += valores.at(fin);
			fin++;
		}
		// Si se cumple el TM de forma exacta...
		if (TMnow == ExactTM){
			// Revisamos el largo del oligo
			cantNow = (fin+1)-(ini+1);
			// Si entra en el rango lo guardamos
			if (cantNow >= ntMin && cantNow <= ntMax){
				nuevo.first = ini;
				nuevo.second = fin;
				OligosRaw.push_back(nuevo);
			}
		}
		// Eliminamos el primer valor agregado
		TMnow -= valores.at(ini);
		ini++;
		// Eliminamos los últimos dos agregados
		TMnow -= valores.at(fin-1) + valores.at(fin-2);
		fin -= 2;
	}
	return;
}

void ModoDeUso(){
	Cabecera("Modo de uso");
	cout << "    El programa se basa en analizar secuencias de nucle\242tidos" << endl
		 << "    de DNA, por lo que se espera que cada cadena se componga de" << endl
		 << "    los siguiente posibles caracteres:" << endl
		 << "    - a \242 A -> Adenina" << endl
		 << "    - g \242 G -> Guanina" << endl
		 << "    - c \242 C -> Citosina" << endl
		 << "    - t \242 T -> Timina" << endl
		 << endl
		 << "    Uso de cada funci\242n:" << endl
		 << endl
		 << "    Calcular un TM est\240ndar" << endl
		 << "       Al recibir una secuencia de nucle\242tidos se calcula" << endl
		 << "       el valor de TM utilizando las siguientes conversiones:" << endl
		 << "       - A = T = 2               - C = G = 4" << endl
		 << "       La funci\242n devuelve el resultado de sumar todas" << endl
		 << "       las conversiones de nucle\242tidos." << endl
		 << endl
		 << "    Generar cadena reverso-complementaria" << endl
		 << "       Dada una secuencia de nucle\242tidos la funci\242n" << endl
		 << "       devuelve la cadena reverso complementaria seg\243n los" << endl
		 << "       apareamientos can\242nicos de Watson-Crick. Por ejemplo:" << endl
		 << "       La cadena AGTCTAGATAC se convierte a GTATCTAGACT" << endl
		 << endl
		 << "    Generar cadena reversa" << endl
		 << "       Se devuelve la cadena reversa a la cadena ingresada." << endl
		 << "       Por ejemplo:" << endl
		 << "       La cadena AGTCTAGATAC se convierte a CATAGATCTGA" << endl
		 << endl
		 << "    Generar cadena complementaria" << endl
		 << "       La funci\242n devuelve la cadena complementaria seg\243n" << endl
		 << "       los apareamientos can\242nicos de Watson-Crick." << endl
		 << "       Por ejemplo:" << endl
		 << "       La cadena AGTCTAGATAC se convierte a TCAGATCTATG" << endl
		 << endl
		 << "    Buscador de oligos" << endl
		 << "       Dada una secuencia de nucle\242tidos la funci\242n devuelve" << endl
		 << "       todos los posibles oligos o primers que se pueden obtener" << endl
		 << "       de esa entrada. La funci\242n requiere los par\240metros:" << endl
		 << "       - TM: La TM que deber\240n tener los oligos" << endl
		 << "       - Tama\244o m\241nimo: Tama\244o m\241nimo del oligo" << endl
		 << "       - Tama\244o m\240ximo: Tama\244o m\240ximo del oligo" << endl
		 << "       - Grado de libertad: Indica la cantidad m\240xima de" << endl
		 << "         nucle\242tidos que pueden haber antes de la primera" << endl
		 << "         isla CyG del oligo" << endl
		 << "       - Direcci\242n del oligo: Indica la direcci\242n del oligo" << endl
		 << "         en base a la isla CyG que se busca. Se deber\240 indicar" << endl
		 << "         con un valor num\202rico el sentido de la b\243squeda:" << endl
		 << "         - 1 -> Downstream: Encuentra oligos como CGXXXXXXXXXXXXXXXXXXXX" << endl
		 << "         - 0 -> Doble: Encuentra oligos como CGXXXXXXXXXXXXXXXXXXGC" << endl
		 << "         - -1 -> Upstream: Encuentra oligos como XXXXXXXXXXXXXXXXXXXXGC" << endl
		 << "       Al finalizar puedes guardar los resultados de la b\243squeda en" << endl
		 << "       un archivo de texto que se genera en la misma carpeta de donde" << endl
		 << "       se ejecut\242 el programa." << endl
		 << endl
		 << "       No se recomiendan cadenas con m\240s de 4000 caracteres en " << endl
		 << "       esta versi\242n, por las limitaciones nativas en la entrada por " << endl
		 << "       la consola de Windows." << endl
		 << endl
		 << endl
		 << " Para mayor informaci\242n ingresar a:" << endl
		 << " https://github.com/Include-Poetry/Lab-Coding/tree/master/Epigenetics-mini-tools" << endl
		 << endl
		 << endl;
	return;
}

void About(){
	cout << endl
		 << "    Este programa ha sido dise\244ado como una herramienta de apoyo" << endl
		 << "    y de forma temporal para resolver peque\244as necesidades en la" << endl
		 << "    creaci\242n de primers." << endl
		 << endl
		 << "    Especialmente programada para el laboratorio de:" << endl
		 << "    - Fisiolog\241a animal y vegetal - UASLP" << endl
		 << endl
		 << "    Elaborada por amor al arte por rivel_co" << endl
		 << endl; 
}

int main(){
	string entrada;
	bool menu = true;
	int opc;
	while(menu){
		Cabecera("Men\243");
		cout << "    1- Calcular un TM est\240ndar" << endl
			 << "    2- Generar cadena reverso-complementaria" << endl
			 << "    3- Generar cadena reversa" << endl
			 << "    4- Generar cadena complementaria" << endl
			 << "    5- Buscador de oligos" << endl
			 << endl
			 << "    6- Modo de uso" << endl
			 << "    7- Sobre este programa" << endl
			 << "    8- Salir" << endl
			 << endl
			 << "    N\243mero de tu elecci\242n: ";
		cin >> opc;
		switch(opc){
			case 1:
				cout << "    Ingresa la cadena a evaluar:" << endl << "    ";
				cin >> entrada;
				cout << endl 
					 << "    La TM est\240ndar:" << endl
					 << "    Entrada: " << entrada << endl
					 << "    TM: " << CalcularTM(entrada) << endl
					 << "    Tama\244o: " << entrada.size() << endl
					 << endl
					 << "    Presiona cualquier tecla para volver...";
				system("pause>>null");
				break;
			case 2:
				cout << "    Ingresa la cadena a evaluar:" << endl << "    ";
				cin >> entrada;
				cout << endl
					 << "    Cadena reverso-complementaria:" << endl 
					 << "    Entrada: " << entrada << endl 
					 << "    Reverso-complementaria: " << ReversoComplementaria(entrada) << endl
					 << "    Tama\244o: " << entrada.size() << endl
					 << endl
					 << "    Presiona cualquier tecla para volver...";
				system("pause>>null");
				break;
			case 3:
				cout << "    Ingresa la cadena a evaluar:" << endl << "    ";
				cin >> entrada;
				cout << endl
					 << "    Cadena reversa:" << endl 
					 << "    Entrada: " << entrada << endl 
					 << "    Reversa: " << Reverso(entrada) << endl
					 << "    Tama\244o: " << entrada.size() << endl
					 << endl
					 << "    Presiona cualquier tecla para volver...";
				system("pause>>null");
				break;
			case 4:
				cout << "    Ingresa la cadena a evaluar:" << endl << "    ";
				cin >> entrada;
				cout << endl
					 << "    Cadena complementaria:" << endl 
					 << "    Entrada: " << entrada << endl 
					 << "    Complementaria: " << Complementaria(entrada) << endl
					 << "    Tama\244o: " << entrada.size() << endl
					 << endl
					 << "    Presiona cualquier tecla para volver...";
				system("pause>>null");
				break;
			case 5:
				cout << "    Ingresa la secuencia a analizar:" << endl << "    ";
				cin >> CadenaOligos;
				// Convertimos la entrada a valores numéricos
				cout << endl;
				valores.clear();
				for (int i=0; i<CadenaOligos.size(); i++){
					valores.push_back( ValorParaTM(CadenaOligos.at(i)) );
				}
				GenerarOligosRaw();
				ProcesarFinales();
				cout << endl;
				PrintOligosFinales();
				cout << "    \250Deseas guardar el an\240lisis? (S/N): ";
				if (ValidarBooleano()){
					GuardarOligos();
				}
				cout << "    Presiona cualquier tecla para volver...";
				system("pause>>null");
				break;
			case 6:
				ModoDeUso();
				cout << "    Presiona cualquier tecla para volver...";
				system("pause>>null");
				break;
			case 7:
				About();
				cout << "    Presiona cualquier tecla para volver...";
				system("pause>>null");
				break;
			case 8:
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
