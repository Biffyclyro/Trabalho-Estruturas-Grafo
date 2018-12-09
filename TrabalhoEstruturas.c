#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct cidade{
    char nome[30];
    struct cidade *prox;
    struct adjacente *rotas;
        
};

struct adjacente{
    int peso;
    struct cidade *city;
    struct adjacente *prox;
};

typedef struct cidade Cidade;
typedef struct adjacente Adj;


void addRotas(char n1[], char n2[], int peso, Cidade *lista);
Cidade *addCidade(Cidade *c, char n[]);
Cidade *addTodas();

void exlcuiRota(Cidade *c){
    char nome[30], nome2[30];
    Cidade *p;
    Adj  *ant, *k;
    printf("Entre com a rota:\n");
    printf("De\n");
    gets(nome);
    printf("Ate:\n");
    gets(nome2);
    for(p=c; p->prox!=NULL && strcmp(p->nome, nome)!=0; p=p->prox);
    if(strcmp(p->nome, nome)!=0){
        printf("Nome da cidade de partida errada, tente novamente!\n");
        return;
    }
    for(k=p->rotas; k->prox!=NULL && strcmp(k->city->nome, nome2)!=0;){
        ant=k;
        k=k->prox;
    }
    if(strcmp(k->city->nome, nome2)!=0){
        printf("Cidade destino errada, tente novamente!\n");
        return;
    }
    if(p->rotas==k){
        p->rotas=NULL;
        free(k);
    }

    if(k->prox!=NULL){
        ant->prox=k->prox;
        free(k);
    }else{
        ant->prox=NULL;
        free(k);
    }
}

Cidade *excluiCidade(Cidade *c){
    Cidade *p, *ant=NULL;
    Adj *k;
    char nome[30];
    printf("Entre com o nome da cidade:\n");
    gets(nome);
    for(p=c; c->prox!=NULL && strcmp(p->nome, nome)!=0;){
        ant=p;
        p=p->prox;
    }
    if(strcmp(p->nome, nome)!=0){
        printf("Cidade nao encontrada!\n");
        return c;
    }

    if(p==c){
        if(p->prox==NULL){
            for(k=p->rotas; k->prox!=NULL; k=k->prox)free(k);
            free(p);
            return NULL;
        }else{
            for(k=p->rotas; k->prox!=NULL; k=k->prox)free(k);
            ant=p->prox;
            free(p);
            return ant;
        }
        
    }
    if(p->prox==NULL){
        ant->prox=NULL;
        for(k=p->rotas; k->prox!=NULL; k=k->prox)free(k);
        free(p);
        return c;

    }else{
        for(k=p->rotas; k->prox!=NULL; k=k->prox)free(k);
        ant->prox=p->prox;
        free(p);
        return c;
    }

}

void editarCidade(Cidade *c){
    Cidade *p;
    Adj *k;
    char nome[30];
    int x, resp=0, y;

    printf("Entre com o nome da cidade:\n");
    gets(nome);
    for(p=c; p->prox!=NULL && strcmp(p->nome, nome) != 0; p=p->prox);
    if(strcmp(p->nome, nome) != 0){
        printf("Cidade nao encontrada!\n");
        return;
    }

    while(resp==0){
        printf("Entre com a opcao que quer alterar:\n");
        printf("1.Nome da cidade.\n");
        printf("2.Distancia entre cidades.\n");
        printf("3.Retornar menu principal.\n");
        scanf("%d", &x);

        switch (x)
        {
            case 1:{
                printf("Entre com o novo nome:\n");
                gets(nome);
                strcpy(p->nome, nome);
                break;
            }
            case 2:{
                printf("Entre com a cidade destino e a nova distancia:\n");
                gets(nome);
                scanf("%d", &y);
                for(k=p->rotas; k->prox!=NULL && strcmp(k->city->nome, nome)!=0; k=k->prox);
                if(strcmp(k->city->nome, nome)!=0){
                    printf("Cidade destino nao encontrada!\n");
                    return;
                }
                k->peso=y;
                break;
            }

            case 3:{
                printf("Voltado...\n");
                resp++;
                break;
            }

            default:{
                printf("Opcao invalida!\n");
                break;
            }
        
        }
    }


}

