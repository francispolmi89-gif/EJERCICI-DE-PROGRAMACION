#include <stdio.h>

#define MAX 5
#define TAM 50

void limpiarEntrada();
int leerEntero(char mensaje[]);
float leerReal(char mensaje[]);
void leerTexto(char mensaje[], char texto[]);
int compararNombres(char a[], char b[]);
int buscarProducto(char nombres[][TAM], int n, char buscado[]);
void registrar(char nombres[][TAM], int *cantidad, float *tiempo,
               float *recursos, int *n);
void mostrar(char nombres[][TAM], int cantidad[], float tiempo[],
             float recursos[], int n);
void buscar(char nombres[][TAM], int cantidad[], float tiempo[],
            float recursos[], int n);
void editar(char nombres[][TAM], int cantidad[], float tiempo[],
            float recursos[], int n);
void eliminar(char nombres[][TAM], int cantidad[], float tiempo[],
              float recursos[], int *n);
void calcular(char nombres[][TAM], int cantidad[], float tiempo[],
              float recursos[], int n);

void limpiarEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int leerEntero(char mensaje[]) {
    int valor, correcto;
    do {
        printf("%s", mensaje);
        correcto = scanf("%d", &valor);
        if (correcto != 1) {
            printf("Error: ingrese un numero entero.\n");
            limpiarEntrada();
        } else {
            limpiarEntrada();
            if (valor < 0) {
                printf("El valor no puede ser negativo.\n");
                correcto = 0;
            }
        }
    } while (correcto != 1);
    return valor;
}

float leerReal(char mensaje[]) {
    float valor;
    int correcto;
    do {
        printf("%s", mensaje);
        correcto = scanf("%f", &valor);
        if (correcto != 1) {
            printf("Error: ingrese un numero valido.\n");
            limpiarEntrada();
        } else {
            limpiarEntrada();
            if (valor < 0) {
                printf("El valor no puede ser negativo.\n");
                correcto = 0;
            }
        }
    } while (correcto != 1);
    return valor;
}

void leerTexto(char mensaje[], char texto[]) {
    int i;
    printf("%s", mensaje);
    fgets(texto, TAM, stdin);
    for (i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == '\n') {
            texto[i] = '\0';
            break;
        }
    }
}

int compararNombres(char a[], char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return 0;
        i++;
    }
    return a[i] == b[i];
}

int buscarProducto(char nombres[][TAM], int n, char buscado[]) {
    int i;
    for (i = 0; i < n; i++) {
        if (compararNombres(nombres[i], buscado)) return i;
    }
    return -1;
}

void registrar(char nombres[][TAM], int *cantidad, float *tiempo,
               float *recursos, int *n) {
    if (*n >= MAX) {
        printf("\nNo se pueden registrar mas productos.\n");
        return;
    }

    leerTexto("Nombre del producto: ", nombres[*n]);
    if (nombres[*n][0] == '\0') {
        printf("El nombre no puede estar vacio.\n");
        return;
    }
    if (buscarProducto(nombres, *n, nombres[*n]) != -1) {
        printf("El producto ya se encuentra registrado.\n");
        return;
    }

    cantidad[*n] = leerEntero("Cantidad demandada: ");
    tiempo[*n] = leerReal("Tiempo por unidad: ");
    do {
        recursos[*n] = leerReal("Recursos por unidad: ");
        if (recursos[*n] <= 0)
            printf("Los recursos por unidad deben ser mayores que cero.\n");
    } while (recursos[*n] <= 0);

    (*n)++;
    printf("\nProducto registrado correctamente.\n");
}

void mostrar(char nombres[][TAM], int cantidad[], float tiempo[],
             float recursos[], int n) {
    int i;
    if (n == 0) {
        printf("\nNo existen productos registrados.\n");
        return;
    }
    printf("\n===== PRODUCTOS REGISTRADOS =====\n");
    for (i = 0; i < n; i++) {
        printf("\nProducto: %s\n", nombres[i]);
        printf("Cantidad: %d\n", cantidad[i]);
        printf("Tiempo por unidad: %.2f\n", tiempo[i]);
        printf("Recursos por unidad: %.2f\n", recursos[i]);
    }
}

void buscar(char nombres[][TAM], int cantidad[], float tiempo[],
            float recursos[], int n) {
    char nombre[TAM];
    int posicion;
    leerTexto("Ingrese el nombre del producto: ", nombre);
    posicion = buscarProducto(nombres, n, nombre);
    if (posicion == -1) {
        printf("\nProducto no encontrado.\n");
    } else {
        printf("\nProducto encontrado:\n");
        printf("Nombre: %s\n", nombres[posicion]);
        printf("Cantidad: %d\n", cantidad[posicion]);
        printf("Tiempo: %.2f\n", tiempo[posicion]);
        printf("Recursos: %.2f\n", recursos[posicion]);
    }
}

