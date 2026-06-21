#include <stdio.h>
#include"tela.h"
#include <stdlib.h>
#include <string.h>

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
//struct regiao 
//vai ter a linha e a coluna de uma parte específica da tela e vai ser usada pra marcar a area da nota, do texto de busca e da etiqueta
//a tecla tab pra navegar entre essas partes vai ser tratada num loop separado
typedef struct{
    int linha;
    int coluna;
} regiao;
//cria um enum com os modos

typedef enum{
    modo_principal,
    modo_editar_texto,
    modo_editar_etiqueta,
    modo_editar_texto_busca,
    modo_editar_etiqueta_busca,
    modo_terminar
}modo_programa;
//crio a struct de nota
typedef struct{
    char texto[200];
    char etiqueta[4];
    cor cor;
    retangulo ret;
int cursor_pos;    
}nota;


typedef struct{
nota *vnotas;
int num_notas;
int regiao_atual;
int capacidade; //quantas notas cabem no espaço alocado
regiao regioes[3]; //guarda a posição de cada região da tela
modo_programa modo;   
char texto_busca[200];
char etiqueta_busca[4];
int cursor_busca;
int indice_nota_corrente;
nota ultima_removida;
 int tem_removida ;
 } estado;

// protótipos
void recalcula_nota_corrente(estado *e);
 void ler_notas(estado *e);
int nota_e_filtrada(nota n, estado *e);
void nav_anterior(estado *e);
void nav_proxima(estado *e);
void nav_primeira(estado *e);
void nav_ultima(estado *e);
void mover_antes_anterior(estado *e);
void mover_depois_proxima(estado *e);
void mover_para_inicio(estado *e);
void mover_para_fim(estado *e);
void acao_remover(estado *e);
void acao_reinserir(estado *e);
void gravar_notas(estado *e);
void inicializar_estado(estado *e);
void liberar_estado(estado *e);
void criar_nota(estado *e);
void remover_nota(estado *e, int indice);
void executa_modo_principal(estado *e);
void executa_modo_editar_texto(estado *e);
void executa_modo_editar_etiqueta(estado *e);
void executa_modo_editar_texto_busca(estado *e);
void executa_modo_editar_etiqueta_busca(estado *e);

// funções de desenho
void divide_tela(estado *e);
void desenha_modo_principal(estado *e);
void desenha_editar_texto(estado *e);
void desenha_editar_etiqueta(estado *e);
void desenha_editar_texto_busca(estado *e);
void desenha_editar_etiqueta_busca(estado *e);

// funções de ação (lê tecla + executa)
void editar_texto(nota *n, estado *e);
void editar_etiqueta(nota *n, estado *e);
void editar_texto_busca(estado *e);
void editar_etiqueta_busca(estado *e);


// ===== main =====

int main(){
    estado e;
    inicializar_estado(&e);
    ler_notas(&e);
    t_inicia();
    divide_tela(&e);

    while(e.modo != modo_terminar){
        switch(e.modo){
    case modo_principal:
        executa_modo_principal(&e);
        break;
    case modo_editar_texto:
        executa_modo_editar_texto(&e);
        break;
    case modo_editar_etiqueta:
        executa_modo_editar_etiqueta(&e);
        break;
    case modo_editar_texto_busca:
        executa_modo_editar_texto_busca(&e);
        break;
    case modo_editar_etiqueta_busca:
        executa_modo_editar_etiqueta_busca(&e);
        break;
}

    t_fim();
    return 0;
}
}





//inicializa o estado
void inicializar_estado(estado *e){
    e->capacidade = 6;
    e->num_notas = 0;
    e->regiao_atual = 0;
    e->indice_nota_corrente = 0;
    e->modo = modo_principal;
    e->cursor_busca = 0;
    e->texto_busca[0] = '\0';
    e->etiqueta_busca[0] = '\0';
    e->vnotas = malloc(e->capacidade * sizeof(nota));
    e->tem_removida = 0;
}
//liberar o estado
void liberar_estado(estado *e){
    free(e->vnotas);
    e->vnotas = NULL;
}
//obter a nota atual
nota *obter_nota_atual(estado *e) {
    return &e->vnotas[e->regiao_atual];
}

