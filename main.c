#include <stdio.h>
#include <stdlib.h>
#include "estudiante.h"

int opcion_seguir_gestionando_o_salir(NodoEstudiante *listaEstudiantes, NodoMateria *nodoMateria){
    int opcion=0;
    printf("Que desea realizar?\n\n    Digite 1 para volver al Menu Principal o cualquier otra tecla para salir\n");
    scanf("%d", &opcion);
    if (opcion == 1) {
        return 1;

    } else {
        printf("Adios!");
        return 0;
    }
}
int opcion_seguir_gestionando_estudiante_o_volver_al_menu(){
    int opcion=0;
    printf("Que desea realizar?\n\n    Digite 1 para seguir gestionando sobre el estudiante o cualquier otra tecla volver al Menu Principal\n");
    scanf("%d", &opcion);
    if (opcion == 1) {
        return 1;
    } else {
        printf("\n\n\n");
        return 0;
    }
}
NodoEstudiante *opcion_seleccionar_estudiante(NodoEstudiante *listaEstudiantes, NodoMateria *listaMateria){
    int idSeleccionado= 0;
    printf("\n");
    ordenar_por_id(listaEstudiantes);
    printf("Ingrese el ID del estudiante para comenzar a gestionar:\n\n");
    scanf("%d",&idSeleccionado);
    NodoEstudiante *seleccionado = buscar_estudiante_por_id(idSeleccionado,listaEstudiantes);
    if(seleccionado->nombre ==NULL){
        printf("El ID %d no existe. Por favor, intente nuevamente\n" ,idSeleccionado);
        opcion_seleccionar_estudiante(listaEstudiantes, listaMateria);
    }else{
        return seleccionado;
    }
}
void opcion_gestionar_estudiante(NodoEstudiante *estudiante, NodoEstudiante *listaEstudiantes, NodoMateria *listaMateria){
    int opcion=0;
    printf("        Menu Estudiante\nQue gestion desea realizar?:\n");
    printf("1. Anotarse a una materia\n2. Rendir una materia\n3. Eliminar al estudiante\n4. Ver todas las materias del estudiante\n"
           "5. Ver solamente las materias pendientes\n6. Mostrar estadisticas\n7. Volver al Menu Principal\n\n");
    scanf("%d", &opcion);
    if(opcion==1){
        int IdMateria=0;
        imprimir_lista_materias(listaMateria);
        printf("    A que materia se desea anotar?\n");
        scanf("%d", &IdMateria);
        int materiaAsignada=0;
        materiaAsignada = materia_ya_asignada(estudiante,IdMateria);
        if(materiaAsignada == 1){
            asignar_materia_a_estudiante(estudiante->id,IdMateria,listaEstudiantes,listaMateria);
            int seleccion = opcion_seguir_gestionando_estudiante_o_volver_al_menu();
            if(seleccion ==1){
                opcion_gestionar_estudiante(estudiante,listaEstudiantes,listaMateria);
            }
        }else if (materiaAsignada == 0){
            printf("El estudiante ya se encuentra anotado a esta materia\n");
            int seleccion = opcion_seguir_gestionando_estudiante_o_volver_al_menu();
            if(seleccion ==1){
                opcion_gestionar_estudiante(estudiante,listaEstudiantes,listaMateria);
            }
        }
    }
    else if(opcion==2){
        int materia_seleccionada;
        if(estudiante->list_materias_notas == NULL){
            printf("El estudiante no esta anotado a ninguna materia\n");
            int seleccion = opcion_seguir_gestionando_estudiante_o_volver_al_menu();
            if(seleccion ==1){
                opcion_gestionar_estudiante(estudiante,listaEstudiantes,listaMateria);
            }
        }else{
            imprimir_materias_pendientes_de_un_estudiante(estudiante);
            int calificacion = 0;
            printf("Que materia desea rendir?\n");
            scanf("%d",&materia_seleccionada);
            if (materia_seleccionada == NULL){

            }else {
                int materiaAsignada=0;
                materiaAsignada = materia_ya_asignada(estudiante,materia_seleccionada);
                if(materiaAsignada == 0){

                    int valido = 0;
                    while (valido != 1) {
                        printf("Ingrese una calificacion valida entre 1 y 10:\n");
                        scanf("%d", &calificacion);
                        if (calificacion <= 0 || calificacion >= 11) {
                            valido = 0;
                            printf("Numero invalido. Por favor reintente\n");
                        } else {
                            valido = 1;
                        }
                    }
                    rendir_materia(estudiante->id,materia_seleccionada,calificacion,listaEstudiantes);
                    int seleccion = opcion_seguir_gestionando_estudiante_o_volver_al_menu();
                    if(seleccion ==1){
                        opcion_gestionar_estudiante(estudiante,listaEstudiantes,listaMateria);
                    }
                }else if (materiaAsignada == 1){
                    printf("El estudiante no esta anotado a esa materia\n");
                    int seleccion = opcion_seguir_gestionando_estudiante_o_volver_al_menu();
                    if(seleccion ==1){
                        opcion_gestionar_estudiante(estudiante,listaEstudiantes,listaMateria);
                    }
                }
            }
            int seleccion = opcion_seguir_gestionando_estudiante_o_volver_al_menu();
            if(seleccion ==1){
                opcion_gestionar_estudiante(estudiante,listaEstudiantes,listaMateria);
            }
        }
    }
    else if(opcion==3) {
        int id = getID(estudiante);
        borrar_estudiante(id, listaEstudiantes);
        printf("Borrado exitosamente!\n");
    }
    else if(opcion==4){
        printf("Las materias de %s %s son:\n",estudiante->nombre,estudiante->apellido);
        imprimir_materias_de_un_estudiante(estudiante);
        int seleccion = opcion_seguir_gestionando_estudiante_o_volver_al_menu();
        if(seleccion ==1){
            opcion_gestionar_estudiante(estudiante,listaEstudiantes,listaMateria);
        }
    }
    else if(opcion==5){
        imprimir_materias_pendientes_de_un_estudiante(estudiante);
        int seleccion = opcion_seguir_gestionando_estudiante_o_volver_al_menu();
        if(seleccion ==1){
            opcion_gestionar_estudiante(estudiante,listaEstudiantes,listaMateria);
        }
    }
    else if(opcion==6){
        mostrar_estadisticas(estudiante);
        int seleccion = opcion_seguir_gestionando_estudiante_o_volver_al_menu();
        if(seleccion ==1){
            opcion_gestionar_estudiante(estudiante,listaEstudiantes,listaMateria);
        }
    }
    else if(opcion==7){
        printf("Volviendo al Menu Principal...\n");
    }
}
void opcion_agregar_estudiante(NodoEstudiante *listaEstudiantes){
    char *nombre;
    char *apellido;
    int edad;
    printf("Ingrese el nombre del estudiante:\n");
    scanf("%s",nombre);
    printf("Ingrese el apellido del estudiante:\n");
    scanf("%s",apellido);
    printf("Ingrese la edad del estudiante:\n");
    scanf("%d",&edad);

    agregar_estudiante(nombre,apellido,edad,listaEstudiantes);
}
void opcion_buscar_por_rango(NodoEstudiante *listaEstudiantes){
    int parametro1=0;
    int parametro2=0;
    printf("Ingrese el primer numero para buscar por rango:\n");
    scanf("%d",&parametro1);
    printf("Ingrese el segundo numero para buscar por rango:\n");
    scanf("%d",&parametro2);
    buscar_por_rango_edad(listaEstudiantes,parametro1,parametro2);
}
void opcion_buscar_por_nombre(NodoEstudiante *listaEstudiantes){
    char nombre[100];
    printf("Ingrese el nombre a buscar:\n");

    scanf("%s",&nombre);
    buscar_por_nombre(listaEstudiantes, nombre);
}
void opcion_buscar_por_ID(NodoEstudiante *listaEstudiantes){
    int idSeleccionado= 0;
    int opcion=0;
    printf("Ingrese el ID del estudiante para comenzar a gestionar:\n");
    scanf("%d",&idSeleccionado);

    NodoEstudiante *estudiante = buscar_estudiante_por_id(idSeleccionado,listaEstudiantes);
    if(estudiante != NULL){
        printf("ID : %d -Nombre y apellido: %s %s - Edad: %d \n", estudiante->id,estudiante->nombre,estudiante->apellido,estudiante->edad);
    }else{
    }
}
int menuPrincipal(NodoEstudiante *listaEstudiantes, NodoMateria *listaMateria){
    int opcion;
    printf("        Menu Principal\n    1. Agregar un Estudiante \n"
           "    2. Listado de Estudiantes\n"
           "    3. Buscar estudiantes por rango de edad \n"
           "    4. Buscar un estudiante por Nombre \n"
           "    5. Buscar un estudiante por ID\n"
           "    6. Gestionar sobre un estudiante\n\n"
           "    o pulse cualquier tecla para salir \n\nIngrese la Opcion\n");

    scanf("%i",&opcion);
    if(opcion ==1) {
        opcion_agregar_estudiante(listaEstudiantes);
        int op= opcion_seguir_gestionando_o_salir(listaEstudiantes,listaMateria);
        if(op==1){
            menuPrincipal(listaEstudiantes,listaMateria);
        }

    } else if(opcion ==2){
        imprimir_lista_estudiantes(listaEstudiantes);
        int op= opcion_seguir_gestionando_o_salir(listaEstudiantes,listaMateria);
        if(op==1){
            menuPrincipal(listaEstudiantes,listaMateria);
        }

    }else if(opcion ==3){
        opcion_buscar_por_rango(listaEstudiantes);
        int op= opcion_seguir_gestionando_o_salir(listaEstudiantes,listaMateria);
        if(op==1){
            menuPrincipal(listaEstudiantes,listaMateria);
        }

    }else if(opcion ==4){
        opcion_buscar_por_nombre(listaEstudiantes);
        int op= opcion_seguir_gestionando_o_salir(listaEstudiantes,listaMateria);
        if(op==1){
            menuPrincipal(listaEstudiantes,listaMateria);
        }
    }else if(opcion ==5){
        opcion_buscar_por_ID(listaEstudiantes);

        int op= opcion_seguir_gestionando_o_salir(listaEstudiantes,listaMateria);
        if(op==1){
            menuPrincipal(listaEstudiantes,listaMateria);
        }
    }else if(opcion ==6){

        NodoEstudiante *seleccionado = opcion_seleccionar_estudiante(listaEstudiantes,listaMateria);
        opcion_gestionar_estudiante(seleccionado,listaEstudiantes,listaMateria);
            menuPrincipal(listaEstudiantes,listaMateria);
    }else{
        printf("Adios!\n");

    }
}
void inicio(){
    int cantidad=0;
    printf("Ingrese la cantidad de estudiantes con las que quiere iniciar el programa:\n");
    scanf("%d",&cantidad);
    int m=18;
    int n=70;
    char nombres[67][20] = {"ADRIAN","DAVID","MARIO","DIEGO","MARCOS","JAVIER","MARCO","BRUNO","THIAGO","ANTONIO",
                            "CARLOS","ANGEL","JUAN","GONZALO","NAHUEL","SERGIO","NICOLAS","GABRIEL","JORGE","JOSE",
                            "ADAM","SAMUEL","DARIO","HECTOR","LUCA","RODRIGO","VICTOR","FRANCISCO","IVAN","JESUS","RUBEN","RAFAEL"
            ,"MARTIN","SANTIAGO","FERNANDO","ALONSO","MATIAS","ANDRES","AXEL","OSCAR","CRISTIAN","LEONARDO","CARMEN","CARLA",
                            "ALMA","CLAUDIA","VALENTINA","LARA","OLIVIA","MIA","LOLA","JIMENA","ELENA","ADRIANA","CANDELA","MARTA","LAURA",
                            "VICTORIA","ALICIA","EVA","ANGELA","MARA","NATALIA","JULIETA","ARLET","ALEXIA","YASMIN","ISABELLA"
    };

    char apellidos[67][20]= {"GARCIA","GONZALEZ","RODRIGUEZ","FERNANDEZ","LOPEZ","MARTINEZ","SANCHEZ","PEREZ","GOMEZ",
                             "MARTIN","JIMENEZ","RUIZ","HERNANDEZ","DIAZ","MORENO","ALVAREZ","ROMERO","ALONSO","GUTIERREZ","NAVARRO",
                             "TORRES","DOMINGUEZ","VAZQUEZ","RAMOS","GIL","RAMIREZ","SERRANO","BLANCO","MOLINA","MORALES","SUAREZ","ORTEGA","DELGADO",
                             "CASTRO","ORTIZ","RUBIO","MARIN","SANZ","IGLESIAS","MEDINA","GARRIDO","CORTES","CASTILLO","SANTOS",
                             "LOZANO","GUERRERO","CANO","PRIETO","MENDEZ","CRUZ","CALVO","GALLEGO","VIDAL","LEON","MARQUEZ","HERRERA",
                             "PALACIOS","FLORES","CABRERA","CAMPOS","VEGA","FUENTES","CARRASCO","DIEZ","CABALLERO","REYES","NIETO","AGUILAR",
    };

    NodoEstudiante *lista = crear_lista_estudiante();
    while(cantidad!=0){
        int num_nombre = rand()%67 ;
        int num_apellido = rand()%67;
        int num_edad = m+rand()%(n+1-m);
        char*nombre=nombres[num_nombre];
        char*apellido=apellidos[num_apellido];
        int edad = num_edad;
        agregar_estudiante(nombre, apellido, edad,lista);
        cantidad--;
    }

    int cantidad_materias=0;
    printf("Ingrese la cantidad de materias con las que quiere iniciar el programa:\n");
    scanf("%d",&cantidad_materias);
    NodoMateria *listaMaterias = crear_lista_materia();

    char materias[28][40] ={
            "Fisica","Biologia","Anatomia y Fisiologia","Matematicas","Quimica","Ecologia","Metodologia de la Investigacion","Ciencias Sociales",
            "Geografia","Economia","Medio Ambiente","Biografias","Arte","Historia del Arte","Filosofia","Historia",
            "Etica y Valores","Literatura","Lengua Espaniola","Ingles","Informatica","Psicologia","Educacion Fisica",
            "Tecnologia","Politica","Religion","Salud","Educacion",
    };
    int correlativas=1;
    int aux=1;
    while(cantidad_materias!=0){
        if(aux ==28){
            aux=1;
            correlativas++;
        }
        char*nombre_materia=materias[aux];
        aux++;
        agregar_materia(nombre_materia,correlativas,listaMaterias);
        cantidad_materias--;
    }
    menuPrincipal(lista,listaMaterias);
}

int main() {
    inicio();
    return 0;
}
