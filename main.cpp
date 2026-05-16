#include <iostream>
#include <string>
#include <iomanip> // setprecision, fixed
using namespace std;

class Alumno
{
public:
  string nombres;
  string apellidos;
  string carnet;
  string email;
  string telefono;
  double notas[5];

  Alumno()
  {
    for (int i = 0; i < 5; i++)
      notas[i] = 0.0;
  }

  double promedio() const
  {
    double suma = 0;
    for (int i = 0; i < 5; i++)
      suma += notas[i];
    return suma / 5.0;
  }

  void mostrar() const
  {
    cout << "  Nombres   : " << nombres << "\n";
    cout << "  Apellidos : " << apellidos << "\n";
    cout << "  Carnet    : " << carnet << "\n";
    cout << "  Email     : " << email << "\n";
    cout << "  Teléfono  : " << telefono << "\n";
    cout << "  Notas     : ";
    for (int i = 0; i < 5; i++)
    {
      cout << fixed << setprecision(2) << notas[i];
      if (i < 4)
        cout << ", ";
    }
    cout << "\n";
    cout << "  Promedio  : " << fixed << setprecision(2) << promedio() << "\n";
  }
};

class Nodo
{
public:
  Alumno alumno;
  Nodo *siguiente;

  Nodo(const Alumno &a) : alumno(a), siguiente(nullptr) {}
};

class ListaEnlazada
{
private:
  Nodo *cabeza;
  int cantidad;

public:
  ListaEnlazada() : cabeza(nullptr), cantidad(0) {}
  ~ListaEnlazada()
  {
    Nodo *actual = cabeza;
    while (actual != nullptr)
    {
      Nodo *siguiente = actual->siguiente;
      delete actual;
      actual = siguiente;
    }
    cabeza = nullptr;
  }

  void insertar(const Alumno &a)
  {
    Nodo *nuevo = new Nodo(a);

    if (cabeza == nullptr)
    {
      cabeza = nuevo;
    }
    else
    {
      Nodo *actual = cabeza;
      while (actual->siguiente != nullptr)
      {
        actual = actual->siguiente;
      }
      actual->siguiente = nuevo;
    }
    cantidad++;
  }

  void mostrarTodos() const
  {
    if (cabeza == nullptr)
    {
      cout << "  La lista está vacía.\n";
      return;
    }

    Nodo *actual = cabeza;
    int indice = 1;

    while (actual != nullptr)
    {
      cout << "\n  ─────────────────────────────────────\n";
      cout << "  Alumno #" << indice << "\n";
      cout << "  ─────────────────────────────────────\n";
      actual->alumno.mostrar();
      actual = actual->siguiente;
      indice++;
    }
  }

  int getCantidad() const { return cantidad; }
};

double pedirNota(int numero)
{
  double nota;
  do
  {
    cout << "    Nota " << numero << " (0-10): ";
    cin >> nota;
    if (cin.fail())
    {
      cin.clear();
      cin.ignore(1000, '\n');
      nota = -1;
    }
    if (nota < 0 || nota > 10)
    {
      cout << "    !! Valor invalido. Ingrese un numero entre 0 y 10.\n";
    }
  } while (nota < 0 || nota > 10);
  cin.ignore(1000, '\n');
  return nota;
}

Alumno pedirDatosAlumno()
{
  Alumno a;

  cout << "  Nombres   : ";
  getline(cin, a.nombres);
  cout << "  Apellidos : ";
  getline(cin, a.apellidos);
  cout << "  Carnet    : ";
  getline(cin, a.carnet);
  cout << "  Email     : ";
  getline(cin, a.email);
  cout << "  Teléfono  : ";
  getline(cin, a.telefono);

  cout << "  Ingrese las 5 notas:\n";
  for (int i = 0; i < 5; i++)
  {
    a.notas[i] = pedirNota(i + 1);
  }
  return a;
}

int main()
{
  ListaEnlazada lista;
  char continuar;

  cout << "╔══════════════════════════════════════════╗\n";
  cout << "║    LISTA ENLAZADA DE ALUMNOS — C++       ║\n";
  cout << "╚══════════════════════════════════════════╝\n\n";

  do
  {
    cout << "─── Ingreso de Alumno #" << lista.getCantidad() + 1 << " ───\n";
    Alumno nuevo = pedirDatosAlumno();
    lista.insertar(nuevo);

    cout << "\n✔ Alumno agregado correctamente.\n";
    cout << "¿Desea agregar otro alumno? (s/n): ";
    cin >> continuar;
    cin.ignore();
    cout << "\n";

  } while (continuar == 's' || continuar == 'S');

  // Mostrar resultado final
  cout << "\n╔══════════════════════════════════════════╗\n";
  cout << "║         LISTADO FINAL DE ALUMNOS         ║\n";
  cout << "╚══════════════════════════════════════════╝\n";
  cout << "  Total de alumnos registrados: " << lista.getCantidad() << "\n";

  lista.mostrarTodos();

  cout << "\n  ─────────────────────────────────────\n";
  cout << "  Programa finalizado. Memoria liberada.\n";

  return 0;
}
