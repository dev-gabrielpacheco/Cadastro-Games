#include <iostream>
#include <string.h>
#include <Windows.h>
#include <locale>

struct reg
{
	char game[40];
	char media[20];
	char peso[20];
	char val[20];
	char sit;
};

int tamanho(FILE *);
void cadastrar(FILE *);
void consultar(FILE *);
void geraarqtxt(FILE *);
void excluir(FILE *);

int main()
{
	int op;
	FILE *arq;

	if ((arq = fopen("lista de jogos.dat", "rb+")) == NULL)
	{
		if ((arq = fopen("lista de jogos.dat", "wb+")) == NULL)
		{
			printf("Falha ao executar arquivo!\n");
			system("pause");
		}
	}
	do
	{
		system("CLS");
		printf("\n같같캪ISTA DE JOGOS같같�\n");
		printf("1 - Cadastrar jogo\n");
		printf("2 - Consultar jogo por codigo cadastrado\n");
		printf("3 - Gerar arquivo de texto\n");
		printf("4 - Excluir jogo\n");
		printf("5 - Encerrar programa\n");
		printf("같캨ogos cadastrados:%d\n", tamanho(arq));
		printf("\n Selecione uma das opcoes acima:");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			cadastrar(arq);
			break;
		case 2:
			consultar(arq);
			break;
		case 3:
		     geraarqtxt(arq);
			break;
		case 4: 
			excluir(arq); 
			break;
		case 5: fclose(arq);
		printf("\nEncerrando programa...");
		}
	} while (op != 5);
}

void cadastrar(FILE *arq)
{
	reg jogo;
	char confirmar[4];
	jogo.sit = ' ';
	fflush(stdin);

	printf("\nJogo a cadastrar:\n");
	printf("\nJogo com registro de numero:%d\n", tamanho(arq) + 1);
	printf("\nNome do jogo: ");
	gets(jogo.game);
	printf("Media nas reviews: ");
	gets(jogo.media);
	printf("Armazenamento necessario: ");
	gets(jogo.peso);
	printf("Valor do jogo: ");
	gets(jogo.val);
	printf("\nConfirma cadastro? <sim/nao>:");
	fflush(stdin);
	gets(confirmar);

	if (strcmp(confirmar,"sim") == 0)
	{
		printf("\nsalvando...\n\n");
		fseek(arq, 0, SEEK_END);
		fwrite(&jogo, sizeof(reg), 1, arq);

	}
	system("pause");
}

void consultar(FILE *arq)
{
	reg jogo;
	int nmr;
	printf("\nConsultar pelo codigo de cadastro\n");
	printf("\nInforme o codigo que deseja consultar:");
	scanf("%d", &nmr);
	if ((nmr <= tamanho(arq)) && (nmr>0))
	{
		fseek(arq, (nmr - 1) * sizeof(reg), SEEK_SET);
		fread(&jogo, sizeof(reg), 1, arq);
		if (jogo.sit == ' ')
		{
			printf("\nNome do jogo: %s", jogo.game);
			printf("\nMedia nas reviwes: %s", jogo.media);
			printf("\nArmazenamento necessario: %s", jogo.peso);
			printf("\nValor do jogo: %s\n",jogo.val);
		}

		else
			printf("\nO jogo com este codigo foi excluido :( \n");

	}
	else
	{
		printf("\nNao ha nenhum jogo com esse codigo de cadastro\n");
	}
	system("pause");
}

void geraarqtxt(FILE *arq)
{
	char nom[20];
	printf("\nNome do arquivo que deseja criar: ");
	scanf("%s", nom);
	strcat(nom, ".txt");
	FILE *arqtxt = fopen(nom, "w");
	if (!arqtxt)
	{
	printf("Nao foi possivel criar o arquivo %s!");
	}
	else
	{
	printf("\nArquivo %s criado com sucesso!\n",nom);
	system("pause");
	}
	
	fprintf(arqtxt, "Nome do jogo             | Media nas reviews | Armazenamento que ocupa | valor |\n");
	fprintf(arqtxt, "--------------------------------------------------------------------------------\n");
	int numr;
	reg jogos;
	for (numr = 0; numr<tamanho(arq); numr++)
	{
		fseek(arq, numr * sizeof(reg), SEEK_SET);
		fread(&jogos, sizeof(reg), 1, arq);
		fprintf(arqtxt, "%-25s %-19s %-25s %s\n", jogos.game, jogos.media, jogos.peso, jogos.val);
	}
	fprintf(arqtxt, "********************************************************************************\n");
	fclose(arqtxt);
}

void excluir(FILE *arq)
{
	reg games;
	char conf[4];
	int ty;

	printf("\nInforme o codigo do jogo que deseja deletar: ");
	scanf("%d", &ty);
	if ((ty <= tamanho(arq)) && (ty>0))
	{
		fseek(arq, (ty - 1) * sizeof(reg), SEEK_SET);
		fread(&games, sizeof(reg), 1, arq);
		if (games.sit == ' ')
		{
			printf("\nNome do jogo: %s", games.game);
			printf("\nMedia nas reviews: %s", games.media);
			printf("\nArmazenamento necessario: %s", games.peso);
			printf("\nValor do jogo: %s",games.val);
			printf("\nConfirma a exclusao: <sim/nao>\n");
			getchar();
			scanf("%3s",conf);

		if (strcmp(conf,"sim") == 0)
			{
				printf("\nDeletando...\n\n");
				fseek(arq, (ty - 1) * sizeof(reg), SEEK_SET);
				games.sit = '*';
				fwrite(&games, sizeof(reg), 1, arq);
			}
		}
	else
		printf("Jogo com este registro nao encontrado! \n");
	}
	else
	{
		printf("\nJogo com este numero de registro invalido!\n");
	}
	system("pause");
}

int tamanho(FILE *arq)
{
	fseek(arq, 0, SEEK_END);
	return ftell(arq) / sizeof(reg);
}
