/* Substitua por seu nome e seu número USP */

/* O processador executa instruções a partir do endereço zero.
 * as instruções DDF e DFF não precisam ser codificadas.
 * as instruções de deslocamento preservam o sinal.
 * a instrução PAR termina o simulador. */
 
#include <stdio.h>
#include <stdlib.h>

#define MEMSIZE 10000

int M[MEMSIZE];  // representa a memória do HIPO.

void loadM(char *imgFileName) {
    FILE *fp;
    fp = fopen(imgFileName, "rt");
    int i = 0;
    while (!feof(fp)) {
        printf("lendo linha %d ", i);
        /* quem escrever o conteúdo da memória deve ter o cuidado de fazê-lo 
         * conforme a especificação. Esta função não checa. */
        /* podem acontecer coisas inesperadas caso falte ou sobre \n no arquivo. 
         * */
        fscanf(fp, "%d\n", &(M[i]));
        printf("conteúdo: %d ", M[i]);
        ++i;
    }
    fclose(fp);
}

void dumpM() {
    for (int i = 0; i < MEMSIZE; i++) {
        printf("(%d,%d)\t", i, M[i]);
    }
}

int acc;
int pc;  // ou ai
int mbr; // talvez não seja necessário.

void executa() {
    puts("Execução:");
    /* insira seu programa aqui. */
    /* caso crie outras funções, crie neste arquivo (e chame-as aqui ou onde
     * for conveniente */

    pc = 0; // inicializa o program counter

    while (1) {
        // pega a instrução do endereço apontado por pc
        mbr = M[pc];

        // separa o código da operação e o endereço de memória
        int opcode = mbr / 100;
        int address = mbr % 100;

        // executa a instrução de acordo com o opcode
        switch (opcode) {
            case 5:
                acc = M[address];
                break;
            case 1:
                acc += M[address];
                break;
            case 2:
                acc -= M[address];
                break;
            case 3:
                M[address] = acc;
                break;
            case 4:
                pc = address;
                continue; // pula a atualização do PC
            case 6:
                printf("%d\n", acc);
                break;
            case 7:
                exit(0);
                break;
            default:
                printf("Instrução inválida: %d\n", mbr);
                exit(1);
        }

        // incrementa o program counter
        pc++;
    }
}

int main(int argc, char *argv[]) {
    puts("Hello");
    if (argc > 1) {
        /* Um computador frequentemente tem um programa que carrega um 
         * executável na memória. Esse programa é mais complicado que o tipo
         * de programa que é suficiente para oferecer um entendimento básico
         * dos conceitos que quero explorar na disciplina. Por isso, a carga de
         * um programa na memória, neste simulador, é algo feito "por fora"
         * da simulação.
         * */
        loadM(argv[1]);
        dumpM();
        executa();
    }
    }
   
