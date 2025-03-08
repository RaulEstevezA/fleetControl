#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#define MAX_VEHICULOS 500


#ifdef _WIN32
#include <windows.h> // función sleep para Windows
#else
#include <unistd.h> // función sleep para macOS
#endif

void esperar(float segundos) {
    #ifdef _WIN32
        Sleep((int)(segundos * 1000)); // sleep para Windows
    #else
        usleep((int)(segundos * 1000000)); // sleep para Mac
    #endif
}

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls"); // comando para Windows
    #else
        system("clear"); // comando para Mac
    #endif
}


// vehiculos
typedef struct { 
    char matriculaVehiculo[9]; // un espacio más para almacenar el \0 del scanf
    char tipoCombustible[10];    
    float kilometrajeTotal;      
    struct tm fechaAdquisicion;   
    float costoAdquisicion;      
    bool estadoOperativo;        
} tVehiculo;


// flota
typedef struct {
    char nombreEmpresa[100]; 
    int codigoPostalSede;    
    char telefonoContacto[10];   
    tVehiculo vehiculosFlota[MAX_VEHICULOS];     
    int cantidadActualVehiculo;        
} tFlota;


void kilometrajePorCosto(tFlota *flota);
void superarKilometros(tFlota *flota);
void imprimirMenu();
void imprimirMenuModificacion();
void darDeAltaUnaFlota(tFlota *flota);
void comprobarCodigoPostal(int *codigoPostal);
void comprobarTelefonoContacto(char *telefono);
void darDeAltaUnVehiculo(tFlota *flota);
void comprobarMatricula(tFlota *flota, int cantidadActual, char *matricula);
void comprobarCombustible(char *combustibe);
void comprobarKM(float *km);
void comprobarFechaAdquisicion(struct tm *fecha1);
void comprobarCostoAdqusicion(float *costo);
void comprobarAnyo(int *anyo);
void borrarUnVehiculo(tFlota *flota);
void modificarVehiculo(tFlota *flota);
void listarVehiculos(tFlota *flota);
void listarPorKilometraje(tFlota *flota);
void vehiculosAnyo(tFlota *flota);


int main(){
    
    // mensaje bienvenida, imprimido solo 1 vez
    printf("Programa de gestion de flotas para empresas.\n\n");
    int menu;
    int cantidad = 0;
    int flotaCreada = 0;
    tFlota flota1;

    do{
        //imprimir menu cada vuelta
        imprimirMenu(); 
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                // dar de alta una flota
                if(flotaCreada == 0){
                    limpiarPantalla();
                    printf("Has elegido dar de alta una flota.\n");
                    esperar(1);
                    darDeAltaUnaFlota(&flota1);
                    flotaCreada = 1;
                    break;
                } else {
                    printf("Ya hay una flota creada.\n");
                    break;
                }
                

            case 2:
                // dar de alta un vehiculo
                if(flotaCreada == 0){
                    printf("Primero hay que dar de alta una flota\n");
                    break;
                } else{
                    limpiarPantalla();
                    printf("Has elegido dar de alta un vehiculo.\n");
                    esperar(1);
                    darDeAltaUnVehiculo(&flota1);
                    break;

                }
                

            case 3:
                // borrar un vehiculo
                if(flotaCreada == 0){
                    printf("Primero hay que dar de alta una flota\n");
                    break;
                } else{
                    limpiarPantalla();
                    printf("Has elegido borrar un vehiculo.\n");
                    esperar(1);
                    borrarUnVehiculo(&flota1);
                    break;
                }
               

            case 4:
                // modificar un vehiculo
                if(flotaCreada == 0){
                    printf("Primero hay que dar de alta una flota\n");
                    break;
                } else{
                    limpiarPantalla();
                    printf("Has elegido modificar un vehiculo.\n");
                    esperar(1);
                    modificarVehiculo(&flota1);
                    break;
                }
                

            case 5:
                // codigo para listar vehiculos
                if(flotaCreada == 0){
                    printf("Primero hay que dar de alta una flota\n");
                    break;
                } else{
                    limpiarPantalla();
                    printf("Has elegido listar los vehículos.\n");
                    esperar(1);
                    listarVehiculos(&flota1);
                    break;
                }
                

            case 6:
                // codigo para listar vehiculos que superen un kilometraje
                if(flotaCreada == 0){
                    printf("Primero hay que dar de alta una flota\n");
                    break;
                } else{
                    limpiarPantalla();
                    printf("Has elegido listar vehiculos que superen un kilometraje.\n");
                    esperar(1);
                    listarPorKilometraje(&flota1);
                    break;
                }

            case 7:
                // codigo para listar vehiculos de un año
                if(flotaCreada == 0){
                    printf("Primero hay que dar de alta una flota\n");
                    break;
                } else{
                    limpiarPantalla();
                    printf("Has elegido listar vehículos de un año.\n");
                    esperar(1);
                    vehiculosAnyo(&flota1);
                    break;
                }

            case 8:
                // ratio coste km
                if(flotaCreada == 0){
                    printf("Primero hay que dar de alta una flota\n");
                    break;
                } else{
                    limpiarPantalla();
                    printf("Has elegido ratio de coste por kilometros de los vehiculos.\n");
                    esperar(1);
                    kilometrajePorCosto(&flota1);
                    break;
                }

            case 9:
                if(flotaCreada == 0){
                    printf("Primero hay que dar de alta una flota\n");
                    break;
                } else{
                    limpiarPantalla();
                    printf("Has elegido ver el numero de vehículos que superen los kilometros que vas a introducir.\n");
                    esperar(1);
                    superarKilometros(&flota1);
                    break;
                }

            case 0:
                printf("Saliendo del menu.\n");
                break;

            default:
                printf("Error, solo se aceptan numeros del 0 al 9. Introduzca un numero del 0 al 9.\n\n");
                break;
        }
    } while (menu != 0);
    return 0;
}