void exibirCidade(Cidade *c){
    Cidade *p;
    Adj *k;
    char nome[30];
    printf("Entre com o nome da cidade:\n");
    
    //fflush(stdin);
    gets(nome);
    for(p=c; p->prox!=NULL && strcmp(p->nome, nome)!=0; p=p->prox);
    if(strcmp(p->nome, nome)!=0){
        printf("Cidade nao encontrada!\n");
        return;
    }
    //puts(p->nome);
    for(k=p->rotas; k->prox!=NULL; k=k->prox){
        puts(p->nome);
        puts(k->city->nome);
        printf("Distancia %dKm\n",k->peso);
        printf("\n");
    }
}

Cidade *varreGrafo(Cidade *o, Cidade *d){
    Adj *k;
    Cidade *p;
    if(o->rotas ==NULL){
        printf("rotas vazias\n");
        return;
    }
    for(k=o->rotas; k->prox!=NULL && k->city != d; k=k->prox);
    puts(k->city->nome);
    if(k->city != d){
        p=varreGrafo(k->city, d);
        puts(p->nome);
        return k->city;
    }else return o;
}

void rotaEntreCidades(Cidade *c){
    Cidade *p, *pp, *r;
    
    char nome[30], nome2[30];
    printf("Entre com o nome da cidade origem:\n");
    gets(nome);
    printf("Entre com o nome da cidade destino:\n");
    gets(nome2);
    
    for(p=c; p->prox!=NULL && strcmp(p->nome, nome)!=0;p=p->prox);
    if(strcmp(p->nome, nome)!=0){
        printf("Cidade origem nao encontrada!\n");
        return;
    }

    for(pp=c; pp->prox!=NULL && strcmp(pp->nome, nome2)!=0;pp=pp->prox);
    if(strcmp(pp->nome, nome2)!=0){
        printf("Cidade origem nao encontrada!\n");
        return;
    }
    r=varreGrafo(p,pp);
    //puts(r->nome);

}


main(){
    __fpurge(stdin);
    int resp=0, x, y;
    char nome[30],nome2[30];
    Cidade *c=NULL;
    c=addTodas();

    puts(c->rotas->prox->city->nome);

    while (resp!=1){
        printf("1.Cadastrar cidade.\n");
        printf("2.Cadastrar caminho.\n");
        printf("3.Remover cidade.\n");
        printf("4.Remover caminho.\n");
        printf("5.Editar cidade.\n");
        printf("6.Editar rota.\n");
        printf("7.Consultar cidade.\n");
        printf("8.Consultar rota entre cidade.\n");
        printf("9.Sair.\n");
        scanf("%d", &x);
       // fflush(stdin);
        __fpurge(stdin);

        switch (x){
            case 1:{
                printf("Entre com o nome da cidade:\n");
                gets(nome);
                c=addCidade(c,nome);
                break;

            }

            case 2:{
                printf("Entre com nova rota:\n");
                printf("De:\n");
                gets(nome);
                printf("Para:\n");
                gets(nome2);
                printf("Distancia:\n");
                scanf("%d", &y);
                addRotas(nome, nome2, y, c);
                break;
            }

            case 3:{
                c=excluiCidade(c);
                break;
            }

            case 4:{
                exlcuiRota(c);
                break;
            }

            case 5:{
                editarCidade(c);
                break;
            }

            case 6:{
                exibirCidade(c);
                break;
            }

            case 7:{
                rotaEntreCidades(c);
                break;
            }

            case 8:{
                break;
            }

            case 9:{
                printf("Saindo...\n");
                resp++;
                break;
            }

            default:{
                printf("Opcao errada...");

                break;
            }
                
        }
    }

}

void addRotas(char n1[], char n2[], int peso, Cidade *lista){
    Adj *p, *nova;
    Cidade *k, *c;
    int cont=0;
   // printf("\n");
    //puts(n1);
    for(c=lista; c->prox!=NULL && strcmp(c->nome, n1)!=0; c=c->prox);
    if(strcmp(c->nome, n1)!=0){
      
        return;
    }   

    if(c->rotas==NULL){
        for(k=lista; k->prox != NULL && strcmp(k->nome, n2)!=0 ; k=k->prox);
        if(strcmp(k->nome, n2)!=0){
            printf("nao existe a cidade ", cont);
            return;
        }
        nova=(Adj*) malloc(sizeof(Adj));
        c->rotas=nova;
        nova->peso=peso;
        nova->city=k;        
        
        nova->prox=NULL;
    }else{
        for(p=c->rotas; p->prox!=NULL; p=p->prox);
        for(k=lista; k->prox != NULL && strcmp(k->nome, n2)!=0 ; k=k->prox);
        if(strcmp(k->nome, n2)!=0){
            printf("nao existe a cidade%d\n", cont);
            return;
        }
        nova=(Adj*) malloc(sizeof(Adj));
        p->prox=nova;
                    //printf("nao existe a cidade%d\n", cont);

        nova->peso=peso;        
        nova->city=k;
        nova->prox=NULL;

    }
}


