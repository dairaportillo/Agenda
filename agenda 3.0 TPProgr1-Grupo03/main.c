// INTEGRANTES: ANTONELLA PERALTA, PORTILLO DAIRA, SANTIAGO ERNST.
//ERROR CRITICO:  falta la parte de que los DNI sean únicos. (ARREGLADO CON UNA FUNCION).

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h> //para poder escribir los nombres

#define MAXPERSONAS 100

struct registro{ //armamos una estructura para registrar a cada persona.
    int dni;
    char nombre[42]; //para poder escribir
    char apellido[42];
    int dia;
    int mes;
    int anio;
    int telefono;
};

//funcion auxiliar que nos ayuda a comparar fechas
//si la fecha compuesta por d1 m1 a1 es superior a la fecha compuesta
//por d2 m2 a2, por tanto edad1 es menor a edad2, retorna 1(verdadero)
//caso contrario retorna 0 (falso).
int menor_que(int d1, int m1, int a1, int d2, int m2, int a2){
    if(a1== a2){
        if(m1== m2) return d1> d2;
        else return m1> m2;
    }
    else return a1> a2;
}

//evalúa si 'dni' se encuentra registrado en el array 'reg'
//si esta registrado retorna 1 (true), caso contrario retorna
//0 (false)
int existe (int dni, struct registro reg [], int n){
    int i;
    for (i= 0; i< n; ++i){
        if (dni== reg [i].dni)
            return 1;
    }
    return 0;
}