void kilometrajePorCosto(tFlota *flota){
    // comprobar que hay vehiculos
    if(flota->cantidadActualVehiculo == 0){
        printf("La flota no tiene ningun vehiculo actualmente.\n");
        return;
    } 

    float mejorRatio = 9999999999;
    float ratio = 0;
    int posicion = 0;

    for (int i = 0; i < flota->cantidadActualVehiculo; i++) {
        if (flota->vehiculosFlota[i].kilometrajeTotal > 0) {
            ratio = flota->vehiculosFlota[i].costoAdquisicion / flota->vehiculosFlota[i].kilometrajeTotal;
            if (ratio < mejorRatio) {
                mejorRatio = ratio;
                posicion = i;
            }
        }
    }

    printf("El mejor ratio es %.4f realizado por el vehiculo:\n", mejorRatio);
    printf("%s, %s, %.2f km, %.2f €, ", 
           flota->vehiculosFlota[posicion].matriculaVehiculo,
           flota->vehiculosFlota[posicion].tipoCombustible, 
           flota->vehiculosFlota[posicion].kilometrajeTotal, 
           flota->vehiculosFlota[posicion].costoAdquisicion);

    struct tm fecha = flota->vehiculosFlota[posicion].fechaAdquisicion;
    printf("%02d/%02d/%04d, ", fecha.tm_mday, fecha.tm_mon + 1, fecha.tm_year + 1900);

    if (flota->vehiculosFlota[posicion].estadoOperativo == 1) {
        printf("activo.\n");
    } else {
        printf("inactivo.\n");
    }
}


void superarKilometros(tFlota *flota){
    // comprobar que hay vehiculos
    if(flota->cantidadActualVehiculo == 0){
        printf("La flota no tiene ningun vehiculo actualmente.\n");
        return;
    }

    float km;
    int cantidad = 0;
    comprobarKM(&km);

    
    for (int i = 0; i < flota->cantidadActualVehiculo; i++)
    {
        if(flota->vehiculosFlota[i].kilometrajeTotal > km){
            cantidad++;
        }
    }
    
    printf("Hay un total de %d vehiculos que superan los %.2f km\n", cantidad, km);
}


void imprimirMenu(){
    printf("Introduzca un numero para escoger una funcion del menu:\n\n"
           "1. Dar de alta una flota\n"
           "2. Dar de alta el vehiculo en una flota\n"
           "3. Borrar un vehiculo de una flota\n"
           "4. Modificar los datos de un vehiculo de una flota\n"
           "5. Listar los vehiculos de una flota\n"
           "6. Listar los vehiculos que superen los kilometros introducidos por el usuario\n"
           "7. Listar los vehiculos para un año facilitado por el usuario\n"
           "8. Obtener el ratio y el vehiculo con mejor ratio de coste por kilometros realizados\n"
           "9. Obtener la cantidad de vehiculos que superan uno kilometros introducidos\n\n"
           "Introducir 0 para salir del menu\n\n");
}


