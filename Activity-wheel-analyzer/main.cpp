/*	Programa auxiliar en el análisis del conteo de vueltas en ruedas
	Especialmente programado para la estudiante de maestría Teresa Belem
	Programado por Ricardo Velázquez Contreras
	www.include-poetry.com/Equipo/rivel_co/
*/
#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;

// Matriz para meter las capturas, funcionará hasta antes del año 2050
long long int captura[50][13][32][24];
// 1 - Año del 2000
// 2 - Mes
// 3 - Día
// 3 - Horas en reloj de 24 hrs

// Se guardan las fechas en periodo o individuales en las que hubo actividad
string DiasConvertidos[500];
int VueltasDia[500];
// Variable que marca la hora 0 en la conversión
int HoraCero;

long long int convertidos[500][24];
// 1 - Dia para el ratón
// 2 - Hora de su dia segun su 0

// Arreglo para cuando se ingresan carpetas desordenadas
string CarpetasDes[200];
// Arreglo para los ratones
string Ratones[200];
// Arreglo para las ruedas
string Ruedas[200];
// Cantidad de ratones y ruedas
int RatonesCant;

// Fechas iniciales y finales para optimizar
int DiaF, MesF, AnoF, DiaI, MesI, AnoI;
// Corrección de tiempo para horas
int correct;

// Control de las carpetas para periodo y la carpeta actual
string CarpetaIni, CarpetaFin, CarpetaAct;

// Días totales en conversión
int totales;
// Ratón y rueda procesándose
string RatonPro, RuedaPro;

void Inicializar(){		// Reseteamos los arreglos que guardan las actividades
	for (int i=0; i<200; i++){
		for (int j=0; j<24; j++){
			convertidos[i][j] = 0;
		}
	}
	for (int i=AnoI; i <= AnoF; i++){
		for (int j = MesI; j <= MesF; j++){
			for (int k = DiaI; k <= DiaF; k++){
				for (int l = 0; l < 24; l++){
					captura[i][j][k][l] = 0;
				}
			}
		}
	}
	for (int i=0; i<500; i++){
		VueltasDia[i] = 0;
	}
	DiasConvertidos[0] = "";
	return;
}

string Formato(int x, int n){	// Para dar formato a los Números tipo reloj
	stringstream ss;
	ss << setw(n) << setfill('0') << x;
	string s = ss.str();
	return s;
}

string SiguienteCarpeta(){		// Determinación de siguiente fecha a partir de CarpetaAct
	string aux;		// Cadena auxiliar de formación
	int cambio;		// Para el control de duración de mes + 1
	
	aux = CarpetaAct.substr(0, 2);		// Extracción del día de CarpetaAct
	int dia = stoi(aux);
	aux = CarpetaAct.substr(2, 2);		// Extracción del mes de CarpetaAct
	int mes = stoi(aux);
	aux = CarpetaAct.substr(4, 4);		// Extracción del año de CarpetaAct
	int ano = stoi(aux);
	
	string final;	// Variable que tendrá el valor final

	// Determinación del cambio según la duración de cada mes + 1
	if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12){
		cambio = 32;
	} else if (mes == 2){
		if (ano%4 == 0) cambio = 30;
		else cambio = 29;
	} else cambio = 31;

	ano += ( mes + ((dia+1)/cambio) )/13;	// Determinación del nuevo año
	mes = ( mes + ((dia+1)/cambio) )%13;	// Determinación del nuevo mes
	dia = (dia+1)%cambio;					// Determinación del nuevo día
	if (!dia) dia++;	// Corrección de día 0
	if (!mes) mes++;	// Corrección de mes 0

	// Formamos la cadena final
	final = Formato(dia,2) + Formato(mes,2) + Formato(ano, 4);
	CarpetaAct = final;	// Actualizamos la carpeta actual
	return final;	// Devolvemos la nueva carpeta
}