//abre o arquivo
FILE *abre_arq(void){
    FILE *f;
    f = fopen("nota.txt", "r");
    if(f == NULL){
        return NULL;
    }
return f;    
    }


    //cria uma função pra dividira tela em regiões pra serem acessadas com tab 
void divide_tela(estado *e){
    //escreve um nome em cada parte da tela que vai ter uma região
    //ex: nota corrente, texto da nota, etiqueta
    //para que o leitor de tela consiga ler e saber em qual parte o cursor está
 t_lincol(5, 5);
printf("nota corrente");
 t_lincol(10, 10);
printf("texto de busca");
 t_lincol(15, 15);
printf("etiqueta de busca");
t_lincol(20, 5);
printf("use as cetas para cima ou para baixo para navegar entre as notas");
    // guarda as coordenadas reais de cada região em estado
    e->regioes[0].linha=5;
    e->regioes[0].coluna=5;

    e->regioes[1].linha=10;
    e->regioes[1].coluna=10;

    e->regioes[2].linha=15;
    e->regioes[1].coluna=15;
    e->regiao_atual=0;
}
//salva as notas no vetor da main, precisa passar por referência
// void salvar(estado *e=vnotas[]){
//     if(!abre_arq()) return 0;
//     while(true){
//         if(eof(f)) break;
//         *n =f;
//     }
// }
// //lista as notas
// void lista_notas(estado *e =vnotas[]){
//     for(;;){
//         printf("%d", *n);
//     }
// }




// //cria uma nova nota:
void criar_nota(estado *e){
    if(e->num_notas == e->capacidade){
        int nova_cap = e->capacidade + e->capacidade+(e->capacidade*75)/100; //almenta a capacidade entre os 50-100%
e->vnotas = realloc(e->vnotas, nova_cap*sizeof(nota));
e->capacidade = nova_cap;

    }
    //inicializa a nota criada na posição num_notas
    e->num_notas ++;
}

//remover a nota e encolhe o espaço quando fica abaixo de 30 %
void remover_nota(estado *e, int indice){
    //deslocar as notas uma posição pra tras
    for(int i=indice; i <e->num_notas; i++){
        e->vnotas[i] = e->vnotas[i+1];
    }
    e->num_notas --;

if(e->num_notas < (e->capacidade*30) /100){
int nova_cap = e->capacidade /2;
e->vnotas = realloc(e->vnotas, nova_cap *sizeof(nota));
 e->capacidade = nova_cap;
}

}