void imprimirMenuModificacion(){
    printf("Introduzca un numero para escoger una funcion del menu:\n\n"
           "1. Modificar matricula\n"
           "2. Modificar tipo de combustible\n"
           "3. Modificar kilometros\n"
           "4. Modificar fecha adquisicion\n"
           "5. Modificar coste de adquisicion\n"
           "6. Modificar estado operativo\n"
           "7. Modificar todo\n"
           "Introducir 0 para salir del menu\n\n");
} 


void darDeAltaUnaFlota(tFlota *flota){
    printf("Introduce el nombre de la empresa: ");
    fgets(flota->nombreEmpresa, 100, stdin);
    while (getchar() != '\n');

    comprobarCodigoPostal(&flota->codigoPostalSede);
    comprobarTelefonoContacto(flota->telefonoContacto);
  
    flota->cantidadActualVehiculo = 0;
}


void darDeAltaUnVehiculo(tFlota *flota) {
    if (flota->cantidadActualVehiculo >= MAX_VEHICULOS) {
        printf("Alcanzado el maximo de vehiculos.\n");
        return;
    }
    tVehiculo *nuevoVehiculo = &flota->vehiculosFlota[flota->cantidadActualVehiculo];

    comprobarMatricula(flota, flota->cantidadActualVehiculo, nuevoVehiculo->matriculaVehiculo);
    comprobarCombustible(nuevoVehiculo->tipoCombustible);
    comprobarKM(&nuevoVehiculo->kilometrajeTotal);     
    comprobarFechaAdquisicion(&nuevoVehiculo->fechaAdquisicion);
    comprobarCostoAdqusicion(&nuevoVehiculo->costoAdquisicion);

    nuevoVehiculo->estadoOperativo = 1;

    flota->cantidadActualVehiculo++;
}


void comprobarCodigoPostal(int *codigoPostal1) {
    char numeros[20];
    int valido;


    while(1){
        printf("Introduce el codigo postal de la sede: ");
        fgets(numeros, 20, stdin); 

        numeros[strcspn(numeros, "\n")] = '\0';

        valido = 1;


        for (int i = 0; i < strlen(numeros); i++) {
            if (!isdigit(numeros[i])) {
                valido = 0; 
                break;
            }
        }


        // no se sale del bucle si no se introducen numeros
        if (valido == 1) {
               *codigoPostal1 = atoi(numeros);
               break;
        }

        // solo se imprime si no es valido
        printf("Error: Solo se permiten numeros. Intentalo de nuevo.\n");
    }
}


void comprobarTelefonoContacto(char *telefono){
    char telefono2[12];
    int valido;


    while(1){
        printf("Introduce el telefono de contacto (9 digitos sin espacios): ");
        fgets(telefono2, 12, stdin); 

        telefono2[strcspn(telefono2, "\n")] = '\0';

        if (strlen(telefono2) != 9) {
            printf("Los telefonos tienen 9 digitos. Intentalo de nuevo.\n");
            continue; // volver a empezar
        }

        valido = 1;

        for (int i = 0; i < strlen(telefono2); i++) {
            if (!isdigit(telefono2[i])) {
                valido = 0; 
                break;
            }
        }


        // no se sale del bucle si no se introducen numeros
        if (valido == 1) {
            strcpy(telefono, telefono2);
            break;
        }

        // solo se imprime si no es valido
        printf("Solo se permiten 9 numeros sin espacios. Intentalo de nuevo.\n");
    }
}


void comprobarMatricula(tFlota *flota, int cantidadActual, char *matricula) {
    int valida;

    do {
        while (getchar() != '\n');
        printf("Introduce la matricula del vehiculo (max 8 caracteres): ");
        fgets(matricula, 9, stdin);

        matricula[strcspn(matricula, "\n")] = '\0';

        // comprobar si existe la matricula
        valida = 1; 
        for (int i = 0; i < cantidadActual; i++) {
            if (strcmp(flota->vehiculosFlota[i].matriculaVehiculo, matricula) == 0) {
                printf("Error: La matricula ya existe en la flota. Intenta de nuevo.\n");
                valida = 0; 
                break;
            }
        }
    } while (valida != 1); 
}