void Captura(string FileName){	// Función que captura los datos desde la ruta FileName
	// Limpiamos la pantalla
	system("cls");

	// Señalización para el usuario
	cout << "     ------------------- Convertidor de conteos -------------------" << endl
		 << endl
		 << "     Carpeta a procesar: " << CarpetaAct << endl
		 << "     Rat\242n " << RatonPro << endl
		 << "     Rueda " << RuedaPro << endl
		 << endl;
	
	// Creamos la referencia al archivo
	ifstream archivo;
	archivo.open(FileName);

	// Leemos las primeras cuatro líneas que no sirven
	string temp;
	for (int i=0; i<4; i++){
		archivo >> temp;
	}
	
	// En caso de que haya que adelantar o atrasar en horas
	cout << "     Correcci\242n de hora (0 si no hay que corregir): ";
	cin >> correct;
	
	string parte;
	while(archivo >> parte){	// Mientras se puedan leer datos
		/* ------------ Lectura del archivo ------------ */
		archivo >> parte;		// Hora
		string tiempo;
		tiempo = parte.substr(0,2);
		int hora = stoi(tiempo) + correct;
		tiempo = parte.substr(3,2);
		int minuto = stoi(tiempo);
		tiempo = parte.substr(6,2);
		int segundo = stoi(tiempo);

		archivo >> parte;		// Fecha
		string fecha;
		fecha = parte.substr(3,2);
		int dia = stoi(fecha);
		fecha = parte.substr(0,2);
		int mes = stoi(fecha);
		fecha = parte.substr(8,2);
		int ano = stoi(fecha);
	
		archivo >> parte;		// Segundos del archivo
		/* ------------ Fin lectura del archivo ------------ */

		/* ------------ Registro de las horas ------------ */		
		captura[ano][mes][dia][hora]++;		// Actualizamos la actividad de esa fecha y hora

		if (ano < AnoI){		// Evaluamos la primera fecha
			AnoI = ano;
			MesI = mes;
			DiaI = dia;
		} else if (ano == AnoI){
			if (mes < MesI){
				MesI = mes;
				DiaI = dia;
			} else if (mes == MesI){
				if (dia < DiaI){
					DiaI = dia;
				}
			}
		}
		if (ano > AnoF){		// Evaluamos la última fecha
			AnoF = ano;
			MesF = mes;
			DiaF = dia;
		} else if (ano == AnoF){
			if (mes > MesF){
				MesF = mes;
				DiaF = dia;
			} else if (mes == MesF){
				if (dia > DiaF){
					DiaF = dia;
				}
			}
		}
	} // Terminamos de leer

	// Cerramos el archivo
	archivo.close();
	
	return;
}