//edição do texto da nota
void editar_texto(nota *n, estado *e){
char buffer[200]; //buffer da edição da nota
tecla_t tecla_digitada = t_tecla(); //le a tecla digitada com a função t_tecla de tela.h

strcpy(buffer, n->texto);
//fazer um switch para colocar cada comando em uma tecla
 switch(tecla_digitada){
    case T_ENTER:
    strcpy(n->texto, buffer);
    e->modo=modo_principal;
    break;
    case T_ESC:
    case T_CTRL_C:
e->modo=modo_principal;
break;
    
    
    case T_CTRL_B:
    case T_BS:
    //se a posição do cursor for maior que 0, subtrai 1 dessa posição e apaga um caractere
    if(n->cursor_pos >0){
        n->cursor_pos--;
        int tamanho = strlen(buffer);
        for(int i =n->cursor_pos; i<tamanho; i++){
            buffer[i] = buffer[i+1];
        }
    }
        break;
        case T_DEL:
        case T_CTRL_D:
        //se o cursor estiver em uma posição inferior ao tamanho do texto, remove o caractere na posição do cursor
        if(n->cursor_pos <(int)strlen(buffer)){
            int tamanho = strlen(buffer);
            for(int i=n->cursor_pos; i<tamanho; i++){
                buffer[i] = buffer[i+1];
            }
        }
                break;
                case T_CTRL_H:
                case T_ESQUERDA:
                //se a posição do cursor for maior que 0, subtrai 1 dessa posição
                if(n->cursor_pos>0){
                    n->cursor_pos --;
                }
break;
                                case T_CTRL_L:
                                case T_DIREITA:
                                //Se a posição do cursor for menor que o tamanho do texto, soma 1 nessa posição
                                if(n->cursor_pos <(int)strlen(buffer)){
                                    n->cursor_pos++;
                                }
break;
case T_NADA:
break;
default:
//se tecla_digitada for um caractere imprimível e se houver espaço no buffer, insere um caractere na posição do cursor
if(tecla_digitada >=32&&tecla_digitada<=126){
    int tamanho =strlen(buffer);
    if(tamanho<200-1){
    for(int i=tamanho; i>n->cursor_pos; i--){
        buffer[i+1] = buffer[i];
        
    }
    buffer[n->cursor_pos] = (char) tecla_digitada;
    buffer[tamanho+1] ='\0';
        n->cursor_pos++;
}
}
//se for qualquer outro caractere, como só ctrl precionado ou uma tecla desconhecida, ignora
break;
 }
}

//edição da etiqueta
void editar_etiqueta(nota *n, estado *e){
char buffer[4];
tecla_t tecla_digitada = t_tecla();
strcpy(buffer, n->etiqueta);
    //switch com os comandos de teclado para esse modo
    switch(tecla_digitada){
        case T_CTRL_C:
        //modo principal
        e->modo=modo_principal;
        break;
        case T_ESC:
                //modo principal
                e->modo=modo_principal;
                break;
                case T_CTRL_D:
                //remove o o último caractere da etiqueta, se houver
    {                int tamanho = strlen(buffer);
                if(tamanho>0){
                    buffer[tamanho-1] = '\0';
                }
            }
                break;
                   case T_ENTER:
                   //se tiver 3 caracteres imprimiveis salva a etiqueta e volta para o modo principal
                   {
int tamanho = strlen(buffer);
if(tamanho ==4){
    strcpy(buffer, n->etiqueta);
}
                   }
break;
case T_CTRL_T:
case T_SHIFT_ENTER:
//se a etiqueta tiver 3 caracteres imprimíveis troca todas as notas para essa etiqueta e muda para o modo principal
{
int tamanho = strlen(buffer);
if(tamanho ==4){
    for(int i=0; i<e->num_notas; i++){
        strcpy(e->vnotas[i].etiqueta, buffer);
    }
}
}
break;
default:
if(tecla_digitada>=32 &&tecla_digitada<=126){
    int tamanho = strlen(buffer);
    if(tamanho<3){
    if(tamanho+1=='\0'){
        buffer[tamanho] = (char) tecla_digitada;
    }
}
}
break;

    
    }
}