void editar(char nombres[][TAM], int cantidad[], float tiempo[],
            float recursos[], int n) {
    char nombre[TAM];
    int posicion, i;
    char *p;

    leerTexto("Nombre del producto que desea editar: ", nombre);
    posicion = buscarProducto(nombres, n, nombre);
    if (posicion == -1) {
        printf("\nProducto no encontrado.\n");
        return;
    }

    printf("\nIngrese los nuevos datos:\n");
    leerTexto("Nuevo nombre: ", nombre);
    if (nombre[0] == '\0') {
        printf("El nombre no puede estar vacio.\n");
        return;
    }
    if (buscarProducto(nombres, n, nombre) != -1 &&
        !compararNombres(nombres[posicion], nombre)) {
        printf("Ya existe un producto con ese nombre.\n");
        return;
    }

    p = nombres[posicion];
    i = 0;
    while (nombre[i] != '\0' && i < TAM - 1) {
        *(p + i) = nombre[i];
        i++;
    }
    *(p + i) = '\0';

    cantidad[posicion] = leerEntero("Nueva cantidad: ");
    tiempo[posicion] = leerReal("Nuevo tiempo por unidad: ");
    do {
        recursos[posicion] = leerReal("Nuevos recursos por unidad: ");
        if (recursos[posicion] <= 0)
            printf("Los recursos deben ser mayores que cero.\n");
    } while (recursos[posicion] <= 0);

    printf("\nProducto actualizado correctamente.\n");
}

void eliminar(char nombres[][TAM], int cantidad[], float tiempo[],
              float recursos[], int *n) {
    char nombre[TAM];
    int posicion, i, j;

    leerTexto("Nombre del producto que desea eliminar: ", nombre);
    posicion = buscarProducto(nombres, *n, nombre);
    if (posicion == -1) {
        printf("\nProducto no encontrado.\n");
        return;
    }

    for (i = posicion; i < *n - 1; i++) {
        j = 0;
        while (nombres[i + 1][j] != '\0') {
            nombres[i][j] = nombres[i + 1][j];
            j++;
        }
        nombres[i][j] = '\0';
        cantidad[i] = cantidad[i + 1];
        tiempo[i] = tiempo[i + 1];
        recursos[i] = recursos[i + 1];
    }
    (*n)--;
    printf("\nProducto eliminado correctamente.\n");
}

void calcular(char nombres[][TAM], int cantidad[], float tiempo[],
              float recursos[], int n) {
    float tiempoTotal = 0, recursosTotales = 0;
    float tiempoDisponible, recursosDisponibles;
    int i;

    if (n == 0) {
        printf("\nNo hay productos para calcular.\n");
        return;
    }

    for (i = 0; i < n; i++) {
        tiempoTotal += cantidad[i] * tiempo[i];
        recursosTotales += cantidad[i] * recursos[i];
    }

    printf("\n===== DISPONIBILIDAD DE FABRICA =====\n");
    printf("Tiempo total requerido: %.2f\n", tiempoTotal);
    printf("Recursos totales requeridos: %.2f\n", recursosTotales);

    tiempoDisponible = leerReal("\nTiempo disponible: ");
    recursosDisponibles = leerReal("Recursos disponibles: ");

    printf("\n===== RESULTADOS =====\n");
    if (tiempoTotal <= tiempoDisponible &&
        recursosTotales <= recursosDisponibles) {
        printf("La fabrica SI puede cumplir la demanda.\n");
    } else {
        printf("La fabrica NO puede cumplir la demanda.\n");
        if (tiempoTotal > tiempoDisponible)
            printf("Tiempo adicional necesario: %.2f\n",
                   tiempoTotal - tiempoDisponible);
        if (recursosTotales > recursosDisponibles)
            printf("Recursos adicionales necesarios: %.2f\n",
                   recursosTotales - recursosDisponibles);
    }
}

int main() {
    char nombres[MAX][TAM];
    int cantidad[MAX];
    float tiempo[MAX], recursos[MAX];
    int n = 0, opcion;

    do {
        printf("\n========== SISTEMA DE PRODUCCION ==========\n");
        printf("1. Registrar producto\n");
        printf("2. Mostrar productos\n");
        printf("3. Buscar producto\n");
        printf("4. Editar producto\n");
        printf("5. Eliminar producto\n");
        printf("6. Calcular produccion\n");
        printf("7. Salir\n");

        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion) {
            case 1:
                registrar(nombres, cantidad, tiempo, recursos, &n);
                break;
            case 2:
                mostrar(nombres, cantidad, tiempo, recursos, n);
                break;
            case 3:
                buscar(nombres, cantidad, tiempo, recursos, n);
                break;
            case 4:
                editar(nombres, cantidad, tiempo, recursos, n);
                break;
            case 5:
                eliminar(nombres, cantidad, tiempo, recursos, &n);
                break;
            case 6:
                calcular(nombres, cantidad, tiempo, recursos, n);
                break;
            case 7:
                printf("\nGracias por utilizar el sistema.\n");
                break;
            default:
                printf("\nOpcion no valida.\n");
        }
    } while (opcion != 7);

    return 0;
}