void Conversion(bool todo){		// Convertimos los datos de la captura en la hora del ratón
	int dia = 1;			// Posición del arreglo donde comenzamos a guardar la actividad
	int hora;				// Las horas para el arreglo de convertidos
	int NowD, NowM, NowY;	// Indicadores de fecha procesándose
	bool cambio;			// Evalúa si existen cambios en actividad
	bool sigue;				// Control para el ciclo
	string SigFecha, aux,	// Control de siguiente fecha y un auxiliar de cadenas
		   Respaldo = CarpetaAct;	// Ya que modificaremos CarpetaAct varias veces

	HoraCero = 8;		// Determinación de la hora 0 a convertir

	NowD = DiaI, NowM = MesI, NowY = AnoF;	// Valor inicial de fecha a procesar

	sigue = true;
	while (sigue){
		sigue = NowD != DiaF || NowM != MesF || NowY != AnoF;

		if (!todo) cambio = false;		// Evaluación de cambio

		// Guardamos las fechas en que se evalúo la actividad
		DiasConvertidos[dia-1] += " " + Formato(NowD, 2) + '-' + Formato(NowM, 2) + '-' + Formato(NowY, 2);
		DiasConvertidos[dia] = Formato(NowD, 2) + '-' + Formato(NowM, 2) + '-' + Formato(NowY, 2);

		// Determinación de actividad en la primera mitad del día
		for (int l = 0, hora = 16; l < HoraCero; l++, hora++){
			convertidos[dia][hora] = captura[NowY][NowM][NowD][l];
			VueltasDia[dia] += captura[NowY][NowM][NowD][l];	// Guardamos para el contador
			if (!todo && captura[NowY][NowM][NowD][l]) cambio = true;	// Determinación de cambios
		}

		if (!todo){		// Para determinación de cambios
			if (cambio) dia++;
		} else dia++;	// Cambiamos de día a guardar conversión

		// Determinación de actividad en la segunda mitad del día
		for (int l = HoraCero, hora = 0; l < 24; l++, hora++){
			convertidos[dia][hora] = captura[NowY][NowM][NowD][l];
			VueltasDia[dia] += captura[NowY][NowM][NowD][l];	// Guardamos para el contador
		}

		// Calculamos la siguiente fecha que debe ser procesada
		NowY += 2000;
		CarpetaAct = Formato(NowD, 2) + Formato(NowM, 2) + Formato(NowY, 4);
		SigFecha = SiguienteCarpeta();
		aux = SigFecha.substr(0, 2);		// Extracción del día de SigFecha
		NowD = stoi(aux);
		aux = SigFecha.substr(2, 2);		// Extracción del mes de SigFecha
		NowM = stoi(aux);
		aux = SigFecha.substr(6, 2);		// Extracción del año de SigFecha
		NowY = stoi(aux);
	}
	
	CarpetaAct = Respaldo;	// Restauramos el valor de CarpetaAct
	totales = dia;			// La cantidad total de días será la cantidad de cambios de día

	return;
}

void GuardarConteos(string carpeta){	// Guardamos los conteos
	int NowD, NowM, NowY;	// Controles de fecha procesándose
	bool sigue;				// Control del ciclo
	string aux, SigFecha,	// Auxiliar de cadena y temporal de siguiente fecha
		   resp = CarpetaAct;	// Respaldo del valor de CarpetaAct
	NowD = DiaI, NowM = MesI, NowY = AnoF;	// Valor inicial de fecha a procesar
	// Creación de archivo y definición de ruta
	ofstream salida;
	string ruta = "Convertidos";
	CreateDirectory(ruta.c_str(), NULL);
	ruta += '/' + carpeta;
	CreateDirectory(ruta.c_str(), NULL);
	ruta += "/Raton" + RatonPro;
	CreateDirectory(ruta.c_str(), NULL);
	ruta += "/Rueda" + RuedaPro + " - conteos.txt";

	// Abrimos el archivo
	salida.open(ruta);
	// Mensaje al usuario
	salida << "Datos de conteo con horario normal (civil)" << endl
		   << "Ratón " << RatonPro << " - Rueda " << RuedaPro << endl
		   << endl;	

	sigue = true;
	while (sigue){	// Iteramos en todas las fechas
		sigue = NowD != DiaF || NowM != MesF || NowY != AnoF;

		salida << "Año " << NowY << " mes " << NowM << " día " << NowD << endl;
		for (int l = 0; l < 24; l++){	// Control de horas
			salida << "Hora " << l << " vueltas " << captura[NowY][NowM][NowD][l] << endl;
		}
		salida << endl;

		NowY += 2000;	// Calibramos para el correcto funcionamiento de SiguienteCarpeta()
		CarpetaAct = Formato(NowD, 2) + Formato(NowM, 2) + Formato(NowY, 4);
		SigFecha = SiguienteCarpeta();		// Calculamos la siguiente fecha como cadena
		// Evaluamos como enteros y reasignamos
		aux = SigFecha.substr(0, 2);		// Extracción del día de SigFecha
		NowD = stoi(aux);
		aux = SigFecha.substr(2, 2);		// Extracción del mes de SigFecha
		NowM = stoi(aux);
		aux = SigFecha.substr(6, 2);		// Extracción del año de SigFecha
		NowY = stoi(aux);
	}
	CarpetaAct = resp;	// Restauramos el valor de CarpetaAct
	salida.close();	// Cerramos el archivo
	return;
}