void comprobarCombustible(char *combustible) {
    int tipo;

    while (1) {
        printf("Introduce el tipo de combustible (1, 2 o 3):\n"
               "1. Gasolina\n"
               "2. Diesel\n"
               "3. Electrico\n");
        scanf("%d", &tipo);

        
        if (tipo != 1 && tipo != 2 && tipo != 3) {
            printf("Introducir solo un 1, un 2 o un 3.\n");
            while (getchar() != '\n'); 
            continue;
        }


        if (tipo == 1) {
            strcpy(combustible, "Gasolina");
        } else if (tipo == 2) {
            strcpy(combustible, "Diesel");
        } else if (tipo == 3) {
            strcpy(combustible, "Electrico");
        }
        break;
    }
}


void comprobarKM(float *km){

    char km2[50]; 

    while (1) {
        while (getchar() != '\n');
        printf("Introduce los kilometros con decimales: ");
        fgets(km2, sizeof(km2), stdin);
        km2[strcspn(km2, "\n")] = '\0'; 

        
        char *endptr;
        *km = strtof(km2, &endptr);

        
        if (*endptr == '\0') { 
            break;
        } else {
            printf("Introduce un numero valido.\n");
        }
    }

}


void comprobarFechaAdquisicion(struct tm *fecha1){

    char fecha[12];
    int valido;

    while (1) {
        printf("Introduce la fecha de adquisicion DD/MM/YYYY: ");
        fgets(fecha, sizeof(fecha), stdin);

        fecha[strcspn(fecha, "\n")] = '\0';


        if (strlen(fecha) != 10) {
            printf("Error: La fecha debe tener exactamente 10 caracteres DD/MM/YYYY.\n");
            continue;
        }


        // validar formato
        valido = 1;
        for (int i = 0; i < 10; i++) {
            if ((i == 2 || i == 5)) {
                if (fecha[i] != '/') {
                    valido = 0;
                    break;
                }
            } else {
                if (!isdigit(fecha[i])) {
                    valido = 0;
                    break;
                }
            }
        }


        if (valido == 1) {
            // extraer valores de día, mes y año
            int dia, mes, anio;
            sscanf(fecha, "%2d/%2d/%4d", &dia, &mes, &anio);

            
            fecha1->tm_mday = dia;
            fecha1->tm_mon = mes - 1; // tm_mon va de 0 a 11
            // tm_year va desde 1900, hay que restar 1900 para no tener problemas despues con mktime o strftime 
            // pues sino, al introducir una fecha como 2024 seria interpretado como 3924 
            fecha1->tm_year = anio - 1900; 
            fecha1->tm_hour = 0;
            fecha1->tm_min = 0;
            fecha1->tm_sec = 0;
            break;
        }


        printf("La fecha debe seguir el formato DD/MM/YYYY.\n");
    }
}


void comprobarCostoAdqusicion(float *costo){

    char costo2[50]; 

    while (1) {
        printf("Introduce el coste con decimales: ");
        fgets(costo2, sizeof(costo2), stdin);
        costo2[strcspn(costo2, "\n")] = '\0'; 

        
        char *endptr;
        *costo = strtof(costo2, &endptr);

        
        if (*endptr == '\0') { 
            break;
        } else {
            printf("Introduce un numero valido.\n");
        }
    }

}


void comprobarAnyo(int *anyo) {
    char fecha[50];
    char *endptr;

    while (1) {
        printf("Introduce un año: ");
        fgets(fecha, sizeof(fecha), stdin);

        fecha[strcspn(fecha, "\n")] = '\0';

        *anyo = strtol(fecha, &endptr, 10); 

        if (*endptr == '\0') {
            break;
        } else {
            printf("Introduce un numero entero valido (maximo 9 cifras).\n");
        }
    }
}


