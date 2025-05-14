
#include <iostream>
#include <string>
#include "grafo.h"

using namespace std;

int const MAX_VEC = 50;

int main()
{
	// Declaración de variables iniciales
	Grafo G;

	string vertice, identificador1, identificador2, unidad;
	string *preguntas = new string[MAX_VEC * 2];
	string *prioridades = new string[MAX_VEC * 3];
	int nVertices, nIdentificadores, nPreguntas, nUnidades;
	bool usarPrioridades = false;
	float coste;
	
	// Carga de vertices
	cin >> nVertices; //lee el primer valor entero. Porque nVertices es “integer”
	
	for (int n = 0; n < nVertices; n++) {
		cin >> vertice; //lee un string, tantas veces como se realice el bucle
		G.insertarVertice(vertice);
	}

	// Carga de aristas
	cin >> nIdentificadores;
	for (int d = 0; d < nIdentificadores; d++) {
		cin >> identificador1;
		cin >> identificador2;
		cin >> coste;
		G.insertarArista(identificador1, identificador2,coste);
	}

	// Recogemos todas las preguntas
	cin >> nPreguntas;
	nUnidades = nPreguntas * 2;
	int p;
	for (p = 0; p < nUnidades; p++) {
		string cad;
		cin >> cad;
		preguntas[p] = cad;
	}

	// Detectamos comienzo de "Prioridades"
	string test;
	cin >> test;
	if (test == "Prioridades") {
		usarPrioridades = true;
		// Guardamos las nuevas aristas en un vector para procesarlas más tarde
		for (int d = 0; d < nIdentificadores*3; d++) {
			string cad;
			cin >> cad;
			prioridades[d] = cad;
		}
	}

	// Llegados a este punto, ya hemos cargado y almacenado todo lo que necesitamos.
	// Ahora podemos empezar a responder.

	cout << endl;

	// Con los datos de las aristas almacenados, calculamos los caminos mínimos, para servir a las siguientes preguntas.
	G.calcularFloyd();

	// Procesamos las preguntas
	float res;
	for (p = 0; p < nUnidades; p += 2) {
		res = G.calcularMinimoCamino(preguntas[p], preguntas[p + 1]);
		cout << " " << res << endl;
	}

	if (usarPrioridades) { // Si se han introducido Prioridades, entonces las resolvemos también.

		// Restablecemos por defecto las matriz de adyacencia para acomodar los nuevos valores.
		// Pero, antes queremos guardar los costes originales de nuestras carreteras.
		// Para esto, moveremos temporalmente los datos de la Matriz de Adyacencia en la Matriz de Floyd.
		G.copiarAdyacenciaFloyd();
		G.restablecerMatAdy();

		// Insertamos nuevas aristas en la Matriz de Adyacencia, por medio de las prioridades anteriormente almacenadas.
		for (int d = 0; d < nIdentificadores*3; d += 3) {
			G.insertarArista(prioridades[d], prioridades[d+1], stoi(prioridades[d+2]));
		}

		// Calculamos el árbol de expansión mínimo de los datos de las prioridades que acabamos de meter y mostramos cuanta carretera se debe de arreglar.
		// El algoritmo de Prim hace uso de de las aristas de 
		cout << endl << G.calcularPrim() << endl << endl;

		// Copiamos el resultado a la Matriz de Adyacencia.
		G.copiarPrimAdyacencia();

		// Calculamos Floyd con dichos datos copiados. Pero antes, debemos limpiar su Matriz y la de P.
		G.restablecerMatFloyd();
		G.restablecerMatP();
		G.calcularFloyd();

		// Procesamos de nuevo las preguntas.
		float res;
		for (p = 0; p < nUnidades; p += 2) {
			res = G.calcularMinimoCamino(preguntas[p], preguntas[p + 1]);
			cout << " " << res << endl;
		}

	}
	return(0);
}