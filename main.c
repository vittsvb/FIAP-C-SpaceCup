#include "pilha_sucesso.h"
#include<string.h>
// NUMERO DE LANÇAMENTO
#define NL 50


void classificacao(lancamento l[], int nGrupos, tipopilha *podio){
	int i;
	int j;
	float menorDistanciaAux = 0;
	int index=0;
	int nTentativaAux = 0;
	float maior=0;
	int maiorT = 0;
	for(i = 0; i < nGrupos; i++){
		if(l[i].distanciaAlvo > maior){
			maior = l[i].distanciaAlvo;
		}
		
		if(l[i].nTentativas > maior){
			maiorT = l[i].nTentativas;
		}
	}
	
	for(j = 0; j < 3; j++){
		menorDistanciaAux = maior+1;
		nTentativaAux = maiorT+1;
		
		for(i = 0; i < nGrupos; i++){
			printf("situacao %d: \n",l[i].situacao);
			if(l[i].situacao == 1){
						
					if(l[i].distanciaAlvo < menorDistanciaAux || i == 0){
						menorDistanciaAux = l[i].distanciaAlvo;
						index = i;
						
					}else
						if(l[i].distanciaAlvo == menorDistanciaAux || i == 0){
							if(l[i].nTentativas < nTentativaAux){
								nTentativaAux = l[i].nTentativas;
								index = i;
							}
						}
			}
		}

		PUSH(podio,l[index]);
		
		l[index].situacao = 0;
		
	}
	
}


void simulacao(int nGrupos, lancamento l[]){
	int i;
	int control;
	for(i = 0; i < nGrupos; i++){
	
		do{
		
			printf("O lancamento do grupo %s foi efetuado?\n1 - Sim\n2 - Nao", l[i].nomeEquipe);
			scanf("%d",&control);
			l[i].nTentativas++;
			
			if(control == 1){
				l[i].situacao = 1;
				printf("Digite a distancia do alvo: ");
				scanf("%d",&l[i].distanciaAlvo);
				
				printf("\n\n*------Lancamento efetuado com sucesso-----*");
				
			}
					
		}while(l[i].situacao != 1 && l[i].nTentativas < 3);
		
		
		if(l[i].nTentativas == 3 && l[i].situacao == 0){
			l[i].situacao = -1;
		}
		
	}

	
}


void inputGrupo(lancamento l[], tipopilha *podio){
	int control = 1;
	int nGrupo=0;
	do{
		printf("Digite o nome da equipe: ");
		fflush(stdin);
		gets(l[nGrupo].nomeEquipe);
		
		l[nGrupo].nTentativas = 0;
		l[nGrupo].situacao = 0;
		
		nGrupo++;
				
		printf("Digite 1 para cadastrar novo grupo\n0 para encerrar cadastro");
		scanf("%d",&control);
				
	}while(control != 0);
	simulacao(nGrupo, l);
	classificacao(l,nGrupo,podio);
	
}


int main(){
	lancamento lanc[NL];
	tipopilha podio;
	lancamento elem;
	//Inicia a pilha
	INIT(&podio);
	inputGrupo(lanc, &podio);
		
	while(!IsEmpty(podio)){
		POP(&podio,&elem);
		printf("%s\n",elem.nomeEquipe);
	}
	
	return 0;	
}
