#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "estudiante.h"

static int id_materia=1;

NodoEstudiante * crear_nodo_estudiante(ListaEstudiantes * list, char *nombre , char *apellido , int edad){
    NodoEstudiante * newNode = malloc(sizeof(NodoEstudiante));
    if (!newNode) {
        return NULL;
    }
    for (int indice = 0; nombre[indice] != '\0'; ++indice) {
        nombre[indice] = toupper(nombre[indice]);
    }
    for (int indice = 0; apellido[indice] != '\0'; ++indice) {
        apellido[indice] = toupper(apellido[indice]);
    }
    newNode->nombre=nombre;
    newNode->apellido=apellido;
    newNode->edad = edad;
    newNode->aprobadas=0;
    newNode->desaprobadas=0;
    newNode->rendidas=0;
    newNode->total_notas=0;
    newNode->promedio_general=0;
    newNode->id = list->id++;
    newNode->proximo_estudiante = NULL;
    newNode->list_materias_notas = NULL;
    return newNode;
}
NodoMateria * crear_nodo_materia(Materia *subject){
    NodoMateria * newNode = malloc(sizeof(NodoMateria));
    if (!newNode) {
        return NULL;
    }

    newNode->data = subject;
    newNode->proxima_materia = NULL;
    return newNode;
}
NodoMateriaAlumno *crear_estudiante_materia(Materia *subject){
    NodoMateriaAlumno * newNode = malloc(sizeof(NodoMateriaAlumno));
    newNode->materia = subject;
    newNode->nota = 0;
    newNode->proximo_materia_alumno = NULL;
    return newNode;
}
ListaEstudiantes * crear_lista_estudiante(){
    ListaEstudiantes * list = malloc(sizeof(ListaEstudiantes));
    if (!list) {
        return NULL;
    }
    list->tail = NULL;
    list->head = NULL;
    list->id=1;
    return list;
}
ListaMaterias * crear_lista_materia(){
    ListaMaterias * list = malloc(sizeof(ListaMaterias));
    if (!list) {
        return NULL;
    }
    list->head = NULL;
    list->id= NULL;
    return list;
}
NodoEstudiante * buscar_estudiante_por_id(int id, ListaEstudiantes * list){
    if (list == NULL) {
        return list;
    } else {
        int contador = 0;
        NodoEstudiante *cursor = list->head;
        while (cursor->proximo_estudiante != NULL) {
            if (cursor->id == id) {
                contador++;
                return cursor;
            }
            cursor = cursor->proximo_estudiante;
        }
        if (cursor->id == id){
            return cursor;
        }
        if(contador ==0){
            printf("No hay ningun estudiante con el ID %d\n", id);
            return cursor = NULL;
        }
    }
}
Materia * buscar_materia_por_id(int id, ListaMaterias *list){
    if (list == NULL) {
        return list;
    } else {
        int contador = 0;
        NodoMateria *cursor = list->head;
        while (cursor->proxima_materia != NULL) {
            if (cursor->data->id == id) {
                contador++;
                return cursor->data;
            }
            cursor = cursor->proxima_materia;
        }
        if (cursor->data->id == id){
            return cursor->data;
        }
        if(contador ==0){
            printf("No hay ninguna materia con el ID %d", id);
            return NULL;
        }
    }
}
int materia_ya_asignada(NodoEstudiante *estudiante, int id){
    NodoMateriaAlumno *nodecurrent = estudiante->list_materias_notas;
    for (; nodecurrent != NULL ;nodecurrent= nodecurrent->proximo_materia_alumno) {
        if(nodecurrent->materia->id == id){
            return 0;
        }
    }
    return 1;
}
void asignar_materia_a_estudiante(int student_id, int subject_id, ListaEstudiantes *listaestudiantes, ListaMaterias *listamaterias){

    NodoEstudiante *nodo_student = buscar_estudiante_por_id(student_id, listaestudiantes);
    Materia *subject_data = buscar_materia_por_id(subject_id, listamaterias);

    if(subject_id <=27){
        NodoMateriaAlumno *current = NULL;

        NodoMateriaAlumno *nodoaux = crear_estudiante_materia(subject_data);
        if(nodo_student->list_materias_notas == NULL){
            nodo_student->list_materias_notas = nodoaux;
        }
        else {
            current = nodo_student->list_materias_notas;
            while (current->proximo_materia_alumno != NULL){
                if(current->proximo_materia_alumno->materia->id == subject_id){
                    printf("Ya esta inscripto\n");
                    current = current->proximo_materia_alumno;
                }else{
                    current = current->proximo_materia_alumno;
                }

            }
            current->proximo_materia_alumno = nodoaux;
        }

    }
    if(subject_id>=28){
        int aux= subject_id-27;
        int pe = materia_ya_asignada(nodo_student,aux);
        if(pe!=0){
            printf("El estudiante no se puede anotar a esta materia ya que no se inscribio a la correlativa anterior\n");
        }else{
            NodoMateriaAlumno *current = NULL;

            NodoMateriaAlumno *nodoaux = crear_estudiante_materia(subject_data);
            if(nodo_student->list_materias_notas == NULL){
                nodo_student->list_materias_notas = nodoaux;
            }
            else {
                current = nodo_student->list_materias_notas;
                while (current->proximo_materia_alumno != NULL){
                    if(current->proximo_materia_alumno->materia->id == subject_id){
                        printf("Ya está inscripto\n");
                    }else{
                        current = current->proximo_materia_alumno;
                    }
                }
                current->proximo_materia_alumno = nodoaux;
            }
        }


    }
}
void rendir_materia(int student_id, int subject_id, int nota, ListaEstudiantes *listaestudiantes){

    NodoMateriaAlumno *current = NULL;
    NodoEstudiante *estudiante = buscar_estudiante_por_id(student_id, listaestudiantes);

    current = estudiante->list_materias_notas;
    while (current->proximo_materia_alumno != NULL){
        if(current->materia->id == subject_id){
            current->nota = nota;
            if(nota>=4 && nota<=10){
                estudiante->total_notas = estudiante->total_notas+nota;
                estudiante->rendidas++;
                estudiante->aprobadas++;
            }else{
                estudiante->total_notas = estudiante->total_notas+nota;
                estudiante->rendidas++;
                estudiante->desaprobadas++;
            }
        }
        current = current->proximo_materia_alumno;
    }

    if(current->materia->id == subject_id){
        current->nota = nota;
        if(nota>=4 && nota<=10){
            estudiante->total_notas = estudiante->total_notas+nota;
            estudiante->rendidas++;
            estudiante->aprobadas++;
        }else{
            estudiante->total_notas = estudiante->total_notas+nota;
            estudiante->rendidas++;
            estudiante->desaprobadas++;
        }
    }
    estudiante->promedio = (float)estudiante->total_notas/(float)estudiante->rendidas;
    estudiante->promedio_general = (float)estudiante->aprobadas*100/(float)estudiante->rendidas;
}
void mostrar_estadisticas(NodoEstudiante *estudiante){
    printf("El estudiante %s %s rindio %d materias.\nMaterias aprobadas: %d\nMaterias desaprobadas: %d\nPorcentaje de aprobacion: %f\n"
           "Promedio de notas: %f\n",
           estudiante->nombre,estudiante->apellido,estudiante->rendidas,estudiante->aprobadas,estudiante->desaprobadas,estudiante->promedio_general,estudiante->promedio);
}
void agregar_estudiante(char *nombre , char *apellido , int edad, ListaEstudiantes * list){
    NodoEstudiante * current = NULL;
    if(list->head == NULL){
        NodoEstudiante *nodoaux = crear_nodo_estudiante(list, nombre,apellido,edad);
        list->head = nodoaux;
    }
    else {
        current = list->head;
        while (current->proximo_estudiante != NULL){
            current = current->proximo_estudiante;
        }
        current->proximo_estudiante = crear_nodo_estudiante(list,nombre,apellido,edad);
        list->tail=current->proximo_estudiante;
    }
}
void agregar_materia(char *nombre, int correlativa, ListaMaterias * list){
    NodoMateria * current = NULL;
    Materia *subaux = malloc(sizeof(Materia));
    subaux->id = id_materia++;
    subaux->nombre_materia = nombre;
    subaux->anio_materia = correlativa;
    if(list->head == NULL){
        NodoMateria *nodoaux = crear_nodo_materia(subaux);
        list->head = nodoaux;
    }
    else {
        current = list->head;
        while (current->proxima_materia != NULL){
            current = current->proxima_materia;
        }
        current->proxima_materia = crear_nodo_materia(subaux);
    }
}
void imprimir_materias_de_un_estudiante(NodoEstudiante * estudiante) {
    NodoMateriaAlumno *nodecurrent = estudiante->list_materias_notas;
    for (; nodecurrent != NULL ;nodecurrent= nodecurrent->proximo_materia_alumno) {
        if(nodecurrent->nota == 0){
            printf("Materia ID: %d  Nombre: %s %d \n", nodecurrent->materia->id , nodecurrent->materia->nombre_materia, nodecurrent->materia->anio_materia);
            printf("Nota: MATERIA PENDIENTE\n\n");
        }else{
            printf("Materia ID: %d  Nombre: %s %d \n", nodecurrent->materia->id , nodecurrent->materia->nombre_materia, nodecurrent->materia->anio_materia);
            printf("Nota: %d \n\n", nodecurrent->nota);
        }
    }
}
void imprimir_materias_pendientes_de_un_estudiante(NodoEstudiante * estudiante) {
    NodoMateriaAlumno *nodecurrent = estudiante->list_materias_notas;
    for (; nodecurrent != NULL ;nodecurrent= nodecurrent->proximo_materia_alumno) {
        if(nodecurrent->nota ==1 || nodecurrent->nota ==2 || nodecurrent->nota ==3  ){
            printf("Materia ID: %d  Nombre: %s %d \n", nodecurrent->materia->id , nodecurrent->materia->nombre_materia, nodecurrent->materia->anio_materia);
            printf("Nota: %d \n\n", nodecurrent->nota);

        }if(nodecurrent->nota == 0){
            printf("Materia ID: %d  Nombre: %s %d \n", nodecurrent->materia->id , nodecurrent->materia->nombre_materia, nodecurrent->materia->anio_materia);
            printf("Nota: MATERIA PENDIENTE\n\n");

        }
    }
}
void imprimir_lista_estudiantes(ListaEstudiantes * list) {
    NodoEstudiante * actual = list->head;
    if(list->head == NULL) return;
    for(; actual != NULL; actual = actual->proximo_estudiante) {
        printf("ID : %d -Nombre y apellido: %s %s - Edad: %d \n", actual->id,actual->nombre,actual->apellido,actual->edad);
    }
}
void imprimir_lista_materias(ListaMaterias * list){
    NodoMateria * actual = list->head;
    if(list->head == NULL) return;
    for(; actual != NULL; actual = actual->proxima_materia) {
        printf("Materia ID: %d ---- Nombre: %s %d\n", actual->data->id, actual->data->nombre_materia,actual->data->anio_materia);
    }
}
void *ordenar_por_edad(ListaEstudiantes * list) {
    NodoEstudiante *cursor = list->head;
    while (cursor != NULL) {
        NodoEstudiante *sig = cursor->proximo_estudiante;
        while (sig != NULL) {
            if (cursor->edad > sig->edad) {

                char* auxedad = sig->edad;
                sig->edad = cursor->edad;
                cursor->edad = auxedad;

                char* auxnombre = sig->nombre;
                sig->nombre = cursor->nombre;
                cursor->nombre = auxnombre;

                int auxapellido = sig->apellido;
                sig->apellido = cursor->apellido;
                cursor->apellido = auxapellido;

                int auxID =  sig->id;
                sig->id = cursor->id;
                cursor->id = auxID;
            }
            sig = sig->proximo_estudiante;
        }
        cursor = cursor->proximo_estudiante;
    }
}
void *ordenar_por_id(ListaEstudiantes * list) {
    NodoEstudiante *cursor = list->head;
    while (cursor != NULL) {
        NodoEstudiante *sig = cursor->proximo_estudiante;
        while (sig != NULL) {
            if (cursor->id > sig->id) {
                char* auxedad = sig->id;
                sig->id = cursor->id;
                cursor->id = auxedad;
                char* auxnombre = sig->nombre;
                sig->nombre = cursor->nombre;
                cursor->nombre = auxnombre;
                int auxapellido = sig->apellido;
                sig->apellido = cursor->apellido;
                cursor->apellido = auxapellido;
                int auxEdad =  sig->edad;
                sig->edad = cursor->edad;
                cursor->edad = auxEdad;
            }
            sig = sig->proximo_estudiante;
        }
        cursor = cursor->proximo_estudiante;
    }

}
void *buscar_por_rango_edad(ListaEstudiantes * list, int num1, int num2){
    ordenar_por_edad(list);
    printf("Estudiantes con edad entre %d y %d:\n", num1, num2);
    int aux = num1;
    int aux2 = num2;
    if(list->tail->edad < aux || list->head->edad > aux2){
        printf("No hay estudiantes en ese rango de edad\n");
    }else{
        if (list->head == NULL) {
            printf("No hay estudiantes \n");
        } else {
            NodoEstudiante *cursor = list->head;
            while (cursor->edad < num1) {
                cursor = cursor->proximo_estudiante;
            }
            while (cursor->edad >= num1 && cursor->edad <= num2) {
                printf("ID: %d -    Nombre y Apellido: %s %s - Edad : %d \n",cursor->id, cursor->nombre,cursor->apellido, cursor->edad);
                cursor = cursor->proximo_estudiante;
            }
            printf("\n");
        }
    }
}
void *buscar_por_nombre(ListaEstudiantes * list, char *nombreBuscado){
    if (list == NULL) {
        return list;
    } else {
        int contador=0;
        for (int indice = 0; nombreBuscado[indice] != '\0'; ++indice) {
            nombreBuscado[indice] = toupper(nombreBuscado[indice]);
        }

        NodoEstudiante *cursor = list->head;
        printf("Estudiantes con nombre %s:\n", nombreBuscado);
        while (cursor->proximo_estudiante != NULL) {
            if(strcmp(cursor->nombre,nombreBuscado) == 0){
                printf("ID: %d -    Nombre y Apellido: %s %s - Edad : %d \n",cursor->id, cursor->nombre,cursor->apellido, cursor->edad);
                contador++;
            }
            cursor = cursor->proximo_estudiante;
        }
        if(strcmp(cursor->nombre,nombreBuscado) == 0){
            printf("ID: %d -    Nombre y Apellido: %s %s - Edad : %d \n",cursor->id, cursor->nombre,cursor->apellido, cursor->edad);
            contador++;
        }
        if(contador ==0){
            printf("No hay ningun estudiante con el nombre %s", nombreBuscado);
        }
        printf("\n");
    }
}
int getID(NodoEstudiante *estudiante){
    return estudiante->id;
}
void *borrar_estudiante(int id, ListaEstudiantes * lista){
    NodoEstudiante * actual = lista->head;
    NodoEstudiante * anterior = actual;
    while(actual != NULL){
        if(actual->id == id){
            anterior->proximo_estudiante = actual->proximo_estudiante;
            if(actual == lista->head)
                lista->head = actual->proximo_estudiante;
            free(actual);
        }
        anterior = actual;
        actual = actual->proximo_estudiante;
    }
}