Cidade *addCidade(Cidade *c, char n[]){
    Cidade *nova, *p;
    if(c==NULL){
        nova=(Cidade*) malloc(sizeof(Cidade));
        strcpy(nova->nome, n);
        nova->prox=NULL;
        nova->rotas=NULL;
        return nova;
       
    }else{
        
        for(p=c; p->prox!=NULL; p=p->prox);
        nova=(Cidade*) malloc(sizeof(Cidade));        
        strcpy(nova->nome, n);
        nova->prox=NULL;
        nova->rotas=NULL;
        p->prox=nova;
        puts(p->nome);
        return c; 

    }

}


Cidade *addTodas(){
    char nome[30], nome2[30];
    Cidade *c=NULL;
    strcpy(nome,"SM");
    c=addCidade(c,nome);    
    strcpy(nome,"POA");
    c=addCidade(c,nome);    
    strcpy(nome,"Passo Fundo");
    c=addCidade(c,nome);
    strcpy(nome,"Pelotas");
    c=addCidade(c,nome);
    strcpy(nome,"Bage");
    c=addCidade(c,nome);
    strcpy(nome,"Sao Gabriel");
    c=addCidade(c,nome);
    strcpy(nome,"Alegrete");
    c=addCidade(c,nome);
    strcpy(nome,"Sao Borja");
    c=addCidade(c,nome);
    strcpy(nome,"Santiago");
    c=addCidade(c,nome);
    strcpy(nome,"Cruz Alta");
    c=addCidade(c,nome);
printf("\n");

    strcpy(nome, "Passo Fundo");
    strcpy(nome2, "POA");
    addRotas(nome, nome2, 289, c);

    strcpy(nome, "POA");
    strcpy(nome2, "Pelotas");
    addRotas(nome, nome2, 261, c);

    strcpy(nome, "Pelotas");
    strcpy(nome2, "Bage");
    addRotas(nome, nome2, 189, c);

    strcpy(nome, "Bage");
    strcpy(nome2, "Sao Gabriel");
    addRotas(nome, nome2, 268, c);

    strcpy(nome, "Sao Gabriel");
    strcpy(nome2, "Alegrete");
    addRotas(nome, nome2, 204, c);

    strcpy(nome, "Alegrete");
    strcpy(nome2, "Sao Borja");
    addRotas(nome, nome2, 315, c);

    strcpy(nome, "Sao Borja");
    strcpy(nome2, "Santiago");
    addRotas(nome, nome2, 141, c);

    strcpy(nome, "Santiago");
    strcpy(nome2, "Cruz Alta");
    addRotas(nome, nome2, 242, c);

    strcpy(nome, "Cruz Alta");
    strcpy(nome2, "Passo Fundo");
    addRotas(nome, nome2, 149, c);

    strcpy(nome, "Cruz Alta");
    strcpy(nome2, "SM");
    addRotas(nome, nome2, 134, c);

    strcpy(nome, "SM");
    strcpy(nome2, "Santiago");
    addRotas(nome, nome2, 152, c);

    strcpy(nome, "SM");
    strcpy(nome2, "Alegrete");
    addRotas(nome, nome2, 258, c);

    strcpy(nome, "SM");
    strcpy(nome2, "Sao Gabriel");
    addRotas(nome, nome2, 182, c);

    strcpy(nome, "SM");
    strcpy(nome2, "Bage");
    addRotas(nome, nome2, 239, c);

    strcpy(nome, "SM");
    strcpy(nome2, "POA");
    addRotas(nome, nome2, 291, c);

    strcpy(nome, "POA");
    strcpy(nome2, "Bage");
    addRotas(nome, nome2, 377, c);
    return c;
}