int main (){
    setlocale(LC_ALL,"spanish"); // con esto se puede ver correctamente las letras con tilde y caracteres especiales.
    struct registro registro_datos[MAXPERSONAS]; // vamos a registrar 5 personas sólo para probar (max 100)
    int n= 0;

    int opc=1, contador, nuevo;
    int i=0, j, buscar, salir;

    while(opc!=0){
        printf("1. Registrar persona.\n2. Ver personas registradas.\n3. Ver personas por año.\n4. Persona más joven.\n5. Editar registro persona.\n6. Buscar persona por DNI.\n0. Salir.\n");
        printf ("\nOpción: ");
        scanf("%d", &opc);
        getchar();
        printf("\n");

        switch(opc){ //depende de la opcion que elija el usuario haremos
        case 1:
            if(n< MAXPERSONAS){
                printf("Ingrese los datos de la persona numero %d a registrar:\n", n+ 1);
                printf("DNI: ");
                scanf("%i", &registro_datos[n].dni);
                if (existe (registro_datos[n].dni, registro_datos, n)){
                    puts ("El dni ya esta registrado, intente de nuevo");
                break;
                }
                printf("Nombre: ");
                getchar();
                fgets(registro_datos[n].nombre, 40, stdin);


                printf("Apellidos: ");
                fgets(registro_datos[n].apellido, 40, stdin);

                printf("Telefono: ");
                scanf("%d", &registro_datos[n].telefono);

                printf("\nIngrese cumpleaños.\n");
                printf("Dia: ");
                scanf("%d", &registro_datos[n].dia);

                printf("Mes (ingrese solo el numero del mes): ");
                scanf("%d", &registro_datos[n].mes);

                printf("Año: ");

                scanf("%d", &registro_datos[n].anio);
                getchar();
                ++n;
            }
            else{
                printf("Máximo alcanzado, no se puede seguir añadiendo datos.\n");
            }
            break;

        case 2: // Mostrará la cantidad de persona en nuestra agenda.
            if(n== 0){ // si la cantidad de personas que registraron es igual a 0 entonces:
                printf("Aún no hay personas registradas.\n");
            }
            else{ //sino mostrarme a quiénes registrar
                printf("Total de personas registradas: %d\n", n);
                for (i = 0; i < n; i++) { // se repetira esta lista con cada dato que registramos.
                    printf("Número:    \t%d\n", i+ 1);
                    printf("DNI:      \t%d\n", registro_datos[i].dni);
                    printf("Nombres:\t%s\n", registro_datos[i].nombre);
                    printf("Apellidos:\t%s\n", registro_datos[i].apellido);
                    printf("Telefono:\t%d\n", registro_datos[i].telefono);
                    printf("Cumpleaños: %2d/%2d/%4d\n", registro_datos[i].dia, registro_datos[i].mes, registro_datos[i].anio);
                    printf ("--------------------------------\n");

                } // del for.
            } //del else;
            break; //fin del case 2.

        case 3: //listado de todas las personas nacidas en un año especifico
            printf("Ingrese año a buscar: ");
            scanf("%d", &buscar);
            getchar();

            contador=0;

            for(i= 0; i< n; i++){ //para que busque todas las personas que se registraron
                if(buscar== registro_datos[i].anio){
                    contador++; // que vaya imprimiendo en pantalla a medida que va encontrando
                    printf("Coincidencia: %d\n", contador);
                    printf("DNI:\t%d\n", registro_datos[i].dni);
                    printf("Nombres:\t%s\n", registro_datos[i].nombre);
                    printf("Apellidos:\t%s\n", registro_datos[i].apellido);
                    printf("Telefono:\t%d\n", registro_datos[i].telefono);
                    printf("Cumpleaños:%2d/%2d/%4d\n", registro_datos[i].dia, registro_datos[i].mes, registro_datos[i].anio);
                    printf ("--------------------------------\n");
                } // del if.
            } // del for.

            if (contador==0){
                printf("Sin resultados en la búsqueda."); } //if.
            break; //fin del case 3.

        case 4: // ver quien es la persona mas joven.
            if(n== 0){
                printf("La agenda se encuentra vacía.\n");
            }
            else{
                j= 0;   //se asume que la primera persona es la mas joven
                for(i= 1; i< n; ++i){
                    //si la persona en 'i' es mas joven que la de en 'j'
                    if(menor_que(registro_datos[i].dia, registro_datos[i].mes, registro_datos[i].anio,
                            registro_datos[j].dia, registro_datos[j].mes, registro_datos[j].anio)){
                        j= i;
                    }
                }
                //en este punto j es el indice de la persona mas joven,
                //asumiendo que es un dato único
                printf("La persona más joven es:\n");
                printf("DNI:\t%d\n", registro_datos[j].dni);
                printf("Nombres:\t%s\n", registro_datos[j].nombre);
                printf("Apellidos:\t%s\n", registro_datos[j].apellido);
                printf("Telefono:\t%d\n", registro_datos[j].telefono);
                printf("Cumpleaños:\t%2d/%2d/%4d\n", registro_datos[j].dia, registro_datos[j].mes, registro_datos[j].anio);
            }
            break; //fin del case 4

            /*---------------- separador para entender mejor el case 5, porque es muy largo-----------------------*/

        case 5: //Para poder editar los datos de algun usuario.
            printf("Ingrese DNI de la persona a editar datos: ");
            scanf("%i", &buscar); // buscaremos por su dni para identificarla y asi cambiar los datos.
            getchar();
            contador=0;
            for(i=0; i< n; i++){ // un ciclo para que vaya recorriendo
                if(buscar== registro_datos[i].dni) break;
            } // del for.

            // en este punto i es  el indice de la persona encontrada
            if(i< n){  //si 'i' es un índice válido

                salir= 1; //para evitar un cero alamacenado anteriromente

                while(salir!=0){ //armamos un ciclo para que se repita si es que el usuario quiere modificar mas de una cosa
                    printf("\n1. Número DNI.\n2. Nombre\n3. Apellido\n4. Telefono.\n5. Fecha de nacimiento\n0. Terminar.\n");
                    printf ("Opcion: ");
                    scanf("%d",&salir);
                    getchar();

                    switch(salir){ //armamos otro switch para que el usuario decida qué es lo que quiere editar.

                    case 1: // si quiero cambiar su dni
                        printf("Ingrese nuevo número de DNI: \n");
                        scanf("%d", &nuevo);
                        getchar();

                        for(j=0; j< n; j++){
                            if(nuevo== registro_datos[j].dni){
                                printf("%i Este número de DNI ya existe, intente con otro.\n",nuevo);
                                contador= 1;
                                break;
                            }
                        } // del for
                        if(contador==0){
                            registro_datos[i].dni= nuevo;
                            printf("Número de DNI cambiado.\n");
                        }
                        break;

                    case 2: //cambiar su nombre

                        printf("Ingrese nuevo nombre: ");
                        fgets(registro_datos[i].nombre, 40, stdin); // donde se guardara el nuevo nombre
                        registro_datos[i].nombre[strlen(registro_datos[i].nombre)- 1]= '\0';
                        printf("Nombre cambiado.\n");
                        break;

                    case 3:
                        printf("Ingrese nuevo apellido: ");
                        fgets(registro_datos[i].apellido, 40, stdin); // donde se guardara el nuevo nombre
                        registro_datos[i].apellido[strlen(registro_datos[i].apellido)- 1]= '\0';
                        printf("Apellido cambiado.\n");
                        break;

                    case 4:
                        printf("Ingrese nuevo telefono: ");
                        scanf("%d", &registro_datos[i].telefono);
                        getchar();
                        printf("Teléfono cambiado.\n");
                        break;

                    case 5:  //cambiar fecha de nacimiento
                        printf("Ingrese la nueva fecha de nacimiento:\n");
                        printf("Ingrese dia : ");
                        scanf("%d", &registro_datos[i].dia);
                        printf("Ingrese mes : ");
                        scanf("%d", &registro_datos[i].mes);
                        printf("Ingrese anio: ");
                        scanf("%d", &registro_datos[i].anio);
                        getchar();
                        printf("Fecha de nacimiento cambiada.\n");
                        break;
                    default:
                        printf("Opción incorrecta\n");
                        break;
                    } // del switch
                } // del while
            }
            else{
                printf("Registro no encontrado");
            }

            if(contador==1){
                salir=1;

            } // del if donde sirve para editar los datos del usuario.
            break;


            /*--------------------- Fin del separador del case 5 ------------------------------------*/

        case 6:
            printf("Ingrese identificación de la persona a buscar: ");
            scanf("%i", &buscar);
            getchar();
            contador=0;
            for(i= 0; i< n; i++){
                if(buscar== registro_datos[i].dni){
                    printf("DNI         : %d\n", registro_datos[i].dni);
                    printf("Nombres     : %s\n", registro_datos[i].nombre);
                    printf("Apellidos   : %s\n", registro_datos[i].apellido);
                    printf("Telefono    : %d\n", registro_datos[i].telefono);
                    printf("Cumpleaños  : %2d/%2d/%4d\n", registro_datos[i].dia, registro_datos[i].mes, registro_datos[i].anio);
                    contador++;
                } //del if
            } // del for.
            if(contador==0){
                printf("Sin resultados."); } //del if
            break; // fin del case 6

        } // del primer switch.
        printf("\n");
        system("pause"); // se espera a que el usuario presione alguna tecla para continuar con la ejecución del programa.
        system("cls"); // para limpiar la pantalla del menú.
    } // del primer while
    return 0;
}
