#include <string>
#include <set>
using namespace std;

static const int MAX = 20;
	class Grafo {
		int N;
		string Cjtovertices[MAX];
		float MatAdyacencia[MAX][MAX];
		float MatFloyd[MAX][MAX];
		int MatP[MAX][MAX];
		float MatPrim[MAX][MAX];

	public:
		// DESC: Constructor por defecto de Grafo: Inicializa una instancia de Grafo.
		Grafo();
		// DESC: Restablece la Matriz de Adyacencia a su valor por defecto.
		void restablecerMatAdy();
		// DESC: Restablece la Matriz de Floyd a su valor por defecto.
		void restablecerMatFloyd();
		// DESC: Restablece la Matriz de P a su valor por defecto.
		void restablecerMatP();

		// PRE: string cad1 no existente dentro de Cjtovertices.
		// DESC: Inserta un vertice tipo 'String' en el conjunto de vertices.  
		void insertarVertice(string cad1);
		// PRE: string cad, cad2 existentes dentro de Cjtovertices.
		// DESC: Inserta una arista, compuesta de dos strings existentes en el conjunto de vertices y un coste, y lo inserta en el conjunto de aristas.
		//		 Si no se encuentra los strings, no se inserta.
		void insertarArista(string cad1, string cad2, float coste);
		// DESC: Busca en el conjunto de vertices el tipo 'String' indicado por parámetro.
		// POST: Devuelve el índice de dicho vertice en el vector del conjunto de vertices, o -1 en caso de no encontrar nada.
		int buscarPosicion(string cad1);
		// DESC: Busca el vertice de tipo 'String' ubicado en la posición del vector del conjunto de vectores dada por index (tipo 'Integer').
		// POST: Devuelve dicho vertice en forma de 'String'.
		string getVertice(int index);
		// DESC: Muestra por pantalla la Matriz de Adyecencia. 
		void MostrarMatrizAdy();
		// DESC: Muestra por pantalla la Matriz de Floyd.   
		void MostrarMatrizFloyd();
		// DESC: Muestra por pantalla la Matriz P (relacionada con Floyd).
		void MostrarMatrizP();
		// DESC: Muestra por pantalla la Matriz Prim (relacionada con la Adyacencia y Floyd).
		void MostrarMatrizPrim();


		// PRE: MatAdyacencia[MAX][MAX] debe estar inicializada con los valores a calcular. MatP[MAX][MAX] debe estar inicializada a 0.
		// DESC: Realiza los cálculos necesarios para calcular la Matriz de Floyd a partir de la Matriz de Adyacencia.
		//		 Primero, copia la Matriz de Adyacencia en la Matriz de Floyd.
		//		 Después, calcula el algoritmo de Floyd sobre dicha matriz.
		//	 	 La Matriz P recibe modificaciones. Es imperativo que dicha matriz esté vacía antes de operar.
		void calcularFloyd();
		// PRE: Requiere calcular la Matriz de Floyd y P previamente.
		// DESC: Muestra por pantalla el camino más corto entre dos vértices (de tipo 'String').
		//		 El método invoca a la versión recursiva para hacer el recorrido por los vertices y aristas.
		// POST: Devuelve un 'Float' equivalente al costo total de dicho recorrido, o -1 si no existe un camino posible entre dichos vertices.
		float calcularMinimoCamino(string cad1, string cad2);
		// DESC: Versión recursiva que hace el trabajo de calcular el mínimo camino de calcularMinimoCamino(string, string).
		void calcularMinimoCaminoRec(int i, int j);
		// PRE: MatAdyancencia[MAX][MAX] inicializada con aristas, MatPrim[MAX][MAX] inicializada por defecto, MatFloyd[MAX][MAX] inicializado con las mismas aristas que MatAdy.
		// DESC: Utiliza el algoritmo de Prim para calcular un árbol de expansión mínimo de la Matriz de Adyacencia.
		//	     Guarda en la Matriz de Prim las aristas de MatAdyacencia[MAX][MAX] resultantes del algoritmo con el costo almacenado en MatFloyd[MAX][MAX] de dicha arista.
		// POST: Devuelve un entero equivalente a la suma total de los costos de las aristas elegidas.
		float calcularPrim();

		// DESC: Copia los datos de la Matriz de Prim a la Matriz de Adyacencia.
		void copiarPrimAdyacencia();
		// DESC: Copia los datos de la Matriz de Adyacencia a la Matriz de Floyd.
		void copiarAdyacenciaFloyd();
};