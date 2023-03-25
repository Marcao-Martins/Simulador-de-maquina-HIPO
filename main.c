/* Marcos Martins de Oliveira Pacheco 13672602 */

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
int pc;
int mbr;

void executa() {
    puts("Execução:");

    int halt = 0;
    pc = 0; // pc deve começar em zero

    while (!halt) {
        // busca a instrução na memória
        mbr = M[pc];
        pc++;

        // decodifica a instrução
        int opcode = mbr / 100;
        int operand = mbr % 100;

        // executa a instrução
        switch (opcode) {
            case 10: // LDA
                acc = M[operand];
                break;
            case 11: // STA
                M[operand] = acc;
                break;
            case 20: // ADD
                acc += M[operand];
                break;
            case 21: // SUB
                acc -= M[operand];
                break;
            case 30: // JMP
                pc = operand;
                break;
            case 31: // JGE
                if (acc >= 0) {
                    pc = operand;
                }
                break;
            case 32: // JG
                if (acc > 0) {
                    pc = operand;
                }
                break;
            case 33: // JL
                if (acc < 0) {
                    pc = operand;
                }
                break;
            case 34: // JLE
                if (acc <= 0) {
                    pc = operand;
                }
                break;
            case 40: // INP
                printf("Digite um valor: ");
                scanf("%d", &acc);
                break;
            case 41: // OUT
                printf("%d\n", acc);
                break;
            case 42: // OTS
                printf("%c", acc);
                break;
            case 43: // HALT
                halt = 1;
                break;
            default:
                printf("Instrução inválida: %d\n", opcode);
                halt = 1;
                break;
        }
    }
}

int main(int argc, char *argv[]) {
    puts("Hello");
    if (argc > 1) {
        loadM(argv[1]);
        dumpM();
        executa();
    }
}
