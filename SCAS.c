#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>
#include "queue.h"

enum typeServiceInterval {BY_N_OF_SERVICES, BY_TIME};
typedef enum typeServiceInterval typeSI;

struct ServiceConfiguration
{
    int numCSD; // number of Costumer Service Desks
    int numPriorityCSD; // number of Priority Costumer Service Desks
    typeSI type; //type of attendant interval  
    int periodServiceInterval; // period of attendant interval (time or number of attendances)
    int durationServiceInterval; // duration of attendant interval (time or number of attendances)  
};

typedef struct ServiceConfiguration sConfig;

bool password_check[1000];




bool config_system_interface(sConfig* configuration)
{
    setlocale(LC_ALL, "Portuguese");
    printf("---- SCAS - Sistema de Controle de Atendimento baseado em Senhas ----\n");
    printf("\t\t<< SCAS - Configuração de guichês >>\n");

    // number of Costumer Service Desks
    printf("Insira o número de guichês de atendimento comum (mínimo 1):\n> ");
    scanf("%d", &configuration->numCSD);
    if(configuration->numCSD < 1)
    {
        printf("Número inválido. Número mínimo de guichês definido: 1.\n");
        configuration->numCSD = 1;
    }
    printf("\n");

    // number of Priority Costumer Service Desks
    printf("Insira o número de guichês de atendimento prioritário (mínimo 1):\n> ");
    scanf("%d", &configuration->numPriorityCSD);
    if(configuration->numPriorityCSD < 1)
    {
        printf("Número inválido. Número mínimo de guichês prioritários definido: 1.\n");
        configuration->numPriorityCSD = 1;
    }
    printf("\n");

    // type of attendant interval  
    printf("Defina o critério de parada dos guichês:\n");
    printf("\t (1) Por número de atendimentos (opção padrão)\n");
    printf("\t (2) Por tempo\n> ");
    int choice;
    scanf("%d", &choice);
    configuration->type = choice - 1;
    if(configuration->type != BY_N_OF_SERVICES && configuration->type != BY_TIME)
    {
        printf("Opção inválida. Opção padrão definida: Por número de atendimentos.\n");
        configuration->type = BY_N_OF_SERVICES;
    }
    printf("\n");

    // period of attendant interval (time or number of attendances)
    printf("Defina a periodicidade da parada dos guichês (mínimo 10 (min ou número de atendimentos)):\n> ");
    scanf("%d", &configuration->periodServiceInterval);
    if(configuration->periodServiceInterval < 10)
    {
        printf("Número inválido. Número mínimo de periodicidade definido: 10.\n");
        configuration->periodServiceInterval = 10;
    }
    printf("\n");

    // duration of attendant interval (time or number of attendances)  
    printf("Defina a duração da parada dos guichês (mínimo 5 (min)):\n> ");
    scanf("%d", &configuration->durationServiceInterval);
    if(configuration->durationServiceInterval < 5)
    {
        printf("Número inválido. Número mínimo de duração definido: 5.\n");
        configuration->durationServiceInterval = 5;
    }
    printf("\n\n");
 
    // confirmation
    printf("\t\t*** Confirmação de configuração ***\n");
    printf("Número total de guichês - %d\n", (configuration->numPriorityCSD + configuration->numCSD));
    printf("\tNúmero de guichês comuns - %d\n", configuration->numCSD);
    printf("\tNúmero de guichês prioritários - %d\n", configuration->numPriorityCSD);
    if(configuration->type == BY_N_OF_SERVICES)
    {
        printf("Critério de parada - Por número de atendimentos\n");
        printf("\tPeriodicidade de parada - %d atendimentos\n", configuration->periodServiceInterval);
    }
    else
    {
        printf("Critério de parada - Por tempo\n");
        printf("\tPeriodicidade de parada - %d minutos\n", configuration->periodServiceInterval);
    }
    printf("\tDuração de parada - %d minutos\n\n", configuration->durationServiceInterval);
    
    printf("Confirmar (1)\t Reconfigurar (2)\n");
    int read_command; 

    scanf("%d", &read_command);
    
    if(read_command == 2)
        return false;
    else
        return true;
}

bool insert_costumers(bool* _password_check, queue* _costumers)
{
    printf("\t\t<< SCAS - Cadastro clientes >>\n");
    printf("\t (1) Cadastrar clientes\n");
    printf("\t (2) Carregar último cadastro de clientes\n");
    int read_command; 
    scanf("%d", &read_command);
    if(read_command == 1)
    {
        printf("Inserir dado dos clientes no seguinte formato:\n");
        printf("[TEMPO EM MINUTOS] [COMPLEXIDADE]\n");
        printf("TEMPO EM MINUTOS - Inteiro >= 0.\n");
        printf("COMPLEXIDADE - EXPRESSO = 1 / NORMAL = 2 / COMPLEXO = 3\n");
        bool flag = 0;
        do
        {

        }
        while(!flag)
    }
    else
    {

    }


    for (int i = 0; i < 1000; ++i)
    {
        printf("%d %d\n", _password_check[i], rand() % 1000); 
        _password_check[i] = false;
    }


}

sConfig global_config;

int main()
{   
    memset(password_check, 1, 1000); // Set all values to 1 to indicate all passwords are available
    srand (time(NULL)); // Set a seed for generate random number
    queue costumers;    

    insert_costumers(password_check, &costumers);

    for (int i = 0; i < 1000; ++i)
    {
        printf("%d %d\n", password_check[i], rand() % 1000); 
    }


    bool isConfig = false;
    do
        isConfig = config_system_interface(&global_config);
    while(!isConfig);
    
    



    queue_initialize(&costumers);
    printf("Initial size: %d\n", costumers.size);
    for (int i = 0; i < 1000000; i++)
    {
        queue_add(&costumers, i, i%3);
        printf("Size: %d - %d %d added.\n", costumers.size, i, i%3);
    }

    while (costumers.size != 0)
    {
        int x;
        attComp y; 
        queue_remove(&costumers, &x, &y);
        printf("Size: %d - %d %d removed.\n", costumers.size, x, y);
    }


    





}