void GuardarConvertidos(string carpeta){	// Guardamos los convertidos con carpeta de fecha 'carpeta'
	// Definición de salida y de ruta
	ofstream salida;
	string ruta = "Convertidos";
	CreateDirectory(ruta.c_str(), NULL);
	ruta += '/' + carpeta;
	CreateDirectory(ruta.c_str(), NULL);
	ruta += "/Raton" + RatonPro;
	CreateDirectory(ruta.c_str(), NULL);
	ruta += "/Rueda" + RuedaPro + ".txt";
	// Abrimos el archivo
	salida.open(ruta);
	// Mensaje al usuario
	salida << "Datos de conteo tras conversión de hora civil 08:00 -> 00:00 ratón" << endl
		   << "Ratón " << RatonPro << " - Rueda " << RuedaPro << endl
		   << endl;

	for (int i=1; i<=totales; i++){	// Control de los días de actividad
		// Mensaje al usuario
		salida << "En los días: " << DiasConvertidos[i-1] << endl
			   << "Hora | Vueltas" << endl;
		for (int j=0; j<24; j++){	// Control de las horas
			salida << j << " " << convertidos[i][j] << endl;
		}
		salida << "Vueltas totales en el día: " << VueltasDia[i] << endl;
		salida << endl;
	}
	// Se cierra el archivo
	salida.close();
	return;
}

void MostrarConvertidos(){	// Mostramos los convertidos en la consola
	// Limpiamos la pantalla
	system("cls");
	// Mensaje al usuario
	cout << "     ------------------- Convertidor de conteos -------------------" << endl
		 << endl
		 << "     Datos de conteo tras conversi\242n" << endl
		 << "     Rat\242n " << RatonPro << " - Rueda " << RuedaPro << endl
		 << endl;

	for (int i=1; i<=totales; i++){		// Control de días de actividad
		// Mensaje al usuario con fecha o periodo que se registro
		cout << "     En los d\241as: " << DiasConvertidos[i-1] << endl;
		for (int j=0; j<24; j++){		// Control de horas
			cout << "     Hora " << j << " vueltas " << convertidos[i][j] << endl;
		}
		cout << "     Vueltas totales en el d\241a: " << VueltasDia[i] << endl
			 << endl;
	}
	// Mensaje al usuario por pausa
	cout << "     Presiona cualquier tecla para continuar...";
	system("pause>>null");
	return;
}

