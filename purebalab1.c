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

// Enumeración para los tipos de mensajes
typedef enum {
    STATUS = 1,  // Mensaje de estado
    CONTROL = 2, // Mensaje de control
    ERROR = 3    // Mensaje de error
} mensaje;

typedef enum {
    AYUDA=1,
    PELIGRO=2
} aviso;

// Enumeración para las respuestas recibidas
typedef enum {
    STATUS_BIEN = 1,   // Estado bueno
    STATUS_MAL = 2,    // Estado malo
    CONTROL_BIEN = 3,  // Control bueno
    CONTROL_MAL = 4,   // Control malo
    ERROR_R = 5        // Error en la comunicación
} respuesta;

typedef enum {
    AYUDA_EN_CAMINO = 1,
    IMPOSIBLE_AYUDAR = 2
} respuesta_aviso;

// Estructura para el mensaje que se enviará
struct Message {
    int type; // Almacena si se trata de un mensaje o una respuesta
    int subtype; // Almacena un subtipo que varia segun el tipo
    char message[MAX_MESSAGE_SIZE]; // Buffer para almacenar el mensaje

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
    mensaje M = 0;        // Variable para almacenar el tipo de mensaje
    int type = 0;

    while (type!= 1,2,3) {   
        printf("Ingrese tipo de mensaje que quiere enviar (0 para salir):\n");
        printf("1 --> SOLICITUD\n");
        printf("2 --> AVISO\n");
        printf("3--> ERROR\n"); //Error en la comunicacion
        scanf("%d", &type);
        // Opción de salida del programa
        if (type == 0) return; 
    }

    // Selección del mensaje basado en la entrada del usuario
    switch (type) {
        case 1:
            msg.type=1;
            while (M < 1 || M > 2) {   
            printf("Ingrese una solicitud valida (0 para salir):\n");
            printf("1 --> STATUS\n");
            printf("2 --> CONTROL\n");
            scanf("%d", &M);
            // Opción de salida del programa
            if (M == 0) return; 
            }
            switch (M)
            {
            case 1:   
                msg.subtype=1;
                strcpy(msg.message, "Enviar STATUS."); // Configura el mensaje para STATUS
                break;
            case 2:  
                msg.subtype=2; 
                strcpy(msg.message, "Enviar CONTROL."); // Configura el mensaje para STATUS
            default:
                break;
            }
            break;
        case 2:
            msg.type=2;
            while (M < 1 || M > 2) {   
            printf("Ingrese un aviso valido (0 para salir):\n");
            printf("1 --> PELIGRO\n");
            printf("2 --> AYUDA\n");
            scanf("%d", &M);
            // Opción de salida del programa
            if (M == 0) return; 
            }
            switch (M)
            {
            case 1:   
                msg.subtype=1;
                strcpy(msg.message, "ESTAMOS EN PELIGRO."); // Configura el mensaje para PELIGRO
                break;
            case 2:  
                msg.subtype=2; 
                strcpy(msg.message, "NECESITAMOS AYUDA."); // Configura el mensaje para AYUDA
            default:
                break;
            }
            break;
        case 3:
            strcpy(msg.message, "Enviar ERROR."); // Configura el mensaje para ERROR
            msg.type=3;

            break;
    }

    // Muestra el mensaje que se ha configurado para ser enviado
    printf("%s\n", msg.message); 
}

// Función para recibir y procesar una respuesta
void receive() {
    respuesta R = 0; // Variable para almacenar la respuesta recibida

    // Bucle para solicitar y validar la entrada del usuario
    while (!(R > 0 && R < 6)) {   
        printf("Esperando respuesta.\n");
        scanf("%d", &R);
    }

    // Selección del mensaje de respuesta basado en la entrada del usuario
    switch (R) {
        case 1:
            printf("SIN PROBLEMAS.\n"); // Mensaje para respuesta STATUS_BIEN
            break;
        case 2:
            printf("PELIGRO.\n"); // Mensaje para respuesta STATUS_MAL
            break;
        case 3:
            printf("TODO DESPEJADO.\n"); // Mensaje para respuesta CONTROL_BIEN
            break;
        case 4:
            printf("ENEMIGOS AVISTADOS.\n"); // Mensaje para respuesta CONTROL_MAL
            break;
        case 5:
            printf("FALLO LA COMUNICACION.\n"); // Mensaje para respuesta ERROR_R
            break;
        default:
            printf("FIN DEL MENSAJE.\n"); // Mensaje por defecto para casos inesperados
            break;
    }
}






