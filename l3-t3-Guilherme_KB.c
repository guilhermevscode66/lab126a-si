#include <stdio.h>
#include"tela.h"



//struct cor
typedef struct{
    int r;
    int g;
    int b;
} cor;
//struct retangulo
typedef struct{
    int x;
    int y;
    int altura;
    int largura;
}retangulo;

//crio a struct de nota
typedef struct{
    char texto[200];
    char etiqueta[3];
    cor cor;
    retangulo ret;
}nota;
//abre o arquivo
int abre_arq(){
    file *f;
    f = fopen("nota.txt", "r");
    if(f == NULL){
        
        return 0;
    }
return f;    
    }


    //cria uma função pra dividira tela em regiões pra serem acessadas com tab 
void divide_tela(){
    //escreve um nome em cada parte da tela que vai ter uma região
    //ex: nota corrente, texto da nota, etiqueta
    //para que o leitor de tela consiga ler e saber em qual parte o cursor está
int nota_corrente = t_lincol(5, 5);
printf("nota corrente");
int texto_busca = t_lincol(10, 10);
printf("texto de busca");
int etiqueta_busca = t_lincol(15, 15);
printf("etiqueta de busca");
printf("\n use as cetas para cima ou para baixo para navegar entre as")
//cria a struct que vai ter  linha e coluna, as regiões vão ser do tipo struct, vão vir dessa struct
typedef struct{
    int linha;
    int coluna;
}regiao;
//cria um array das três regiões da tela, cada uma vai ter uma 'coordenada'
regiao regioes[3]={
{nota_corrente}, //parte da nota corrente
{texto_busca}, //parte do texto de busca
{etiqueta_busca} //parte da etiqueta de busca
};
int regiao_atual =0

if(t_tecla(T_TAB)){
regiao_atual = (regiao_atual+1)%3;
    printf("\033[%d;%dH", regioes[regiao_atual].linha, regioes[regiao_atual].coluna);
    fflush(stdout);
}
}
//salva as notas no vetor da main, precisa passar por referência
void salvar(estado *n=vnotas[]){
    if(!abre_arq()) return 0;
    while(true){
        if(eof(f)) break;
        *n =f;
    }
}
//lista as notas
void lista_notas(estado *n =vnotas[]){
    for(;;){
        printf("%d", *n);
    }
}


//cria o modo principal:
void modo_principal(){ //só printa a lista de notas e permite navegar, não retorna nada
if(!lista_notas()){
    printf("não foi possível abrir o arquivo.");
}


}

//edição do texto da nota
void editar_texto(nota *n){
char buffer[] = n->texto[];
//fazer um switch para colocar cada comando em uma tecla
switch(t_tecla){
    case T_ENTER:
    n -> texto[] = buffer[];
    //mudar pro modo principal, descobrir como
    case T_ESC:
    //mudar para o modo principal
    case T_CTRL_C:
    //modo principal
    case T_CTRL_B:
    //se a posição do cursor for maior que 0, subtrai 1 dessa posição e apaga um caractere
    case T_BS:
        //se a posição do cursor for maior que 0, subtrai 1 dessa posição e apaga um caractere
        case T_DEL:
        //se o cursor estiver em uma posição inferios ao tamanho do texto, remove o caractere na posição do cursor
        case T_CTRL_D:
                //se o cursor estiver em uma posição inferios ao tamanho do texto, remove o caractere na posição do cursor
                case T_CTRL_H:
                //se a posição do cursor for maior que 0, subtrai 1 dessa posição
                case T_ESQUERDA:
                                //se a posição do cursor for maior que 0, subtrai 1 dessa posição
                                case T_CTRL_L:
                                //Se a posição do cursor for menor que o tamanho do texto, soma 1 nessa posição
                                case T_DIREITA:
                                                                //Se a posição do cursor for menor que o tamanho do texto, soma 1 nessa posição
}

}

//edição da etiqueta
void editar_etiqueta(nota *n){
    char buffer[] = n -> etiqueta[];
    //switch com os comandos de teclado para esse modo
    switch(t_tecla){
        case T_CTRL_C:
        //modo principal
        case T_ESC:
                //modo principal
                case T_CTRL_D:
                //remove o o último caractere da etiqueta, se houver
                case T_ENTER:
                if(buffer[] ==3){
n -> etiqueta[] = buffer[];
//muda para o modo principal
case T_CTRL_T:
//se a etiqueta tiver 3 caracteres troca todas as notas para essa etiqueta e muda para o modo principal
case T_SHIFT_ENTER:
//se a etiqueta tiver 3 caracteres troca todas as notas para essa etiqueta e muda para o modo principal

                }
    }
}


//edição do texto de busca
void editar_texto_busca(nota *n){
//switch dos atalhos
switch(t_tecla){
    case T_CTRL_C:
    //esvazia o texto de busca e volta para o modo principal
    case T_ESC:
        //esvazia o texto de busca e volta para o modo principal
        case T_ENTER:
        //muda para o modo principal
        case T_CTRL_B:
//se o cursor não estiver no início, recua o cursor e remove 1 caractere
        case T_BS:
        //se o cursor não estiver no início, recua o cursor e remove 1 caractere
        case T_CTRL_D:
//se o cursor não estiver no final, remova o caractere do cursor
        case T_DEL:
        //se o cursor não estiver no final, remova o caractere do cursor
        case T_CTRL_H:
//move esq
case T_ESQ
//move esq
        T_CTRL_L:
        //move dir
        case T_DIR
        //move dir
        case T_CTRL_K:
        //cursor = 0
        case T_HOME:
                //cursor = 0
                case T_CTRL_J:
//muda o cursor para o tamanho do texto de busca
                case T_END:
                //muda o cursor para o tamanho do texto de busca
}
}
//edição da etiqueta de busca
void editar_etiqueta_busca(nota *n){

    //switch
    switch(t_tecla){
        case T_CTRL_C:
    //esvazia o texto de busca e volta para o modo principal
    case T_ESC:
        //esvazia o texto de busca e volta para o modo principal
    case T_ENTER:
    //modo principal
    case T_CTRL_B:
//remove o caractere final da etiqueta se houver
    case T_BS:
    //remove o caractere final da etiqueta se houver
    }
}

//main
int main(){
    //registro de notas

    typedef struct{
nota vnotas[];
    } estado;

//chama a função que coloca a tela e o teclado em modo cru
t_inicia();


//volta a tela e o teclado para o modo normal
t_fim();
    }