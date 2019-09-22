
#include <math.h>
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
    char DestinationMipAddress;
    char SourceMipAddress;
};

const size_t HEADER_SIZE = sizeof(struct mipPacket);


void printMipPacket(const char *buffer) {
    const struct mipPacket *headers = (struct mipPacket*)buffer;
    const char *payload = buffer + HEADER_SIZE;

    printf("--> T:%d-R:%d-A:%d, TTL:%d, PayloadLength:%d x 4bytes, Dest:%c Src:%c\n", headers->T, headers->R, headers->A, headers->TTL, headers->PayloadLength, headers->DestinationMipAddress, headers->SourceMipAddress);

    printf("    Payload string: \"");
    for(int i = 0; i < headers->PayloadLength * 4; i++){
        if(payload[i] == 0) {
            printf("\\0");
        }
        else
        {
            printf("%c", payload[i]);
        }
    }
    printf("\"\n");

    printf("    Payload hex: 0x");
    for(int i = 0; i < headers->PayloadLength * 4; i++){
        printf("%02x", payload[i]);
    }
    printf("\n");
}


int main(int args, char *argv[]) {
    fprintf(stdout, "*** daemon starting!\n");

    char *payload = "nothing to see, move along\0";
    size_t payloadLength = strlen(payload);

    size_t bufferLength = HEADER_SIZE + payloadLength;
    char *buffer = malloc(bufferLength);
    memset(buffer, 0, ceil((double)bufferLength/4)*4);
    struct mipPacket *headers = (struct mipPacket*)buffer;
    
    headers->T = 0;
    headers->R = 0;
    headers->A = 1;
    headers->TTL = 0xF;
    headers->PayloadLength = ceil((double)payloadLength/4);
    headers->DestinationMipAddress = 'B';
    headers->SourceMipAddress = 'A';
    memcpy(buffer + 4, payload, payloadLength);

    printMipPacket(buffer);

    return 0;
}