void borrarUnVehiculo(tFlota *flota){

    // comprobar que hay vehiculos
    if(flota->cantidadActualVehiculo == 0){
        printf("La flota no tiene ningun vehiculo actualmente.\n");
        return;
    } 
    
    char matricula[9];
    int coincidencia = 0;
    while (getchar() != '\n');
    printf("Introduce la matrícula del vehiculo a borrar (8 caracteres): ");
    fgets(matricula, sizeof(matricula), stdin);

    matricula[strcspn(matricula, "\n")] = '\0';

    // buscar la matrícula
    for(int i = 0; i < flota->cantidadActualVehiculo; i++){
        if(strcmp(flota->vehiculosFlota[i].matriculaVehiculo, matricula) == 0){

            for(int j = i; j < flota->cantidadActualVehiculo - 1; j++){
                flota->vehiculosFlota[j] = flota->vehiculosFlota[j +1];
            }

            coincidencia = 1;
            flota->cantidadActualVehiculo--;
            printf("Vehiculo con matricula %s borrado.\n", matricula);
            break;
        }
        
    }
    
    if(coincidencia == 0){
        printf("No hay ningun vehiculo con esta matricula.\n");
    }
}


void modificarVehiculo(tFlota *flota){
    // comprobar que hay vehiculos
    if(flota->cantidadActualVehiculo == 0){
        printf("La flota no tiene ningun vehiculo actualmente.\n");
        return;
    } 

    
    char matricula[9];
    int posicion, menu = -1;
    int coincidencia = 0;
    while (getchar() != '\n');
    printf("Introduce la matrícula del vehiculo a modificar (8 caracteres): ");
    fgets(matricula, sizeof(matricula), stdin);

    matricula[strcspn(matricula, "\n")] = '\0';

    // buscar la matrícula
    for(int i = 0; i < flota->cantidadActualVehiculo; i++){
        if(strcmp(flota->vehiculosFlota[i].matriculaVehiculo, matricula) == 0){
            coincidencia = 1;
            posicion = i;

            do{
                int activos = 0;
                imprimirMenuModificacion();
                scanf("%d", &menu);
                while (getchar() != '\n');

                switch (menu){
                    case 1:
                        // modificar matricula
                        limpiarPantalla();
                        printf("Ha escogido modificar matrícula\n");
                        esperar(1);
                        comprobarMatricula(flota, flota->cantidadActualVehiculo, flota->vehiculosFlota[posicion].matriculaVehiculo);
                        break;

                    case 2:
                        // modificar tipo de combustible
                        limpiarPantalla();
                        printf("Ha escogido modificar tipo de combustible\n");
                        esperar(1);
                        comprobarCombustible(flota->vehiculosFlota[posicion].tipoCombustible);
                        break;

                    case 3:
                        // modificar kilometraje
                        limpiarPantalla();
                        printf("Ha escogido modificar los kilometros\n");
                        esperar(1);
                        comprobarKM(&flota->vehiculosFlota[posicion].kilometrajeTotal);
                        break;

                    case 4:
                        //modificar fecha de adquisicion
                        limpiarPantalla();
                        printf("Ha escogido modificar los kilometros\n");
                        esperar(1);
                        comprobarFechaAdquisicion(&flota->vehiculosFlota[posicion].fechaAdquisicion);
                        break;

                    case 5:
                        // modificar coste adquisicion
                        limpiarPantalla();
                        printf("Ha escogido modificar la fecha de adquisicion\n");
                        esperar(1);
                        comprobarCostoAdqusicion(&flota->vehiculosFlota[posicion].costoAdquisicion);
                        break;

                    case 6:
                        // modificar estado operativo
                        limpiarPantalla();
                        printf("Ha escogido modificar el estado operativo del vehiculo\n");
                        esperar(1);
                        do{
                            printf("Quiere asignar este vehiculo como inactivo (inserte 1 o 2)?\n"
                                "1. Si\n"
                                "2. No\n");
                            scanf("%d", &activos);
                            while (getchar() != '\n');

                            if(activos != 1 && activos != 2){
                                printf("Responda solo con un '1' o con un '2'.\n");
                            } else {
                                flota->vehiculosFlota[posicion].estadoOperativo = activos -1;
                            }
                        } while (activos != 1 && activos != 2);
                        break;

                    case 7:
                        // modificar todo
                        limpiarPantalla();
                        printf("Ha escogido modificar todo\n");
                        esperar(1);
                        comprobarMatricula(flota, flota->cantidadActualVehiculo, flota->vehiculosFlota[posicion].matriculaVehiculo);
                        comprobarCombustible(flota->vehiculosFlota[posicion].tipoCombustible);
                        comprobarKM(&flota->vehiculosFlota[posicion].kilometrajeTotal);
                        comprobarFechaAdquisicion(&flota->vehiculosFlota[posicion].fechaAdquisicion);
                        comprobarCostoAdqusicion(&flota->vehiculosFlota[posicion].costoAdquisicion);
                        do{
                            printf("Quiere asignar este vehiculo como inactivo (inserte 1 o 2)?\n"
                                "1. Si\n"
                                "2. No\n");
                            scanf("%d", &activos);
                            while (getchar() != '\n');

                            if(activos != 1 && activos != 2){
                                printf("Responda solo con un '1' o con un '2'.\n");
                            } else {
                                flota->vehiculosFlota[posicion].estadoOperativo = activos -1;
                            }
                        } while (activos != 1 && activos != 2);
                        break;

                    case 0:
                        // volver atras
                        printf("Volviendo al menu principal...\n");
                        break;

                    default:
                        printf("Opcion no valida. Por favor, elija una opcion del menu.\n");
                        break;
                }
            } while (menu != 0);
        }
        
    }
    
    if(coincidencia == 0){
        printf("No hay ningun vehiculo con esta matricula.\n");
    }
}


