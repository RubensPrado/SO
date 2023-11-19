#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

// Defina o offset onde os dados da imagem começam no arquivo BMP
#define BMP_DATA_OFFSET 54

static int hello_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    FILE *file = fopen("meu_sistema_de_arquivos.bmp", "rb");
    if (!file) return -ENOENT;

    // Pula para o início dos dados da imagem
    fseek(file, BMP_DATA_OFFSET, SEEK_SET);

    // Lê os dados
    size_t result = fread(buf, 1, size, file);
    if (result != size) {
        fclose(file);
        return -EIO;
    }

    fclose(file);
    return size;
}

static int hello_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    FILE *file = fopen("meu_sistema_de_arquivos.bmp", "r+b");
    if (!file) return -ENOENT;

    // Pula para o início dos dados da imagem
    fseek(file, BMP_DATA_OFFSET, SEEK_SET);

    // Escrever dados
    size_t result = fwrite(buf, 1, size, file);
    if (result != size) {
        fclose(file);
        return -EIO;
    }

    fclose(file);
    return size;
}