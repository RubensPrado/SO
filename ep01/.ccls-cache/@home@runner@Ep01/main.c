/*
Paulo Augusto Siqueira Vaamonde
Engenharia da Computação
*/

#include <stdio.h>
#include <string.h>

#define MEM_SIZE 4096  // 4KB

typedef struct Block {
    size_t size;
    struct Block* next;
} Block;

static char heap[MEM_SIZE];
static Block* freeList = NULL;

void init_memory() {
    freeList = (Block*) heap;
    freeList->size = MEM_SIZE;
    freeList->next = NULL;
}

void* aloca(size_t size) {
    size += sizeof(Block);
    Block** curr = &freeList;

    while (*curr) {
        if ((*curr)->size >= size) {
            Block* used = *curr;
            *curr = (Block*) (((char*) *curr) + size);

            (*curr)->size = used->size - size;
            (*curr)->next = used->next;

            used->size = size;
            return (void*) (used + 1);
        }
        curr = &(*curr)->next;
    }

    return NULL;  // Sem espaço disponível
}

void libera(void* ptr) {
    if (ptr == NULL) {
        return;
    }

    Block* block = ((Block*) ptr) - 1;
    block->next = freeList;
    freeList = block;
}

void listar() {
    Block* curr = freeList;
    while (curr) {
        printf("Bloco livre: %p, tamanho: %zu bytes\n", (void*) curr, curr->size);
        curr = curr->next;
    }
}

int main() {
    init_memory();

    char action;
    size_t size;

    while (1) {
        printf("Deseja alocar (a)\nliberar (l)\nlistar (s)\nsair (q)?\n ");
        scanf(" %c", &action);

        switch (action) {
            case 'a':
                printf("Qual o tamanho que deseja alocar?\n ");
                scanf("%zu", &size);
                void* mem = aloca(size);
                if (mem) {
                    printf("Memória alocada em: %p\n\n", mem);
                } else {
                    printf("Não foi possível alocar memória.\n");
                }
                break;

            case 'l':
                printf("Endereço para liberar (formato hexadecimal): \n");
                void* ptr;
                scanf("%p", &ptr);
                libera(ptr);
                printf("Memória liberada.\n");
                break;

            case 's':
                listar();
                break;

            case 'q':
                return 0;

            default:
                printf("Opção inválida.\n");
        }
    }

    return 0;
}
