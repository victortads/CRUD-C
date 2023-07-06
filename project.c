#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_DADOS 1000

typedef enum{
	TELA_SAIR = -1,
	TELA_PRINCIPAL,
	TELA_CADASTRAR,
	TELA_DESCADASTRAR,
	TELA_LISTAR_TODOS,
	TELA_ATUALIZAR,
} Telas;

typedef struct{
	char nome[128];
	char salario[64];
	char codigoIdentificacao[32];
} Identificacao;

typedef struct{
	Telas menu;
	int totalSalario;
	Identificacao salario[MAX_DADOS];
} NumeroIdentificacao;

int main (){
	
	setlocale(LC_ALL, "Portuguese");
	
	NumeroIdentificacao numero;

	memset(&numero, 0x0, sizeof(numero));
	
	numero.menu = TELA_PRINCIPAL;
	
	FILE * memoria = fopen("cadastro.bin", "rb+wb");
	if(memoria == NULL){
		printf("Erro ao abrir o cadastro.\n");
		printf("Deve criar o aquivo antes de abrir.\n");
		return 1;
	}
	
	size_t lidos = fread(numero.salario, sizeof(Identificacao), 
						MAX_DADOS, memoria);
	printf("%zd dados foram lidos\n", lidos);
	numero.totalSalario = (int) lidos;
	fclose(memoria);
	
	while (numero.menu != TELA_SAIR){
		
		switch (numero.menu){
			case TELA_PRINCIPAL:
				{
				  printf("\t ----------Central de Identificação de funcionários----------\n");
				  int opcao = -1;
				  do{
				  	printf("\nEscolha uma opção:\n");
				  	printf("\tDigite 1 para cadastrar funcionário\n");
				  	printf("\tDigite 2 para remover funcionário\n");
				  	printf("\tDigite 3 para listar todos os funcionários\n");
				  	printf("\tDigite 4 para atualizar os funcionários\n");
				  	printf("\tDigite 0 para sair do programa\n");
				  	scanf("%d", &opcao);
				  	system("cls");
				  }	while (opcao < 0 || opcao > 4);
				if (opcao == 0){
					numero.menu = TELA_SAIR;
				}
						
				if (opcao == 1)
				{
					numero.menu = TELA_CADASTRAR;
					if (numero.totalSalario >= MAX_DADOS){
						printf("\tO programa está lotado, não pode adicionar mais funcionários\n");
						numero.menu = TELA_PRINCIPAL;
					}
				}
				
				if (opcao == 2)
				{
				  	numero.menu = TELA_DESCADASTRAR;
					  if (numero.totalSalario == 0)
					  {
					  	printf("\t Não tem nenhum funcionário cadastrado para remover\n");
					  	numero.menu = TELA_PRINCIPAL;
					  }	
				}
				
				if (opcao == 3)
				{
					numero.menu = TELA_LISTAR_TODOS;
					if (numero.totalSalario == 0){
						printf("\tA programa não tem nada para listar\n");
						numero.menu = TELA_PRINCIPAL;
					}
				}
				
				if (opcao == 4)
				{
					numero.menu = TELA_ATUALIZAR;
					if (numero.totalSalario == 0){
						printf("\tO programa não tem nada para listar\n");
						numero.menu = TELA_PRINCIPAL;
					}
				}
			}
			break;
			case TELA_CADASTRAR:
				{
				printf("-----Cadastro de funcionários-----");
				Identificacao novo;
				char opcao = 's';
				int c = 0;
				while((c = getchar()) != '\n' && c != EOF) { }
					do
					{
						memset(&novo, 0x0, sizeof(novo));
						printf("\nDigite um novo nome para o Funcionário: \n");
						fgets(novo.nome, 128, stdin);
						int id = 0;
						while (novo.nome[id] != '\0' &&novo.nome[id] != '\n')
							id++;
						novo.nome[id] = '\0';
					
						
						printf("Digite o código desse funcionário: \n");
						fgets(novo.codigoIdentificacao, 32, stdin);
						id = 0;
						while (novo.codigoIdentificacao[id] != '\0' &&novo.codigoIdentificacao[id] != '\n')
							id++;					
							novo.codigoIdentificacao[id] = '\0';
					
						
						printf("Digite o salário desse funcionário: \n");
						fgets(novo.salario, 64, stdin);
                        id = 0;
						while (novo.salario[id] != '\0' &&novo.salario[id] != '\n')
							id++;
						novo.salario[id] = '\0';
					
						
						
						printf("Quer adicionar mesmo esse funcionário?(T_T) [s/n]\n");
						opcao = getchar();
						
						int c = 0;
						while ((c = getchar()) != '\n' && c != EOF) { }
					} while (opcao == 'n' || opcao == 'N');
					
					numero.salario[numero.totalSalario] = novo;
					numero.totalSalario++;
					memoria = fopen("cadastro.bin", "w+b");
					if( memoria == NULL)
					{
						printf("erro ao abrir cadastro.bin\n");
						return 0;
					}
					
					size_t salvos = fwrite(numero.salario, sizeof(Identificacao), 
						numero.totalSalario, memoria);
					if (salvos != (size_t)numero.totalSalario)
					{
						printf("Erro ao salvar funcionários na memoria cadastro.bin\n");
						return 1;
					}
					fclose(memoria);
					
					numero.menu = TELA_PRINCIPAL;
				}
				break;
			case TELA_DESCADASTRAR:
	          	{				  
					char opcao = 'n';
					printf("\t----------Tela para descadastrar----------\n");
					int i;
					
					for (i = 0; i<numero.totalSalario; i++)
					{
						printf("Funcionário Nº %d\n", i);
						printf("Nome: %s\n", numero.salario[i].nome);
						printf("Código de identificação: %s\n", numero.salario[i].codigoIdentificacao);
						printf("Salário: %s\n", numero.salario[i].salario);
						printf("--------------------\n");
					}
					
					printf("Deseja remover mais um funcionário?[s/n]");
					opcao = getchar();
				
					if(getchar() == 's' || getchar() == 'S'){
					
					int indice = -1;
					do
					{
						printf("Digite um indice(de 0 até %d) de contato para descadastrar", i-1);
						scanf("%d", &indice);
						
						int c = 0;
						while ((c = getchar()) != '\n' && c != EOF) { }
					} while (indice < 0 || indice >= numero.totalSalario);
					
					for (i = indice; i < numero.totalSalario - 1; i++)
						numero.salario[i] = numero.salario[i + 1];
						
					numero.totalSalario--;}
					
				
					memoria = fopen("cadastro.bin", "w+b");
					if(memoria == NULL)
					{
						printf("erro ao abrir cadastro.bin");
						return 0;
					}
					size_t salvos = fwrite(numero.salario, sizeof(Identificacao), 
						numero.totalSalario, memoria);
					
					if (salvos != (size_t)numero.totalSalario)
					{
						printf("Erro ao salvar funcionários na memoria cadastro.bin\n");
						return 1;
					}
					fclose(memoria);
					
					
					numero.menu = TELA_PRINCIPAL;
				}
				break;
			case TELA_LISTAR_TODOS:
				{
					printf("\t----------Listando funcionários----------");
					int i;
					for(i = 0; i < numero.totalSalario; i++)
					{
						printf("\n\tFuncionário %s\n", numero.salario[i].codigoIdentificacao);
						printf("\tNome: %s\n", numero.salario[i].nome);
						printf("\tSalário: R$%s\n", numero.salario[i].salario);
						}	
					
					numero.menu = TELA_PRINCIPAL;
				}
				break;
			case TELA_ATUALIZAR:
				{
					system("cls");
					printf("\t----------Tela para atualizar----------\n");
					int i;
					
					for (i = 0; i<numero.totalSalario; i++)
					{
						printf("Funcionário Nº %d\n", i);
						printf("Nome: %s\n", numero.salario[i].nome);
						printf("Código de identificação: %s\n", numero.salario[i].codigoIdentificacao);
						printf("Salário: %s\n", numero.salario[i].salario);
						printf("--------------------\n");
					}
					
					
					int indice = -1;
					do
					{
						printf("Digite um indice(de 0 até %d) de contato para atualizar ", i-1);
						scanf("%d", &indice);
						
						int c = 0;
						while ((c = getchar()) != '\n' && c != EOF) { }
					} while (indice < 0 || indice >= numero.totalSalario);
					
					printf("Nome: \n");
   					scanf("%s", numero.salario[indice].nome);
					   
					printf("Funcionário:\n");
   					scanf("%s", numero.salario[indice].codigoIdentificacao);
    				
					printf("salario: \n");
    				scanf("%s", numero.salario[indice].salario);
					printf("\n");	
					
					memoria = fopen("cadastro.bin", "w+b");
					if(memoria == NULL)
					{
						printf("erro ao abrir cadastro.bin");
						return 0;
					}
					size_t salvos = fwrite(numero.salario, sizeof(Identificacao), 
						numero.totalSalario, memoria);
					
					if (salvos != (size_t)numero.totalSalario)
					{
						printf("Erro ao salvar funcionários na memoria cadastro.bin\n");
						return 1;
					}
					fclose(memoria);
					
					
					numero.menu = TELA_PRINCIPAL;	
				}
				break;
			default:
				numero.menu = TELA_PRINCIPAL;
				break;
		}
		
	}
	return 0;
	
}



