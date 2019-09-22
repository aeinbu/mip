#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool showDebug = false;

// void debugPrint(char* format, char *args, ...) {
// 	printf(format, args);
// }

struct mipPacket{
    unsigned char T : 1;
    unsigned char R : 1;
    unsigned char A : 1;
    unsigned char TTL : 4;
    unsigned int PayloadLength : 9;
    char destinationMipAddress;
    char SourceMipAddress;
};


void printMipPacket(const char *buffer) {
    const struct mipPacket *headers;
    headers = (struct mipPacket*)buffer;
    const char *payload = buffer + 4;

    printf("--> T:%d-R:%d-A:%d, TTL:%d, PayloadLength:%d x 4bytes, Dest:%c Src:%c\n", headers->T, headers->R, headers->A, headers->TTL, headers->PayloadLength, headers->destinationMipAddress, headers->SourceMipAddress);
    printf("    Payload string: [");
    for(int i = 0; i < headers->PayloadLength * 4; i++){
        printf("%c", payload[i]);
    }
    printf("]\n");
    printf("    Payload hex: 0x");
    for(int i = 0; i < headers->PayloadLength * 4; i++){
        printf("%x", payload[i]);
    }
    printf("\n");

}

int main(int args, char *argv[]) {
    fprintf(stdout, "*** daemon starting!\n");

    struct mipPacket myPacket;
    myPacket.T = 0;
    myPacket.R = 0;
    myPacket.A = 1;
    myPacket.TTL = 0xF;
    myPacket.PayloadLength = 0x003;
    myPacket.destinationMipAddress = 'B';
    myPacket.SourceMipAddress = 'A';

    char *buffer = malloc(12);
    memcpy(buffer, &myPacket, 4);
    memcpy(buffer + 4, "hello world\0", 12);

    printMipPacket(buffer);

    return 0;
}
