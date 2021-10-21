# TP Final Algoritmos y programacion 3
### _Sistema de estudiantes_

#### Link Youtube:
- Parte 1
    - https://youtu.be/RvmBdd4_7K8
- Parte 2
    - https://youtu.be/ZMkWfQoyz-o

##### Alumnos:
- ###### Giambra Matías.
- ###### Palacios Nahuel.

## Arquitectura:
El sistema utiliza __Linkedlist__ para estudiantes y materias.
A los estudiantes, se le asigna una materia de una __Linkedlist__, de esta manera no se genera una materia por usuario, sino que se hace referencia a un __NodoMateria__, de esta manera optimizamos la memoria del sistema.
Además, agregamos un identificador único __(ID)__ para estudiantes y materias, de esta manera evitamos los errores en caso que existan dos __Estudiantes__ con el mismo nombre.
Al eliminar nodos, se libera la memoria para optimizar la misma.
Gracias a todo esto, el sistema siempre es manejable, ya que podémos acceder a todos los estudiantes y materias por su __identificador unico__. Su única limitante es la capacidad de memoria de cada computadora.

## Features Obligatorias:
- Dar de alta
- Listar estudiantes
- Buscar estudiantes por nombre
- Buscar estudiantes por rango de edad
- Dar de alta y listar materias
- Anotarse en una materia
- Rendir una materia

## Features Adicionales:
- Dar de baja a estudiante
- Asignado ID a cada materia y estudiante.
- Buscar estudiantes por ID
- Nota en materias.
- Mostrar listado de materias pendientes (Es decir, materias sin nota asignada o desaprobadas).
- Mostrar listado completo de materias por estudiante (Todas las materias aprobadas, desaprobadas o no rendidas).
- Correlatividad en materias (No puedo anotarme en Matematica 2, si no estoy inscripto en Matematica 1).
- Mostrar estadisticas (Porcentaje de efectividad de aprobacion).
- Generar estudiantes de prueba y materias aleatorias de forma masiva
    - Se realizaron pruebas con 50.000 estudiantes y 50.000 materias en el video. Paralelamente se realizo una prueba masiva de 500.000 estudiantes y 500.000 materias, y el sistema lo soporto.
    





