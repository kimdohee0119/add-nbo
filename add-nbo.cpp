#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <netinet/in.h>

uint32_t my_ntohl(uint32_t a){
    uint32_t a1 = (a & 0xFF000000) >> 24;
        printf("%x\n", a1);
        uint32_t a2 = (a & 0x00FF0000) >> 8;
        printf("%x\n", a2);
        uint32_t a3 = (a & 0x0000FF00) << 8;
        printf("%x\n", a3);
        uint32_t a4 = (a & 0x000000FF) << 24;
        printf("%x\n", a4);
        return a1 | a2 | a3 | a4;
}

void add(uint32_t network_buffer1[], uint32_t network_buffer2[]) {
    uint32_t* p1 = reinterpret_cast<uint32_t*>(network_buffer1);
    uint32_t n1 = my_ntohl(*p1);

    uint32_t* p2 = reinterpret_cast<uint32_t*>(network_buffer2);
    uint32_t n2 = my_ntohl(*p2);

    printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n",n1, n1, n2, n2, n1+n2, n1+n2);
}

int main(int argc, char *argv[]) {
    if(argc != 3){
        printf("syntax : add-nbo <file1> <file2> \n");
        printf("sample : add-nbo a.bin c.bin \n");
        return -1;
    }

    uint32_t network_buffer1, network_buffer2; 
    FILE *f_1 = fopen(argv[1], "rb");
    FILE *f_2 = fopen(argv[2], "rb");

    fread(&network_buffer1, sizeof(uint32_t), 1, f_1); fread(&network_buffer2, sizeof(uint32_t), 1, f_2);

    add(&network_buffer1, &network_buffer2);
    fclose(f_1); fclose(f_2);
}