void listarVehiculos(tFlota *flota){

    // comprobar que hay vehiculos
    if(flota->cantidadActualVehiculo == 0){
        printf("La flota no tiene ningun vehiculo actualmente.\n");
        return;
    } 

    int activos = 0;
    int indice = 1;


    do{
        printf("Quiere incluir los vehiculos inactivos (inserte 1 o 2)?\n"
               "1. Si\n"
               "2. No\n");
        scanf("%d", &activos);
        while (getchar() != '\n');

        if(activos != 1 && activos != 2){
            printf("Responda solo con un '1' o con un '2'.\n");
        }
    } while (activos != 1 && activos != 2);

    
    if(activos == 1){
        for(int i = 0; i < flota->cantidadActualVehiculo; i++){
            printf("%d. %s, %s, %.2f km, %.2f €, ", i+1, 
            flota->vehiculosFlota[i].matriculaVehiculo,
            flota->vehiculosFlota[i].tipoCombustible, 
            flota->vehiculosFlota[i].kilometrajeTotal, 
            flota->vehiculosFlota[i].costoAdquisicion);
            
            struct tm fecha = flota->vehiculosFlota[i].fechaAdquisicion;
            printf("%02d/%02d/%04d, ", fecha.tm_mday, fecha.tm_mon + 1, fecha.tm_year + 1900);

            if(flota->vehiculosFlota[i].estadoOperativo == 1){
                printf("activo.\n");
            } else{
                printf("inactivo.\n");
            }
        }
    } else {

        for(int i = 0; i < flota->cantidadActualVehiculo; i++){
            if(flota->vehiculosFlota[i].estadoOperativo == 1){
                printf("%d. %s, %s, %.2f km, %.2f €, ", indice, 
                flota->vehiculosFlota[i].matriculaVehiculo,
                flota->vehiculosFlota[i].tipoCombustible, 
                flota->vehiculosFlota[i].kilometrajeTotal, 
                flota->vehiculosFlota[i].costoAdquisicion);
                
                struct tm fecha = flota->vehiculosFlota[i].fechaAdquisicion;
                printf("%02d/%02d/%04d.\n", fecha.tm_mday, fecha.tm_mon + 1, fecha.tm_year + 1900);

                indice++;
            }
        }
    }
}
    

