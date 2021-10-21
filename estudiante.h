#ifndef LINKEDLIST_HEADER
#define LINKEDLIST_HEADER

typedef struct {
    char* nombre_materia;
    int anio_materia;
    int id;
}Materia;
typedef struct nodo_materia {
    struct materias * proxima_materia;
    int id;
    Materia *data;
}NodoMateria;
typedef struct nodo_materia_alumno {
    Materia * materia;
    int nota;
    struct nodo_materia_alumno * proximo_materia_alumno;
}NodoMateriaAlumno;
typedef struct nodo_estudiante {
    char* nombre;
    char* apellido;
    int edad;
    int id;
    int rendidas;
    int aprobadas;
    int desaprobadas;
    int total_notas;
    float promedio_general;
    double promedio;
    struct nodo_estudiante * proximo_estudiante;
    NodoMateriaAlumno *list_materias_notas;
}NodoEstudiante;
typedef struct lista_materias {
    NodoMateria * head;
    int id;
}ListaMaterias;
typedef struct {
    NodoEstudiante * head;
    NodoEstudiante *tail;
    int id;
}ListaEstudiantes;

ListaMaterias * crear_lista_materia();
ListaEstudiantes * crear_lista_estudiante();
Materia * buscar_materia_por_id(int id, ListaMaterias *list);
NodoEstudiante * buscar_estudiante_por_id(int id, ListaEstudiantes *list);
void imprimir_lista_estudiantes(ListaEstudiantes * list);
void agregar_materia(char *nombre, int correlativa, ListaMaterias * list);
void agregar_estudiante(char *nombre , char *apellido , int edad, ListaEstudiantes * list);
void asignar_materia_a_estudiante(int student_id, int subject_id, ListaEstudiantes *listaestudiantes, ListaMaterias *listamaterias);
void imprimir_materias_pendientes_de_un_estudiante(NodoEstudiante * estudiante);
void imprimir_lista_materias(ListaMaterias *list);
void imprimir_materias_de_un_estudiante(NodoEstudiante * estudiante);
NodoEstudiante * crear_nodo_estudiante(ListaEstudiantes * list, char *nombre , char *apellido , int edad);
NodoMateria * crear_nodo_materia(Materia *subject);
void mostrar_estadisticas(NodoEstudiante *estudiante);
void rendir_materia(int student_id, int subject_id, int nota, ListaEstudiantes *listaestudiantes);
ListaMaterias * crear_lista_materia();
void *ordenar_por_id(ListaEstudiantes * list);
void *ordenar_por_edad(ListaEstudiantes * list);
void *buscar_por_rango_edad(ListaEstudiantes * list, int num1, int num2);
void *buscar_por_nombre(ListaEstudiantes * list, char *nombreBuscado);
void *borrar_estudiante(int id, ListaEstudiantes * list);
int materia_ya_asignada(NodoEstudiante *estudiante, int id);
int getID(NodoEstudiante *estudiante);

#endif