//edição do texto de busca
void editar_texto_busca(estado *e){
    char buffer[200];
    tecla_t tecla_digitada = t_tecla();
    strcpy(buffer, e->texto_busca);
//switch dos atalhos
switch(tecla_digitada){
    case T_CTRL_C:
        case T_ESC:
    //esvazia o texto de busca e volta para o modo principal
    buffer[0] ='\0';
    e->modo = modo_principal;
    break;


        case T_ENTER:
        //muda para o modo principal
        e->modo=modo_principal;
        break;
        case T_CTRL_B:
        case T_BS:
//se o cursor não estiver no início, recua o cursor e remove 1 caractere
        if(e->cursor_busca>0){
           e->cursor_busca--;
int tamanho = strlen(buffer);
for(int i=e->cursor_busca; i<tamanho; i++){
buffer[i] = buffer[i+1];
}

        }
break;
        case T_CTRL_D:
        case T_DEL:
//se o cursor não estiver no final, remova o caractere do cursor
        if(e->cursor_busca<strlen(buffer)){
        int tamanho = strlen(buffer);
        for(int i=e->cursor_busca; i<tamanho; i++){
                buffer[i] = buffer[i+1];
            
        }
    }
            break;
        
        case T_CTRL_H:
case T_ESQUERDA:
//move esq
e->cursor_busca--;
break;
       case T_CTRL_L:
       case T_DIREITA:
        //move dir
       e->cursor_busca ++;
        break;
        case T_CTRL_K:
        case T_HOME:
        //cursor = 0
        e->cursor_busca=0;
break;
                case T_CTRL_J:
                                case T_END:
//muda o cursor para o tamanho do texto de busca
e->cursor_busca=strlen(buffer); 
                break;
                default:
                if(tecla_digitada>=32 &&tecla_digitada<=126){
                    int tamanho = strlen(buffer);
                    if(tamanho <200){
                        for(int i=tamanho; i>e->cursor_busca; i--){
        buffer[i+1]= buffer[i];
                        }
                        buffer[e->cursor_busca] = (char) tecla_digitada;
                        buffer[e->cursor_busca+1]='\0';
                        e->cursor_busca++;
                    }
                }
                    //outra tecla extranha, ignora
                    break;
                
}
}
//edição da etiqueta de busca
void editar_etiqueta_busca(estado *e){
char buffer[4];
tecla_t tecla_digitada = t_tecla();
strcpy(buffer, e->etiqueta_busca);
    //switch
    switch(tecla_digitada){
        case T_CTRL_C:
        case T_ESC:
    //esvazia o texto de busca e volta para o modo principal
    buffer[0]='\0';
    e->modo=modo_principal;
    break;

    case T_ENTER:
    //modo principal
    e->modo=modo_principal;
    break;
    
    case T_CTRL_B:
    case T_BS:
//remove o caractere final da etiqueta se houver
    {
        int tamanho = strlen(buffer);
        if(tamanho>0){
            buffer[tamanho-1] = '\0';
        }
    }
break;
default:
if(tecla_digitada>=32 &&tecla_digitada<=126){
    int tamanho = strlen(buffer);
    if(tamanho <3){
buffer[tamanho] = (char) tecla_digitada;

}

}
//outra tecla ignora
break;
    }
}


void executa_modo_principal(estado *e){
    while(e->modo == modo_principal){
        desenha_modo_principal(e);

        tecla_t tecla_digitada = t_tecla();

        switch(tecla_digitada){




            case 'k':
case T_CIMA:
    nav_anterior(e);
    break;
case 'j':
case T_BAIXO:
    nav_proxima(e);
    break;
case 'K':
case T_HOME:
    nav_primeira(e);
    break;
case 'J':
case T_END:
    nav_ultima(e);
    break;
case T_CTRL_K:
    mover_antes_anterior(e);
    break;
case T_CTRL_J:
    mover_depois_proxima(e);
    break;
            case 'i':
    mover_para_inicio(e);
    break;

case 'f':
    mover_para_fim(e);
    break;

case 'd':
case T_DEL:
    acao_remover(e);
    break;

case 'I':
case T_INS:
    acao_reinserir(e);
    break;

case 'g':
    gravar_notas(e);
    break;
            case 'e':
                e->modo = modo_editar_texto;
                break;

            case 't':
                e->modo = modo_editar_etiqueta;
                break;
case 'n':
criar_nota(e);
break;
            case 'b':
                e->modo = modo_editar_texto_busca;
                break;

            case 'B':
                e->modo = modo_editar_etiqueta_busca;
                break;

            case 'q':
                e->modo = modo_terminar;
                break;

            case T_NADA:
                break;
        }
    }
}

void executa_modo_editar_texto(estado *e){
    while(e->modo == modo_editar_texto){
        desenha_editar_texto(e);
        editar_texto(&e->vnotas[e->indice_nota_corrente], e);
    }
}

