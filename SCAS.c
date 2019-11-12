#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>
#include "queue.h"

#define PROB_PRIORITY 20
#define PROB_STOP 3 

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
    printf("\t (1) Cadastrar clientes automaticamente\n");
    printf("\t (2) Carregar último cadastro de clientes\n");
    int read_command; 
    scanf("%d", &read_command);
    if(read_command == 1)
    {
        printf("Inserir quantidade de clientes (máx: 1000):\n");
        int num_clientes;
        scanf("%d", & num_clientes);
        if (num_clientes > 1000) num_clientes = 1000;
        int initial_time = 0;
        FILE * StoreData;
        StoreData = fopen("last_work", "w");
        for (int i = 0; i < num_clientes; i++)
        {
            bool priority; // 0 - 1 (NO_PRIORITY, PRIORITY)
            if((rand() % 1000) < (PROB_PRIORITY * 10))
                priority = 1;
            else
                priority = 0;

            int complexity; // 1 - 3 (EXPRESS, NORMAL, COMPLEX) 
            complexity = (rand() % 3) + 1;

            int time_increment; // 0 - 3 (TIMESTAMP INCREMENT)
            time_increment = rand() % 4;

            initial_time += time_increment; 

            queue_add(&(*_costumers), priority, initial_time, i, NULL, complexity);
            
            fprintf(StoreData, "%d %d %d %d\n", priority, initial_time, i, complexity);
        }   
        fclose(StoreData);    
    }
    else
    {
        FILE * StoredData;
        StoredData = fopen("last_work", "r");
        char* line = NULL;
        int len = 0;
        while (getline(&line, &len, StoredData) != -1)
        {
            bool priority;
            int initial_time, i, complexity;
            //printf("%s", line);
            char* split = strtok(line," \n");
            sscanf(split, "%d", &priority);
            split = strtok (NULL, " \n");
            sscanf(split, "%d", &initial_time);
            split = strtok (NULL, " \n");
            sscanf(split, "%d", &i);
            split = strtok (NULL, " \n");
            sscanf(split, "%d", &complexity);
            split = strtok (NULL, " \n");
            queue_add(&(*_costumers), priority, initial_time, i, NULL, complexity);
        }
        if(line) free(line);
        fclose(StoredData);  
    }

}

sConfig global_config;

int main()
{  
    /* 
    bool isConfig = false;
    do
        isConfig = config_system_interface(&global_config);
    while(!isConfig);
    */
    memset(password_check, 1, 1000); // Set all values to 1 to indicate all passwords are available
    srand (time(NULL)); // Set a seed for generate random number
    
    queue costumers;
    queue_initialize(&costumers);    
    insert_costumers(password_check, &costumers);
    queue_print(&costumers);
}
