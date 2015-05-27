#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "extmem.h"
#include "constant.h"


int createdata(){
	Buffer buf;
	unsigned char *blk;
	int i = 0,j = 0;
	int a,b;
	srand((unsigned)time(NULL));
	if(!initBuffer(BUFFER_SIZE,BLOCK_SIZE,&buf)){
		perror("Buffer Initialization Failed!\n");
        return -1;
	}

	blk = getNewBlockInBuffer(&buf);

	for(i = ADDR_START_R; i < ADDR_START_R+16; i ++ ){
		for(j = 0; j < 56; j+=8){
			a = rand()%40 + 1;
			b = rand()%1000 + 1;
			cpy(blk+j,a);
			cpy(blk+j+4,b);
            //printf("%x,%x ", convert(blk + j),convert(blk+j+4));
            //printf("%d,%d ", convert(blk + j),convert(blk+j+4));
		}
		cpy(blk+j,0);
		cpy(blk+j+4,i+1);
        //printf("%x,%x ", convert(blk + j),convert(blk+j+4));
        //printf("%d,%d ", convert(blk + j),convert(blk+j+4));
		//printf("\n");
		if (writeBlockToDisk(blk, i, &buf) != 0){
        	perror("Writing Block Failed!\n");
        	return -1;
    	}
    	freeBlockInBuffer(blk,&buf);
    	if ((blk = readBlockFromDisk(i, &buf)) == NULL){
            perror("Reading Block Failed!\n");
            return -1;
        }
        for (j = 0; j < 64; j+=8)
            printf("%d,%d ", convert(blk + j),convert(blk+j+4));
        printf("\n");
        freeBlockInBuffer(blk,&buf);
	}

	for(i = ADDR_START_S; i < ADDR_START_S+32; i ++ ){
		for(j = 0; j < 56; j+=8){
			a = rand()%40 + 21;
			b = rand()%1000 + 1;
			cpy(blk+j,a);
			cpy(blk+j+4,b);
		}
		cpy(blk+j,0);
		cpy(blk+j+4,i+1);
		if (writeBlockToDisk(blk, i, &buf) != 0){
        	perror("Writing Block Failed!\n");
        	return -1;
    	}
    	freeBlockInBuffer(blk,&buf);
    	if ((blk = readBlockFromDisk(i, &buf)) == NULL){
            perror("Reading Block Failed!\n");
            return -1;
        }
        for (j = 0; j < 64; j+=8)
            printf("%d,%d ", convert(blk + j),convert(blk+j+4));
        printf("\n");
        freeBlockInBuffer(blk,&buf);
	}
    for(i = ADDR_START_R; i < ADDR_START_R+16;i++){
        if ((blk = readBlockFromDisk(i, &buf)) == NULL){
            perror("Reading Block Failed!\n");
            return -1;
        }
        printf("%d: ",i);
        for (j = 0; j < 64; j+=8)
            printf("%d,%d ", convert(blk + j),convert(blk+j+4));
        printf("\n");
        freeBlockInBuffer(blk,&buf);
    }

    for(i = ADDR_START_S; i < ADDR_START_S+32;i++){
        if ((blk = readBlockFromDisk(i, &buf)) == NULL){
            perror("Reading Block Failed!\n");
            return -1;
        }
        printf("%d: ",i);
        for (j = 0; j < 64; j+=8)
            printf("%d,%d ", convert(blk + j),convert(blk+j+4));
        printf("\n");
        freeBlockInBuffer(blk,&buf);
    }



	freeBuffer(&buf);
	return 0;

}
