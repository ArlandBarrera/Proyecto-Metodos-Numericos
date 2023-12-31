#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

// Secuencias de escape ANSI para colores y limpieza de pantalla
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define CLEAR   "\e[1;1H\e[2J"

void clear_screen() {
    printf("%s", CLEAR);
    fflush(stdout);
}

bool validar_entrada(double *valor) {
    return scanf("%lf", valor) == 1;
}

void imprimir_animacion() {
	int i;
    char anim[] = "|/-\\";
    for(i = 0; i < 10; i++) {
        printf("\r%c", anim[i % sizeof(anim)]);
        fflush(stdout);
        usleep(100000); // 0.1 segundos
    }
    printf("\r");
}

void guardar_resultado(double y) {
    FILE *file = fopen("resultado_interpolacion.txt", "w");
    if(file == NULL) {
        printf(RED "Error al abrir el archivo para escribir.\n" RESET);
        return;
    }
    fprintf(file, "La temperatura estimada a las 3:00 PM es: %.2f grados Celsius\n", y);
    fclose(file);
    printf(GREEN "Resultado guardado en 'resultado_interpolacion.txt'.\n" RESET);
}

void mostrar_ayuda() {
    printf(CYAN "\nLa interpolacion lineal es un m�todo para estimar valores desconocidos entre dos puntos conocidos.\n" RESET);
}

int main() {
    double y0, y1, y;
    char opcion;
   system("color 70");
    bool continuar = true;

    while(continuar) {
        clear_screen();
        printf(YELLOW "EJEMPLO BREVE SOBRE INTERPOLACION LINEAL\n\n" RESET);
        printf(GREEN "[1] Realizar interpolacion lineal\n" RESET);
        printf(BLUE "[2] Ayuda\n" RESET);
        printf(RED "[3] Salir\n\n" RESET);
        printf("Seleccione una opcion: ");
        scanf(" %c", &opcion);

        switch(opcion) {
            case '1':
                printf(GREEN "\nIngrese la temperatura a las 2:00 PM (grados Celsius): " RESET);
                if(!validar_entrada(&y0)) {
                    printf(RED "\nEntrada inv�lida. Por favor ingrese un numero valido.\n" RESET);
                    sleep(2);
                    break;
                }

                printf(GREEN "Ingrese la temperatura a las 4:00 PM (grados Celsius): " RESET);
                if(!validar_entrada(&y1)) {
                    printf(RED "Entrada inv�lida. Por favor ingrese un n�mero valido.\n" RESET);
                    sleep(2);
                    break;
                }

                imprimir_animacion();
                y = y0 + (y1 - y0) * (3.0 - 2.0) / (4.0 - 2.0);
                printf(BLUE "\nLa temperatura estimada a las 3:00 PM es: %.2f grados Celsius\n" RESET, y);

                printf(GREEN "\n�Desea guardar el resultado? (y/n): " RESET);
                while (getchar() != '\n'); // Limpiar el buffer de entrada
                scanf("%c", &opcion);
                if(opcion == 'y' || opcion == 'Y') {
                    guardar_resultado(y);
                }
                sleep(2);
                break;

            case '2':
                mostrar_ayuda();
                printf("\nPresione cualquier tecla para continuar...");
                while (getchar() != '\n'); // Limpiar el buffer de entrada
                getchar(); // Esperar una tecla
                break;

            case '3':
                continuar = false;
                break;

            default:
                printf(RED "\nOpci�n no v�lida. Por favor seleccione una opci�n valida del menu.\n" RESET);
                sleep(2);
        }
    }

    printf(GREEN "\nGracias por usar el programa de interpolacion. Hasta luego!\n" RESET);
    return 0;
}


