#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>

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

bool config_system_interface(sConfig* configuration)
{
    setlocale(LC_ALL, "Portuguese");
    printf("---- SCAS - Sistema de Controle de Atendimento baseado em Senhas ----\n");
    printf("\t\t<< SCAS - Configuração de guichês >>\n");

    // Inserir número de guichês comuns.
    printf("Insira o número de guichês de atendimento comum (mínimo 1):\n> ");
    scanf("%d", &configuration->numCSD);
    if(configuration->numCSD < 1)
    {
        printf("Número inválido. Número mínimo de guichês definido: 1.\n");
        configuration->numCSD = 1;
    }
    printf("\n");

    // Inserir número de guichês prioritários
    printf("Insira o número de guichês de atendimento prioritário (mínimo 1):\n> ");
    scanf("%d", &configuration->numPriorityCSD);
    if(configuration->numPriorityCSD < 1)
    {
        printf("Número inválido. Número mínimo de guichês prioritários definido: 1.\n");
        configuration->numPriorityCSD = 1;
    }
    printf("\n");

    // Inserir critério de parada dos guichês
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

    // Inserir periodicidade da parada
    printf("Defina a periodicidade da parada dos guichês (mínimo 10 (min ou número de atendimentos)):\n> ");
    scanf("%d", &configuration->periodServiceInterval);
    if(configuration->periodServiceInterval < 10)
    {
        printf("Número inválido. Número mínimo de periodicidade definido: 10.\n");
        configuration->periodServiceInterval = 10;
    }
    printf("\n");

    // Inserir duração da parada
    printf("Defina a duração da parada dos guichês (mínimo 5 (min)):\n> ");
    scanf("%d", &configuration->durationServiceInterval);
    if(configuration->durationServiceInterval < 5)
    {
        printf("Número inválido. Número mínimo de duração definido: 5.\n");
        configuration->durationServiceInterval = 5;
    }
    printf("\n\n");
 
    // Confirmação1
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

sConfig global_config;

int main()
{   
    bool isConfig = false;
    do
        isConfig = config_system_interface(&global_config);
    while(!isConfig);

}
