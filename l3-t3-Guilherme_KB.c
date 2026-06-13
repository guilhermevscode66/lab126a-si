#include <stdio.h>
#include"tela.h"

//ações do modo principal:
typedef enum{
    nota_p_inicio = T_HOME,
    nota_p_fim = T_END,
    remove_nota = T_DEL,
    reinsere_nota = T_INS,
    cria_nota = 'n',
    grava_notas = 'g',
    edita_texto = 'e',
    texto_busca = 'b',
    nota_ant = T_CIMA,
    nota_prox = T_BAIXO,
    Editar_etiqueta = 't',
    etiqueta_busca = 'B'
} principal_et;

//ações do modo de etição de texto
typedef enum{
    confirma_edicao = T_ENTER,
    cancela_edicao = T_ESC,
    remove_char = T_BS,
    remove_char_cursor = T_DEL,
char_ant = T_ESQ,
char_prox = T_DIR,

} edicao_texto;

//edição da etiqueta
typedef enum{
    modo_principal = T_ESC, //Volta para o modo princiapl
    remove_ult_char = T_BS, //remove o último caractere sendo editado
    salva_et = T_ENTER, //salva a etiqueta
    troca_todas_et = ST_ENTER, //troca a etiquetta de todas as notas visíveis e retorna ao modo principal;
}et_busca;
//edição do texto de busca
typedef enum{
    limpa_texto= T_ESC, //esvazia o texto de busca e cmuda para o modo principal
modo_principal = T_ENTER, //muda para o modo principal sem limpar o texto
remove_char = T_BS, // se o cursor não estiver no início, recua o cursor e remove o caractere do cursor;
remove_char_fim = T_DEL, //se o cursor não estiver no final, remove o caractere do cursor;
linha_ant = T_CIMA, //move o cursor para a linha anterior;
linha_prox = T_BAIXO, //Move o cursor para a próxima linha;
move_inicio = T_HOME, //move o cursor para o início do texto;
move_fim = T_END //move o cursor para o fim do texto;
}edicao_etiqueta;
//edição do texto de busca

typedef enum{
    limpa_texto = T_ESQ, //esvazia o texto de busca e muda para o modo principal;
    modo_principal = T_ENTER, //volta para o modo principal sem limpar o texto;
    remove_char = T_BS, // se o cursor não estiver no início, recua o cursor e remove o caractere do cursor;
    remove_char_fim = T_DEL, //se o cursor não estiver no final, remove o caractere do cursor;
    linha_ant = T_CIMA, // move para a linha anterior;
linha_prox = T_BAIXO, //move para a próxima linha;
move_inicio = T_HOME, //move o cursor para o início;
muda_tam= T_END //Altera o  cursor para o tamanho do texto de busca
}edicao_texto_busca;

//edição da etiqueta de busca
typedef enum{
    limpa_texto = T_ESC, //esvazia a etiqueta de busca e muda para o modo principal
    modo_principal = T_ENTER, //muda para o modo principal sem limpar o texto;
    remove_char = T_BS, //remove o caractere final da etiqueta de busca, se houver

    
}


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

//lista as notas
int lista_notas(){
    if(!abre_arq){
        return 0;
    }
    //?
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


}




//main
int main(){
    //registro de notas

    typedef struct{
nota vnotas[];
int *cursor = vnotas[0];
    }

//chama a função que coloca a tela e o teclado em modo cru
t_inicia();


//volta a tela e o teclado para o modo normal
t_fim();
    }