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
    unsigned int tipo : 2 ; //Guarda 2 bits que indican de que tipode mensaje se trata
    char mensaje[MAX_MESSAGE_SIZE]; // Buffer para almacenar el mensaje
} Mensaje;

// Declaración de las funciones para enviar y recibir mensajes
void enviar(void);
void recibir(void);
// Declaracion de la funcion log
void log(Mensaje *msg);

static unsigned int modo; //Indica en que estado se encuentra actualmente el programa(0->enviar,1->recibir)
Mensaje msg = {0,0,""};

// Función principal del programa
int main() {
    enviar();   // Llama a la función para enviar un mensaje
    recibir(); // Llama a la función para recibir una respuesta
    return 0; // Finaliza la ejecución del programa
}

// Función para enviar un mensaje
void enviar() {
    modo = 0;
printf("COMIENZA FUNCION ENVIAR -------------\n");
    int type=0;
    while (type < 1||type >4) {   
        printf("Ingrese tipo de mensaje que quiere enviar (0 para salir):\n");
        printf("1 --> SOLICITUD\n");
        printf("2 --> INFORMACION\n");
        printf("3 --> AVISO\n");    
        printf("4 --> ERROR\n"); //Error en la comunicacion
        scanf("%d", &type);
        if(type==0){
            msg.tipo=3;
        }
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
            printf("1 --> ESTADO\n");
            printf("2 --> CONTROL\n");
            scanf("%d", &S);
            if(S==0){
            msg.tipo=3;
            }
            // Opción de salida del programa
            if (S == 0) return; 
            }
            switch (S)
            {
            case 1:   
                strcpy(msg.mensaje, "SE SOLICITA ENVIAR ESTADO."); // Configura el mensaje para STATUS
                break;
            case 2:  
                strcpy(msg.mensaje, "SE SOLICITA ENVIAR CONTROL."); // Configura el mensaje para CONTROL
            default:
                break;
            }
            break;
        case 2:
            msg.tipo=1;
            int aux =0;
            S=0;
            while (S < 1 || S > 2) {   
            printf("Ingrese un tipo de informacion valida (0 para salir):\n");
            printf("1 --> ESTADO\n");
            printf("2 --> CONTROL\n");
            scanf("%d", &S);
            if(S==0){   //Se mara el tipo 3 para que la funcion recibir detecte que es un mensaje en falso
            msg.tipo=3;
            }
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
                strcpy(msg.mensaje, "INFORMACION DE STATUS: SIN PROBLEMAS.\n");
                break;
                case 2:
                strcpy(msg.mensaje, "INFORMACION DE STATUS: ESTAMOS EN PROBLEMAS.\n");
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
                    strcpy(msg.mensaje, "INFORMACION DE CONTROL: TODO DESPEJADO\n");
                    break;
                case 2:
                    strcpy(msg.mensaje, "INFORMACION DE CONTROL: ENEMIGOS AVISTADOS\n");
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
            if(S==0){
            msg.tipo=3;
            }
            // Opción de salida del programa
            if (S == 0) return; 
            }
            switch (S)
            {
            case 1:
                strcpy(msg.mensaje, "URGENTE. ESTAMOS EN PELIGRO."); // Configura el mensaje para PELIGRO
                break;
            case 2:
                strcpy(msg.mensaje, "NECESITAMOS AYUDA."); // Configura el mensaje para AYUDA
            default:
                break;
            }
            break;
        case 4:
            strcpy(msg.mensaje, "Enviar ERROR."); // Configura el mensaje para ERROR
            msg.error=1;
            break;
    }

    log(&msg);
    // Muestra el mensaje que se ha configurado para ser enviado
    printf("ENVIANDO MENSAJE : "); 
    printf("%s\n", msg.mensaje); 

}

// Función para recibir y procesar una respuesta
void recibir() {
    modo = 1;
    if(msg.tipo==3) return;
    printf("\nCOMIENZA FUNCION RECIBIR---------------\n\n");
    int aux=0;
    if(msg.error==1){
        printf("ERROR EN LA COMUNICACION.\n");
        log(&msg);
    }else{
        printf("RECIBIMOS UN MENSAJE DE NUESTROS ALIADOS: \n");
        printf("%s\n", msg.mensaje);
        log(&msg);
    }
}

void log(Mensaje *msg){
    FILE *f = fopen("log.txt","a+");
    if (f == NULL) {
        perror("No se pudo abrir el archivo de log");
        return;
    }
    switch (modo)
    {
    case 0:
        fprintf(f,"---------------------------------------------------\n\n");
        fprintf(f,"[Mensaje enviado]: %s\n\n",msg->mensaje);
        fprintf(f,"---------------------------------------------------\n\n");
        break;
    case 1:
        fprintf(f,"---------------------------------------------------\n\n");
        fprintf(f,"[Mensaje recibido]: %s\n\n",msg->mensaje);
        fprintf(f,"---------------------------------------------------\n\n");
        break;
    default:
        break;
    }
    fclose(f);
}

void resetMsg(Mensaje *msg){
    
}