void executa_modo_editar_etiqueta(estado *e){
    while(e->modo == modo_editar_etiqueta){
        desenha_editar_etiqueta(e);
        editar_etiqueta(&e->vnotas[e->indice_nota_corrente], e);
    }
}

void executa_modo_editar_texto_busca(estado *e){
    while(e->modo == modo_editar_texto_busca){
        desenha_editar_texto_busca(e);
        editar_texto_busca(e);
    }
        recalcula_nota_corrente(e);
}

void executa_modo_editar_etiqueta_busca(estado *e){
    while(e->modo == modo_editar_etiqueta_busca){
        desenha_editar_etiqueta_busca(e);
        editar_etiqueta_busca(e);
    }
        recalcula_nota_corrente(e);
}


void desenha_modo_principal(estado *e){
    int nao_filtradas = 0;
    for(int i = 0; i < e->num_notas; i++){
        if(!nota_e_filtrada(e->vnotas[i], e)){
            nao_filtradas++;
        }
    }

    t_lincol(5, 5);
    if(e->num_notas > 0){
        printf("Nota corrente: %s | Etiqueta: %s", e->vnotas[e->indice_nota_corrente].texto, e->vnotas[e->indice_nota_corrente].etiqueta);
    } else {
        printf("Nenhuma nota criada ainda");
    }

    t_lincol(6, 5);
    printf("Notas nao filtradas: %d de %d", nao_filtradas, e->num_notas);

    fflush(stdout);
}

void desenha_editar_texto(estado *e){
    t_lincol(5, 5);
    printf("Editando texto: %s", e->vnotas[e->indice_nota_corrente].texto);
    fflush(stdout);
}

void desenha_editar_etiqueta(estado *e){
    t_lincol(15, 5);
    printf("Editando etiqueta: %s", e->vnotas[e->indice_nota_corrente].etiqueta);
    fflush(stdout);
}

void desenha_editar_texto_busca(estado *e){
    t_lincol(10, 5);
    printf("Texto de busca: %s", e->texto_busca);
    fflush(stdout);
}

void desenha_editar_etiqueta_busca(estado *e){
    t_lincol(10, 5);
    printf("Etiqueta de busca: %s", e->etiqueta_busca);
    fflush(stdout);
}


void mover_para_inicio(estado *e){
    int idx = e->indice_nota_corrente;
    nota atual = e->vnotas[idx];
    for(int i = idx; i > 0; i--){
        e->vnotas[i] = e->vnotas[i-1];
    }
    e->vnotas[0] = atual;
    e->indice_nota_corrente = 0;
}

void mover_para_fim(estado *e){
    int idx = e->indice_nota_corrente;
    nota atual = e->vnotas[idx];
    for(int i = idx; i < e->num_notas - 1; i++){
        e->vnotas[i] = e->vnotas[i+1];
    }
    e->vnotas[e->num_notas - 1] = atual;
    e->indice_nota_corrente = e->num_notas - 1;
}

void acao_remover(estado *e){
    if(e->num_notas == 0) return;
    e->ultima_removida = e->vnotas[e->indice_nota_corrente];
    e->tem_removida = 1;
    remover_nota(e, e->indice_nota_corrente);
    if(e->indice_nota_corrente >= e->num_notas && e->num_notas > 0){
        e->indice_nota_corrente = e->num_notas - 1;
    }
}

void acao_reinserir(estado *e){
    if(!e->tem_removida) return;
    criar_nota(e); // já aloca espaço e incrementa num_notas, posição = num_notas-1
    e->vnotas[e->num_notas - 1] = e->ultima_removida;
    e->indice_nota_corrente = e->num_notas - 1;
    e->tem_removida = 0;
}


void gravar_notas(estado *e){
    FILE *f = fopen("notas.txt", "w");
    if(f == NULL) return;

    for(int i = 0; i < e->num_notas; i++){
        fprintf(f, "%s %s\n", e->vnotas[i].etiqueta, e->vnotas[i].texto);
    }

    fclose(f);
}