void TipoCaptura(int vez){		// Definimos el tipo de captura según el parámetro 'vez'
	string FileName, Destino;	// Variables de control
	bool continua = true;		// Variable de control para carpetas ordenadas
	char opc;	// Variable para pedir opciones S/N
	switch(vez){
		case 1:		// Varias carpetas ordenadas
			// Se ingresan todos los datos asociados al análisis
			cout << "     Nombre de carpeta de inicio: ";
			cin >> CarpetaIni;
			cout << "     Nombre de carpeta de fin: ";
			cin >> CarpetaFin;
			cout << "     Ingresa la cantidad de ratones/ruedas a analizar: ";
			cin >> RatonesCant;
			for (int i=0; i<RatonesCant; i++){
				cout << "     N\243mero de raton (" << i+1  << "/" << RatonesCant << ") a procesar: ";
				cin >> Ratones[i];
				cout << "     N\243mero de rueda (" << i+1  << "/" << RatonesCant << ") a procesar: ";
				cin >> Ruedas[i];
			}
			// Por cada ratón se exploran todas las carpetas para usar una sola matriz de captura
			for (int j=0; j<RatonesCant; j++){
				CarpetaAct = CarpetaIni;	// Le primer carpeta será la inicial
				DiaF = MesF = AnoF = 0;		// Se neutralizan los valores que serán máximos
				DiaI = MesI = AnoI = 5000;	// Se neutralizan los valores que serán mínimos
				continua = true;	// Regulación del ciclo 
				RatonPro = Ratones[j];	// Actualizamos el ratón que estamos analizando
				RuedaPro = Ruedas[j];	// Actualizamos la rueda que estamos analizando
				while (continua){
					// Si la carpeta actual es igual a la final entonces será la última por procesar
					if (CarpetaAct == CarpetaFin) continua = false;
					// Creamos el nombre del archivo a capturar
					FileName = CarpetaAct + "/Raton" + RatonPro + "/Rueda" + RuedaPro + ".txt";
					Captura(FileName);	// Capturamos desde esa ruta
					CarpetaAct = SiguienteCarpeta();	// Determinamos la siguiente carpeta
				}
				// Determinamos el destino de guardado según el periodo
				Destino = CarpetaIni + '-' + CarpetaFin;
				/*cout << endl
					 << "     \250Convertir la actividad del rat\242n " << endl 
					 << "               en todo el periodo de tiempo ingresado? (S/N): ";
				cin >> opc;
				if (opc == 'S' || opc == 's') Conversion(true);
				else Conversion(false);*/
				Conversion(true);	// Convertimos en todo el periodo
				GuardarConvertidos(Destino);	// Guardamos en el destino los convertidos
				GuardarConteos(Destino);		// Guardamos en el destino los conteos
				MostrarConvertidos();			// Mostramos los convertidos
				Inicializar();		// Reseteamos los conteos
			}
			break;
		case 2:		// Varias carpetas desordenadas
			// Ingresamos los datos para el análisis
			cout << "     Ingresa la cantidad de carpetas a procesar: ";
			int cant;
			cin >> cant;
			cout << "     Ingresa los nombres de las carpetas a procesar" << endl;
			Destino = "";
			for (int i=0; i<cant; i++){
				cout << "     Carpeta(" << i+1 << "/" << cant << "): ";
				cin >> CarpetasDes[i];
				// El nombre del destino tendrá todos los nombres de las carpetas
				Destino += CarpetasDes[i];
				if (i+1 < cant) Destino += ',';
			}
			cout << "     Ingresa la cantidad de ratones/ruedas a analizar: ";
			cin >> RatonesCant;
			for (int i=0; i<RatonesCant; i++){
				cout << "     N\243mero de raton (" << i+1  << "/" << RatonesCant << ") a procesar: ";
				cin >> Ratones[i];
				cout << "     N\243mero de rueda (" << i+1  << "/" << RatonesCant << ") a procesar: ";
				cin >> Ruedas[i];
			}
			// Procesamos todas las carpetas por cada ratón a analizar
			for (int i=0; i<RatonesCant; i++){
				DiaF = MesF = AnoF = 0;		// Neutralizamos los valores que serán máximos
				DiaI = MesI = AnoI = 5000;	// Neutralizamos los valores que serán mínimos
				RatonPro = Ratones[i];		// Definimos el ratón a procesar
				RuedaPro = Ruedas[i];		// Definimos la rueda a procesar
				for (int j=0; j<cant; j++){		// Iteramos con cada carpeta
					CarpetaAct = CarpetasDes[j];	// Actualizamos la carpeta actual con las carpetas ingresadas
					// Determinamos la ruta de captura y capturamos
					FileName = CarpetaAct + "/Raton" + RatonPro + "/Rueda" + RuedaPro + ".txt";
					Captura(FileName);
				}
				/*cout << endl
					 << "     \250Convertir la actividad del rat\242n " << endl 
					 << "               en todo el periodo de tiempo ingresado? (S/N): ";
				cin >> opc;
				if (opc == 'S' || opc == 's') Conversion(true);
				else Conversion(false);*/
				Conversion(true);	// Convertimos en todo el periodo
				GuardarConvertidos(Destino);	// Guardamos los convertidos en el destino
				GuardarConteos(Destino);		// Guardamos los conteos en el destino
				MostrarConvertidos();			// Mostramos los convertidos
				Inicializar();		// Reseteamos los arreglos
			}
			break;		
	}
}

