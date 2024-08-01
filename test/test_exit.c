#include <stdlib.h>
#include <stdio.h>

__attribute__((destructor))
static void destructor() {
   system("leaks -q a.out");
}

void allocate_memory() {
    char *buffer = malloc(1024); // メモリを確保
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE); // メモリを解放せずにプロセスを終了
    }
	exit(EXIT_SUCCESS); // メモリを解放せずにプロセスを終了
    // 他の処理
}

int main() {
    allocate_memory();
    // 他の処理
    return 0;
}