int nota_e_filtrada(nota n, estado *e){
    if(strlen(e->texto_busca) > 0){
        if(strstr(n.texto, e->texto_busca) == NULL){
            return 1; // filtrada
        }
    }
    if(strlen(e->etiqueta_busca) > 0){
        if(strstr(n.etiqueta, e->etiqueta_busca) == NULL){
            return 1; // filtrada
        }
    }
    return 0; // não filtrada
}


void nav_anterior(estado *e){ // k / seta cima
    for(int i = e->indice_nota_corrente - 1; i >= 0; i--){
        if(!nota_e_filtrada(e->vnotas[i], e)){
            e->indice_nota_corrente = i;
            return;
        }
    }
}

void nav_proxima(estado *e){ // j / seta baixo
    for(int i = e->indice_nota_corrente + 1; i < e->num_notas; i++){
        if(!nota_e_filtrada(e->vnotas[i], e)){
            e->indice_nota_corrente = i;
            return;
        }
    }
}

void nav_primeira(estado *e){ // K / Home
    for(int i = 0; i < e->num_notas; i++){
        if(!nota_e_filtrada(e->vnotas[i], e)){
            e->indice_nota_corrente = i;
            return;
        }
    }
}

void nav_ultima(estado *e){ // J / End
    for(int i = e->num_notas - 1; i >= 0; i--){
        if(!nota_e_filtrada(e->vnotas[i], e)){
            e->indice_nota_corrente = i;
            return;
        }
    }
}

void mover_antes_anterior(estado *e){ // ctrl+k
    int idx = e->indice_nota_corrente;
    int destino = 0;
    for(int i = idx - 1; i >= 0; i--){
        if(!nota_e_filtrada(e->vnotas[i], e)){
            destino = i;
            break;
        }
    }
    nota atual = e->vnotas[idx];
    for(int i = idx; i > destino; i--){
        e->vnotas[i] = e->vnotas[i-1];
    }
    e->vnotas[destino] = atual;
    e->indice_nota_corrente = destino;
}

void mover_depois_proxima(estado *e){ // ctrl+j
    int idx = e->indice_nota_corrente;
    int destino = e->num_notas - 1;
    for(int i = idx + 1; i < e->num_notas; i++){
        if(!nota_e_filtrada(e->vnotas[i], e)){
            destino = i;
            break;
        }
    }
    nota atual = e->vnotas[idx];
    for(int i = idx; i < destino; i++){
        e->vnotas[i] = e->vnotas[i+1];
    }
    e->vnotas[destino] = atual;
    e->indice_nota_corrente = destino;
}


void ler_notas(estado *e){
    FILE *f = fopen("notas.txt", "r");
    if(f == NULL) return;

    FILE *problemas = NULL;
    char linha[400];

    while(fgets(linha, sizeof(linha), f) != NULL){
        char linha_etiqueta[4];
        char linha_texto[200];

        int lidos = sscanf(linha, "%3s %199[^\n]", linha_etiqueta, linha_texto);

        // verifica se a etiqueta tem exatamente 3 caracteres
        if(lidos == 2 && strlen(linha_etiqueta) == 3){
            criar_nota(e);
            int pos = e->num_notas - 1;
            strcpy(e->vnotas[pos].etiqueta, linha_etiqueta);
            strcpy(e->vnotas[pos].texto, linha_texto);
        } else {
            // linha malformada: copia para problemas.txt
            if(problemas == NULL){
                problemas = fopen("problemas.txt", "w");
            }
            if(problemas != NULL){
                fputs(linha, problemas);
            }
        }
    }

    if(problemas != NULL){
        fclose(problemas);
    }
    fclose(f);
}



void recalcula_nota_corrente(estado *e){
    for(int i = e->num_notas - 1; i >= 0; i--){
        if(!nota_e_filtrada(e->vnotas[i], e)){
            e->indice_nota_corrente = i;
            return;
        }
    }
    // se nenhuma nota não-filtrada existir, mantém o índice como está
}