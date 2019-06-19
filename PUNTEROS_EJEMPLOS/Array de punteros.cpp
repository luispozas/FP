#include <iostream>
#include <string>
using namespace std;
const int N = 1000;

typedef struct{
    string nombre;
    int unidades;
}tObjeto;

// Puntero a un objeto
typedef tObjeto *tObjPtr;

// Array de punteros a registros:
typedef tObjPtr tArray[N];

typedef struct {
    tArray vDinam;
    int tam;
} tLista;

// Prototipos
int menu();
int buscarElemento(const tLista & l, const string & s);
void AddElem(tLista & l);
void Visualizar(const tLista & l);
void libera(tLista & l);

int main(){
    tLista lista;
    lista.tam = 0;
    
    int opcion = menu();
    while (opcion != 0){
        switch (opcion) {
        case 1:
        {
            AddElem(lista);
        }
            break;
        case 2:
        {
            Visualizar(lista);
        }
            break;
        case 3:
        {
            string name = "";
            cout << "Introduce el elemento a buscar su posició en la lista" << endl;
            cin >> name;
            int pos = buscarElemento(lista, name);
            if (pos == -1){
                cout << "No lo he encontrado, :-(" << endl;
            }
            else{
                cout << "Está en la pocición " << pos << endl;
            }
        }
            break;
    }
        opcion = menu();
        
    }

        libera(lista);
    return 0;
}

int menu() {
    int op = -1; // Cualquiera no válida
    while ((op < 0) || (op > 4)) {
        cout << "1 ‐ Nuevo objeto" << endl;
        cout << "2 ‐ Ver objeto" << endl;
        cout << "3 ‐ Buscar objeto" << endl;
        cout << "0 ‐ Salir" << endl;
        cout << "Opción: ";
        cin >> op;
        if ((op < 0) || (op > 3)) {
            cout << "¡Opción no válida!" << endl;
        }
        cout << endl;
    }
    return op;
}

int buscarElemento(const tLista & l, const string & s){
    int pos = 0;
    bool encontrado = false;
    
    while (pos < l.tam && !encontrado){
        if (l.vDinam[pos]->nombre == s){
            encontrado = true;
        }
        else{
            pos++;
        }
    }
    if (!encontrado){
        pos = -1;
    }
    return pos;
}

void AddElem(tLista & l){
    
    string aux_nombre;
    int aux_unidades;
    cout << "Introduce un nombre (sin espacios) y un número" << endl;
    cin >> aux_nombre >> aux_unidades;
    
    if (N == l.tam){
        cout << "No hay espacio" << endl;
    }else{
        l.vDinam[l.tam] = new tObjeto;
        l.vDinam[l.tam]->nombre = aux_nombre;
        l.vDinam[l.tam]->unidades = aux_unidades;
        l.tam++;
    }
    cout << endl;
}


void Visualizar(const tLista & l){
    for(int i=0; i< l.tam; i++){
        cout << "Elemento " << i << ": " << l.vDinam[i]->nombre << " " << l.vDinam[i]->unidades << endl;
    }
    cout << endl;
}

void libera(tLista & l){
    for(int i=0; i< l.tam; i++){
        delete(l.vDinam[i]);
    }
    l.tam = 0;
}

