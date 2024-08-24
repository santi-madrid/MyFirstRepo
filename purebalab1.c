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
typedef struct{
    unsigned int error : 1 ; //Indica si hubo un error en la comunicacion con un 1
    unsigned int tipo : 2 ; //Guarda un 0 si es un mensaje de solicitud y un  si es un mensaje de aviso
    unsigned int subtipo : 1; //Guarda un 0 o un 1 segun los diferentes subtipos correspondientes al primer tipo
    char message[MAX_MESSAGE_SIZE]; // Buffer para almacenar el mensaje
} Mensaje;

// Declaración de las funciones para enviar y recibir mensajes
void send(void);
void receive(void);
void log(Mensaje *msg);

static unsigned int mode;
Mensaje msg = {0,0,0,""};

// Función principal del programa
int main() {
    send();   // Llama a la función para enviar un mensaje
    receive(); // Llama a la función para recibir una respuesta
    return 0; // Finaliza la ejecución del programa
}

// Función para enviar un mensaje
void send() {
    mode = 0;
printf("COMIENZA FUNCION ENVIAR -------------\n");
    int type =0;
    while (type < 1||type >4) {   
        printf("Ingrese tipo de mensaje que quiere enviar (0 para salir):\n");
        printf("1 --> SOLICITUD\n");
        printf("2 --> INFORMACION\n");
        printf("3 --> AVISO\n");
        printf("4--> ERROR\n"); //Error en la comunicacion
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
            int aux =0;
            S=0;
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
                while(aux<1||aux>2){
                printf("Indicar estado en el que se encuentran.\n");
                printf("1-->BIEN\n");
                printf("2-->MAL\n");
                scanf("%d",&aux);
                }
                switch (aux)
                {
                case 1:
                strcpy(msg.message, "INFORMACION DE STATUS: SIN PROBLEMAS.\n");
                break;
                case 2:
                strcpy(msg.message, "INFORMACION DE STATUS: ESTAMOS EN PROBLEMAS.\n");
                break;
                default:
                break;
                }
                break;
            case 2:
                printf("Indicar como se encuentra el control de la zona\n");
                printf("1-->BIEN\n");
                printf("2-->MAL\n");
                scanf("%d",&aux);
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
                    break;
                default:
                    break;
                }
            break;
            break;
        case 3:
            msg.tipo=2;
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
        case 4:
            strcpy(msg.message, "Enviar ERROR."); // Configura el mensaje para ERROR
            msg.error=1;
            break;
    }

    log(&msg);
    // Muestra el mensaje que se ha configurado para ser enviado
    printf("ENVIANDO MENSAJE : "); 
    printf("%s\n", msg.message); 

}

// Función para recibir y procesar una respuesta
void receive() {
    mode = 1;
printf("\nCOMIENZA FUNCION RECIBIR---------------\n\n");
    int aux=0;
    if(msg.error==1){
        printf("ERROR EN LA COMUNICACION.\n");
        log(&msg);
    }else{
        printf("RECIBIMOS UN MENSAJE DE NUESTROS ALIADOS: \n");
        printf("%s\n", msg.message);
        log(&msg);
    }
}

void log(Mensaje *msg){
    FILE *f = fopen("log.txt","a+");
    if (f == NULL) {
        perror("No se pudo abrir el archivo de log");
        return;
    }
    switch (mode)
    {
    case 0:
        fprintf(f,"---------------------------------------------------\n\n");
        fprintf(f,"[Mensaje enviado]: %s\n\n",msg->message);
        fprintf(f,"---------------------------------------------------\n\n");
        break;
    case 1:
        fprintf(f,"---------------------------------------------------\n\n");
        fprintf(f,"[Mensaje recibido]: %s\n\n",msg->message);
        fprintf(f,"---------------------------------------------------\n\n");
        break;
    default:
        break;
    }
    fclose(f);
}

void resetMsg(Mensaje *msg){
    
}