void SobreElPrograma(){
	// Limpiamos la pantalla
	system("cls");

	cout << "     ------------------- Convertidor de conteos -------------------" << endl
		 << endl
		 << endl
		 << "                     Sobre la funci\242n del programa" << endl
		 << endl
		 << "     El programa determina la cantidad de vueltas que un rat\242n" << endl
		 << "     dio en una rueda por cada hora, a partir de una determinada " << endl
		 << "     fecha y hora establecidas por el programa de registro." << endl
		 << "     Los datos se convierten del horario civil (normal) a un" << endl
		 << "     horario en que las 08:00hrs son la hora 00:00" << endl
		 << endl
		 << endl
		 << "                      Sobre los archivos de entrada" << endl
		 << endl
		 << "     El programa espera analizar una estructura de carpetas como:" << endl
		 << "        [Fecha]/RatonX/RuedaY.txt" << endl
		 << "     en donde [Fecha] tiene el formato: DiaMesA\244o como 31122017" << endl
		 << "     y donde X y Y son n\243meros enteros." << endl
		 << "     Este archivo ejecutable debe estar en la misma carpeta en donde" << endl
		 << "     est\202n las carpetas de fecha." << endl
		 << endl
		 << endl
		 << "                      Sobre los datos de los archivos" << endl
		 << endl
		 << "     El programa espera leer en los archivos algo como: " << endl
		 << "        SEXO:" << endl
		 << "        EDAD:" << endl
		 << "        TRMT:" << endl
		 << "        CEPA:" << endl
		 << "        1 08:00:00 03-17-2017 100" << endl
		 << "     Las primeras cuatro l\241neas no tienen ning\243n espacio ( )" << endl
		 << "     A partir de quinta l\241nea todas siguen el mismo formato donde" << endl
		 << "     cada l\241nea tiene cuatro atributos variables, y cada uno es:" << endl
		 << "     1 -> Un n\243mero entero" << endl
		 << "     08:00:00 -> Hora en reloj de 24hrs a dos d\241gitos por parte" << endl
		 << "     03-17-2017 -> Fecha con formato Mes-D\241a-Año a 2, 2 y 4 d\241gitos" << endl
		 << "     100 -> Un n\243mero entero" << endl
		 << endl
		 << endl
		 << endl
		 << "     Desarrollado por Ricardo Vel\240zquez Contreras - rivel_co" << endl
		 << endl
		 << endl
		 << "     Presiona cualquier tecla para volver...";
	system("pause>>null");
	return;
}

int main(){
	system("TITLE Activity wheel analyzer v0.2");
	bool otro = true;		// Control de repetición al menú
	int opc;				// Variable para pedir S/N
	while (otro){		// Mientras no se pida la salida
		Inicializar();	// Inicializamos todos los arreglos
		// Mensaje al usuario del menú
		cout << "     ------------------- Convertidor de conteos -------------------" << endl
			 << endl
			 << "                          Opciones de an\240lisis" << endl
			 << endl
			 << "     1- Analizar un rango de carpetas ordenadas" << endl
			 << "     2- Analizar una cantidad desordenada de carpetas" << endl
			 << "     3- Sobre este programa" << endl
			 << "     4- Salir del convertidor" << endl
			 << endl
			 << "     N\243mero de tu elecci\242n: ";
		// Pedimos la opción que requiera
		cin >> opc;
		// Identificamos la entrada
		switch(opc){
			case 1:	// Carpetas ordenadas
				TipoCaptura(1);
				break;
			case 2:	// Carpetas desordenadas
				TipoCaptura(2);
				break;
			case 3:
				SobreElPrograma();
				break;
			case 4:	// Salimos del programa
				otro = false;
				break;
			default:	// No sirve de mucho pero marca entrada no válida
				cout << "     Ingresa una opci\242n v\240lida" << endl;
				break;
		}
		// Limpiamos la pantalla cada que hacemos un tipo de análisis
		system("cls");
	}
	// Fin del programa
	return 0;
}
