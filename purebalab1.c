/*
 * @file main.c
 * @brief Main file for the project
 *
 * Este archivo contiene la implementación principal de un programa que gestiona el envío y la recepción de mensajes. 
 * Se define una estructura de mensaje y se proporcionan funciones para enviar y recibir mensajes, con opciones 
 * para especificar y mostrar distintos tipos de mensajes y respuestas.
 */

#include <stdio.h>
#include <string.h>

// Definición de tamaño máximo para el mensaje
#define MAX_MESSAGE_SIZE 256

// Estructura para el mensaje que se enviará
struct Message {
    unsigned int esRespuesta : 1 ; //Guarda un 0 si el mensaje no responde a otro y un 1 si respode a otro
    unsigned int tipo : 1 ; //Guarda un 0 si es un mensaje de solicitud y un  si es un mensaje de aviso
    unsigned int subtipo : 1; //Guarda un 0 o un 1 segun los diferentes subtipos correspondientes al primer tipo
    char message[MAX_MESSAGE_SIZE]; // Buffer para almacenar el mensaje
    char note[MAX_MESSAGE_SIZE]; // Buffer para almacenar una nota ligada al mensaje
};

// Declaración de las funciones para enviar y recibir mensajes
void send(void);
void receive(void);

struct Message msg;   // Variable para almacenar el mensaje

// Función principal del programa
int main() {
    send();   // Llama a la función para enviar un mensaje
    receive(); // Llama a la función para recibir una respuesta
    return 0; // Finaliza la ejecución del programa
}

// Función para enviar un mensaje
void send() {
    int type =0;         

    while (type < 1||type >2) {   
        printf("Ingrese tipo de mensaje que quiere enviar (0 para salir):\n");
        printf("1 --> SOLICITUD\n");
        printf("2 --> AVISO\n");
        printf("3--> ERROR\n"); //Error en la comunicacion
        scanf("%d", &type);
        // Opción de salida del programa
        if (type == 0) return; 
    }

    int S=0;
    // Selección del mensaje basado en la entrada del usuario
    switch (type) {
        case 1:
            msg.tipo=0;
            while (S < 1 || S > 2) {   
            printf("Ingrese una solicitud valida (0 para salir):\n");
            printf("1 --> STATUS\n");
            printf("2 --> CONTROL\n");
            scanf("%d", &S);
            // Opción de salida del programa
            if (S == 0) return; 
            }
            switch (S)
            {
            case 1:   
                msg.subtipo=0;
                strcpy(msg.message, "Enviar STATUS."); // Configura el mensaje para STATUS
                break;
            case 2:  
                msg.subtipo=1; 
                strcpy(msg.message, "Enviar CONTROL."); // Configura el mensaje para CONTROL
            default:
                break;
            }
            break;
        case 2:
            msg.tipo=1;
            while (S < 1 || S > 2) {   
            printf("Ingrese un aviso valido (0 para salir):\n");
            printf("1 --> PELIGRO\n");
            printf("2 --> AYUDA\n");
            scanf("%d", &S);
            // Opción de salida del programa
            if (S == 0) return; 
            }
            switch (S)
            {
            case 1:   
                msg.subtipo=0;
                strcpy(msg.message, "ESTAMOS EN PELIGRO."); // Configura el mensaje para PELIGRO
                break;
            case 2:  
                msg.subtipo=1; 
                strcpy(msg.message, "NECESITAMOS AYUDA."); // Configura el mensaje para AYUDA
            default:
                break;
            }
            break;
        case 3:
            strcpy(msg.message, "Enviar ERROR."); // Configura el mensaje para ERROR
            msg.tipo=2;

            break;
    }

    // Muestra el mensaje que se ha configurado para ser enviado
    printf("%s\n", msg.message); 
}

// Función para recibir y procesar una respuesta
void receive() {
    switch (msg.tipo)
    {
    case 0:
        switch (msg.subtipo)
        {
        case 0:
            int aux;
            printf("Indicar estado en el que se encuentran.\n");
            printf("1-->BIEN\n");
            printf("2-->MAL\n");
            scanf("%d",aux);
            switch (aux)
            {
            case 1:
                strcpy(msg.message, "SIN PROBLEMAS.\n");
                break;
            case 2:
                strcpy(msg.message, "ESTAMOS EN PROBLEMAS.\n");
                break;
            default:
                break;
            }
            break;
        case 1:
            printf("Indicar como se encuentra el control de la zona\n");
            printf("1-->BIEN\n");
            printf("2-->MAL\n");
            scanf("%d",aux);
            switch (aux)
            {
            case 1:
                strcpy(msg.message, "TODO DESPEJADO\n");
                break;
            case 2:
                strcpy(msg.message, "ENEMIGOS AVISTADOS\n");
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }; // Variable para almacenar la respuesta recibida

}






