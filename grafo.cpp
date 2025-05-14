#include "grafo.h"
#include <iostream>
#include <limits>

using namespace std;

Grafo::Grafo() {
	N = 0;
	restablecerMatAdy();
	restablecerMatFloyd();
	restablecerMatP();
	float* r = &MatPrim[0][0];
	for (int i = 0; i < MAX * MAX; i++) {
		*r = std::numeric_limits<float>::max();
		r++;
	}
	for (int j = 0; j < MAX; j++) {
		MatPrim[j][j] = 0;
	}
}

void Grafo::restablecerMatAdy() {
	float* a = &MatAdyacencia[0][0];
	for (int i = 0; i < MAX * MAX; i++) {
		*a = std::numeric_limits<float>::max();
		a++;
	}
	for (int j = 0; j < MAX; j++) {
		MatAdyacencia[j][j] = 0;
	}
}

void Grafo::restablecerMatFloyd()
{
	float* f = &MatFloyd[0][0];
	for (int i = 0; i < MAX * MAX; i++) {
		*f = std::numeric_limits<float>::max();
		f++;
	}
	for (int j = 0; j < MAX; j++) {
		MatFloyd[j][j] = 0;
	}
}

void Grafo::restablecerMatP()
{
	int* p = &MatP[0][0];
	for (int i = 0; i < MAX * MAX; i++) {
		*p = -1;
		p++;
	}
}

void Grafo::insertarVertice(string cad1) {
	Cjtovertices[N] = cad1;
	N++;
}

void Grafo::insertarArista(string cad1, string cad2, float coste) {
	int n1 = buscarPosicion(cad1);
	int n2 = buscarPosicion(cad2);
	if (n1 != -1 && n2 != -1) {
		MatAdyacencia[n1][n2] = coste;
		MatAdyacencia[n2][n1] = coste;
	}
}

void Grafo::MostrarMatrizAdy() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (MatAdyacencia[i][j] == std::numeric_limits<float>::max()) {
				cout << "0 ";
			}
			else {
				cout << MatAdyacencia[i][j] << " ";
			}
		}
		cout <<  endl;
	}
}

void Grafo::MostrarMatrizP() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << MatP[i][j] << " ";
		}
		cout << endl;
	}
}

void Grafo::MostrarMatrizPrim()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (MatPrim[i][j] == std::numeric_limits<float>::max()) {
				cout << "INF ";
			}
			else {
				cout << MatPrim[i][j] << " ";
			}
		}
		cout << endl;
	}
}

void Grafo::MostrarMatrizFloyd() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (MatFloyd[i][j] == std::numeric_limits<float>::max()) {
				cout << "0 ";
			}
			else {
				cout << MatFloyd[i][j] << " ";
			}
		}
		cout << endl;
	}
}

int Grafo::buscarPosicion(string cad1)
{
	for (int i = 0; i < N; i++) {
		if (Cjtovertices[i] == cad1) return (i);
	}
	return(-1);
}

string Grafo::getVertice(int index)
{
	return Cjtovertices[index];
}

void Grafo::calcularFloyd()
{
	//Copiamos la Matriz de Adyacencia en Floyd
	copiarAdyacenciaFloyd();

	// Algoritmo de Floyd
	int i, j, k;
	for (k = 0; k < N; k++) {
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				if ((MatFloyd[i][k] + MatFloyd[k][j]) < MatFloyd[i][j]) {
					MatFloyd[i][j] = MatFloyd[i][k] + MatFloyd[k][j];
					MatP[i][j] = k;
				}
			}
		}
	}
}

float Grafo::calcularMinimoCamino(string cad1, string cad2)
{
	int n1 = buscarPosicion(cad1);
	int n2 = buscarPosicion(cad2);
	if (MatFloyd[n1][n2] == std::numeric_limits<float>::max()) return(-1);

	cout << cad1 << " ";
	calcularMinimoCaminoRec(n1,n2);
	cout << cad2;
	return (MatFloyd[n1][n2]);
}

void Grafo::calcularMinimoCaminoRec(int i, int j) {
	int k = MatP[i][j];
	if (k != -1) {
		calcularMinimoCaminoRec(i, k);
		cout << getVertice(k) << " ";
		calcularMinimoCaminoRec(k, j);
	}
}

float Grafo::calcularPrim()
{
	set<int> U; // Creamos un set donde guardar los vértices
	float costoTotal = 0; // Calculamos el coste total.
	int uMin; // Creamos un valor auxiliar para el U procesado actual
	int iMin; // Creamos un valor auxiliar para guardar el índice del vértice con el que, conjunto a U, tienen la arista mejor de las adyacentes con V.
	float costeARebajar; // Coste que debe de ser rebajado (valor de la arista uMin e iMin)
	U.insert(0); // Insertamos un vértice cualquiera
	while (U.size() != N) { // Mientras U no tenga todos los vertices del Cjtovertices...
		uMin = 0;
		iMin = 0;
		costeARebajar = std::numeric_limits<float>::max();
		for (auto u = U.begin(); u != U.end(); u++) { // Por cada vértice existente en U...
			for (int i = 0; i < N; i++) { // Y por cada vértice existente en el Cjtovertices...
				if (U.find(i) == U.end()) { // Si ese vertice i no está en U...
					if (MatAdyacencia[*u][i] < costeARebajar) { // Comparamos el camino de u e i (bucle) con el costeARebajar
						uMin = *u; // Si u e i son menores, u e i será en nuevo menor.
						iMin = i;
						costeARebajar = MatAdyacencia[uMin][iMin]; // Ajustamos el costeARebajar al nuevo valor.
					}
				} // Si el vértice i ya estaba en U, entonces no lo comprobamos
			}
		}	// Una vez terminado todo el búcle...
		float costo = MatFloyd[uMin][iMin];
		float costo2 = MatFloyd[uMin][iMin];
		MatPrim[uMin][iMin] = costo; // Escribimos en la Matriz de Prim la arista de uMin a iMin con su apropiado costo (la obtenemos de la Matriz de Floyd)
		MatPrim[iMin][uMin] = costo; // También al reves, pues es no dirigido.
		costoTotal += costo; // Sumamos el coste de esta arista al total.
		U.insert(iMin); // i ahora forma parte de U.
	}
	// Fin del algoritmo

	return(costoTotal);
}

void Grafo::copiarPrimAdyacencia()
{
	float* a = &MatAdyacencia[0][0];
	float* p = &MatPrim[0][0];
	for (int i = 0; i < MAX * MAX; i++) {
		*a = *p;
		a++;
		p++;
	}
}

void Grafo::copiarAdyacenciaFloyd()
{
	float* a = &MatAdyacencia[0][0];
	float* f = &MatFloyd[0][0];
	for (int i = 0; i < MAX * MAX; i++) {
		*f = *a;
		a++;
		f++;
	}
}