void listarPorKilometraje(tFlota *flota){
    // comprobar que hay vehiculos
    if(flota->cantidadActualVehiculo == 0){
        printf("La flota no tiene ningun vehiculo actualmente.\n");
        return;
    } 

    int indice = 1;
    int coincidencias = 0;
    int activos = 0;
    float km;
    comprobarKM(&km);


    do{
        printf("Quiere incluir los vehiculos inactivos (inserte 1 o 2)?\n"
               "1. Si\n"
               "2. No\n");
        scanf("%d", &activos);
        while (getchar() != '\n');

        if(activos != 1 && activos != 2){
            printf("Responda solo con un '1' o con un '2'.\n");
        }
    } while (activos != 1 && activos != 2);

    
    if(activos == 1){
        for(int i = 0; i < flota->cantidadActualVehiculo; i++){
        if(km < flota->vehiculosFlota[i].kilometrajeTotal){
            printf("%d. %s, %s, %.2f km, %.2f €, ", indice, 
            flota->vehiculosFlota[i].matriculaVehiculo,
            flota->vehiculosFlota[i].tipoCombustible, 
            flota->vehiculosFlota[i].kilometrajeTotal, 
            flota->vehiculosFlota[i].costoAdquisicion);
            
            struct tm fecha = flota->vehiculosFlota[i].fechaAdquisicion;
            printf("%02d/%02d/%04d, ", fecha.tm_mday, fecha.tm_mon + 1, fecha.tm_year + 1900);

            if(flota->vehiculosFlota[i].estadoOperativo == 1){
                printf("activo.\n");
            } else{
                printf("inactivo.\n");
            }
            indice++;
            coincidencias = 1;
        }  
    }
    } else {

        for(int i = 0; i < flota->cantidadActualVehiculo; i++){
            if(flota->vehiculosFlota[i].estadoOperativo == 1){
                if(km < flota->vehiculosFlota[i].kilometrajeTotal){
                    printf("%d. %s, %s, %.2f km, %.2f €, ", indice, 
                    flota->vehiculosFlota[i].matriculaVehiculo,
                    flota->vehiculosFlota[i].tipoCombustible, 
                    flota->vehiculosFlota[i].kilometrajeTotal, 
                    flota->vehiculosFlota[i].costoAdquisicion);
                    
                    struct tm fecha = flota->vehiculosFlota[i].fechaAdquisicion;
                    printf("%02d/%02d/%04d.\n", fecha.tm_mday, fecha.tm_mon + 1, fecha.tm_year + 1900);

                    indice++;
                    coincidencias = 1;
                }
            }
        }
    }

    if (coincidencias == 0) {
        printf("No hay vehiculos que superen los %.2f km.\n", km);
    }
}


void vehiculosAnyo(tFlota *flota){
    // comprobar que hay vehiculos
    if(flota->cantidadActualVehiculo == 0){
        printf("La flota no tiene ningun vehiculo actualmente.\n");
        return;
    } 

    while (getchar() != '\n');
    int anyo;
    int coincidencias = 0;
    int indice = 1;
    int activos = 0;

    comprobarAnyo(&anyo);

    do{
        printf("Quiere incluir los vehiculos inactivos (inserte 1 o 2)?\n"
               "1. Si\n"
               "2. No\n");
        scanf("%d", &activos);
        while (getchar() != '\n');

        if(activos != 1 && activos != 2){
            printf("Responda solo con un '1' o con un '2'.\n");
        }
    } while (activos != 1 && activos != 2);

    
    if(activos == 1){
        for(int i = 0; i < flota->cantidadActualVehiculo; i++){

            struct tm fecha = flota->vehiculosFlota[i].fechaAdquisicion;
        
            if(anyo == (fecha.tm_year + 1900)){
                printf("%d. %s, %s, %.2f km, %.2f €, ", indice, 
                flota->vehiculosFlota[i].matriculaVehiculo,
                flota->vehiculosFlota[i].tipoCombustible, 
                flota->vehiculosFlota[i].kilometrajeTotal, 
                flota->vehiculosFlota[i].costoAdquisicion);
                
                printf("%02d/%02d/%04d, ", fecha.tm_mday, fecha.tm_mon + 1, fecha.tm_year + 1900);

                if(flota->vehiculosFlota[i].estadoOperativo == 1){
                    printf("activo.\n");
                } else{
                    printf("inactivo.\n");
                }
                indice++;
                coincidencias = 1;
            }  
        }
    } else {

        for(int i = 0; i < flota->cantidadActualVehiculo; i++){
            if(flota->vehiculosFlota[i].estadoOperativo == 1){
                struct tm fecha = flota->vehiculosFlota[i].fechaAdquisicion;
        
                if(anyo == (fecha.tm_year + 1900)){
                    printf("%d. %s, %s, %.2f km, %.2f €, ", indice, 
                    flota->vehiculosFlota[i].matriculaVehiculo,
                    flota->vehiculosFlota[i].tipoCombustible, 
                    flota->vehiculosFlota[i].kilometrajeTotal, 
                    flota->vehiculosFlota[i].costoAdquisicion);
                    
                    printf("%02d/%02d/%04d. \n", fecha.tm_mday, fecha.tm_mon + 1, fecha.tm_year + 1900);

                    indice++;
                    coincidencias = 1;
                }
            }
        }
    }


    if (coincidencias == 0) {
        printf("No hay vehiculos del año %d.\n", anyo);
    }
}

