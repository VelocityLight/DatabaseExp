#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <string.h>
#include <math.h>
#include "extmem.h"
#include "constant.h"
using namespace std;

Buffer buf;
unsigned char * blk[8];

void cpy(unsigned char * blk, int x){
	unsigned int mask = 0x000000FF;
	int i;
	int tmp;
	for (i = 0; i < 4; i++){
		tmp = x & mask;
		//printf("%x",tmp);
		tmp = tmp >> (i * 8);
		*(blk + i) = (char)(tmp % 255);
		mask = mask << 8;
	}

}
int convert(unsigned char *blk){
	int x = 0;
	int i;
	unsigned char tmp;
	for (i = 0; i < 4; i++){
		tmp = *(blk + i);
		x += tmp << (i * 8);
	}
	return x;
}


int cmp(const void *a, const void * b)
{
	return convert((unsigned char*)a) > convert((unsigned char*)b);
}
int initrun()
{
	int i, j, k;
	for (i = ADDR_START_R; i < ADDR_START_R + 16; i += 8)
	{
		for (j = 0; j < 8; j++)
		{
			if ((blk[j] = readBlockFromDisk(j + i, &buf)) == NULL)
			{
				perror("Reading Block Failed!\n");
				return -1;
			}
			qsort(blk[j], 7, sizeof(int) * 2, cmp);
			/*for (k = 0; k < 64; k+=8)
			printf("%d,%d ", convert(blk[j] + k),convert(blk[j]+k+4));
			printf("\n");*/
			writeBlockToDisk(blk[j], j + i, &buf);
		}
	}
	return 0;
}


int blksort(int tempbptr,int up){
	int read[7]; //每块已取的字节
	int availablewrite = 7;
	int tempptr = 0;
	blk[7] = getNewBlockInBuffer(&buf);
	memset(read, 0, sizeof(int) * 7);
	availablewrite = up;
	while (availablewrite){
		int min = 2000, minindex = -1;
		for (int i = 0; i < up; i++){
			if (read[i] < 56 && convert(blk[i] + read[i]) < min){
				min = convert(blk[i] + read[i]);
				minindex = i;
			}
		}
		cpy(blk[7] + tempptr, convert(blk[minindex] + read[minindex]));
		cpy(blk[7] + tempptr + 4, convert(blk[minindex] + read[minindex] + 4));
		read[minindex] += 8;
		tempptr += 8;
		if (tempptr == 56){
			cpy(blk[7] + tempptr, 0);
			cpy(blk[7] + tempptr + 4, tempbptr + 1);
			writeBlockToDisk(blk[7], tempbptr, &buf);
			tempbptr++;
			blk[7] = getNewBlockInBuffer(&buf);
			tempptr = 0;
			availablewrite--;
		}
	}
	freeBlockInBuffer(blk[7], &buf);
	return tempbptr;
}

int mergesort()
{

	int tempptr = 0,tempbptr = ADDR_START_TEMP;
	vector<int> index; //归并段头块位置
	vector<int> length; //归并段长度
	int largest = 1; //最大归并段
	int num2merge = 16; //待归并段数
	initrun();  //初始块内排序
	int resultaddr; //排序好的首块地址


	while (largest < 16){
		while (num2merge){
			for (int i = ADDR_START_R; i < ADDR_START_R + 16; i += 7){
				int up = 0;
				if (buf.numFreeBlk == 0){
					perror("No Free Block!\n");
					return -1;
				}
				if (i + 7 > ADDR_START_R + 15)
					up = ADDR_START_R + 16 - i;
				else
					up = 7;
				for (int j = 0; j < up; j++){
					if ((blk[j] = readBlockFromDisk(j + i, &buf)) == NULL){
						perror("Reading Block Failed!\n");
						return -1;
					}
				}
				index.push_back(tempbptr);
				length.push_back(up);
				tempbptr = blksort(tempbptr,up);
				for (int j = 0; j < up; j++){
					freeBlockInBuffer(blk[j], &buf);
				}
				largest = largest > up ? largest : up;
				num2merge -= up;
			}
		}
		if (index.size() < 7){   //最后一次归并
			blk[7] = getNewBlockInBuffer(&buf);
			tempptr = 0;
			largest = 0;
			vector<int> read;   //每块已取的字节
			for (int i = 0; i < index.size(); i++){
				if ((blk[i] = readBlockFromDisk(index[i], &buf)) == NULL){
					perror("Reading Block Failed!\n");
					return -1;
				}
				dropBlockOnDisk(index[i]);
				length[i] --;
				read.push_back(0);
			}
			resultaddr = tempbptr;
			while (1){
				int min = 2000,minindex = -1;
				for (int i = 0; i < index.size(); i++){
					if (read[i] < 56 && length[i] > -1 && convert(blk[i] + read[i]) < min){
						min = convert(blk[i] + read[i]);
						minindex = i;
					}
					//printf("%d,%d,%d\n",read[i],length[i],convert(blk[i]+read[i]));
				}
				cpy(blk[7] + tempptr, convert(blk[minindex] + read[minindex]));
				cpy(blk[7] + tempptr + 4, convert(blk[minindex] + read[minindex] + 4));
				tempptr += 8;
				read[minindex] += 8;
				if (read[minindex] == 56){
				    if(length[minindex]){
                        int nextblk = convert(blk[minindex] + read[minindex] + 4);
                        freeBlockInBuffer(blk[minindex], &buf);
                        index[minindex] = nextblk;
                        if ((blk[minindex] = readBlockFromDisk(index[minindex], &buf)) == NULL){
                            perror("Reading Block Failed!\n");
                            return -1;
                        }
                        dropBlockOnDisk(index[minindex]);
                        read[minindex] = 0;
				    }else{
                        freeBlockInBuffer(blk[minindex], &buf);
				    }
					length[minindex] --;
				}
				if (tempptr == 56){
					cpy(blk[7] + tempptr, 0);
					cpy(blk[7] + tempptr + 4, tempbptr + 1);
					writeBlockToDisk(blk[7], tempbptr, &buf);
					tempbptr++;
					blk[7] = getNewBlockInBuffer(&buf);
					tempptr = 0;
					largest++;
					if (largest == 16){
                        freeBlockInBuffer(blk[7], &buf);
						break;
					}
				}
			}
		}

	}
	return resultaddr;
}

int select()
{
	int i, j, k;
	int a, b;
	int up = -7;
	int ptr = 0, bptr = ADDR_START_RESULT;
	blk[7] = getNewBlockInBuffer(&buf); //result
	for (i = ADDR_START_R; i < ADDR_START_S + 32; i += 7)
	{
		if (buf.numFreeBlk == 0)
		{
			perror("No Free Block!\n");
			return -1;
		}
		if (i + 7 > ADDR_START_S + 31)
		{
			up = ADDR_START_S + 32 - i;
		}
		else
			up = 7;
		for (j = 0; j < up; j++)
		{
			if ((blk[j] = readBlockFromDisk(i + j, &buf)) == NULL)
			{
				perror("Reading Block Failed!\n");
				return -1;
			}
		}


		for (j = 0; j < up; j++)
		{
			for (k = 0; k < 56; k += 8)
			{
				a = convert(blk[j] + k);
				b = convert(blk[j] + k + 4);
				if (a == 40 && i < ADDR_START_R + 16 || a == 60 && i >= ADDR_START_S)
				{
					cpy(blk[7] + ptr, a);
					cpy(blk[7] + ptr + 4, b);
					printf("%d,%d\n", a, b);
					ptr += 8;
					if (ptr == 56)
					{
						cpy(blk[7] + ptr, 0);
						cpy(blk[7] + ptr + 4, bptr + 1);
						writeBlockToDisk(blk[7], bptr, &buf);
						bptr++;
						blk[7] = getNewBlockInBuffer(&buf);
						ptr = 0;
					}
				}
			}
			freeBlockInBuffer(blk[j], &buf);
		}

	}
	if (ptr < 64)
	{
		for (; ptr <64; ptr += 8)
		{
			cpy(blk[7] + ptr, 0);
			cpy(blk[7] + ptr + 4, 0);
		}
		writeBlockToDisk(blk[7], bptr, &buf);
	}
	return 0;
}

int projection()
{
	int i, j, k;
	int a;
	int ptr = 0, bptr = ADDR_START_RESULT;
	int up = -7;
	int sorted = mergesort();
	int pre = 0;
	blk[7] = getNewBlockInBuffer(&buf); //result
	for (i = sorted; i < sorted + 16; i += 7){
		if (buf.numFreeBlk == 0){
			perror("No Free Block!\n");
			return -1;
		}
		if (i + 7 > sorted + 15){
			up = sorted + 16 - i;
		}
		else
			up = 7;
		for (j = 0; j < up; j++){
			if ((blk[j] = readBlockFromDisk(i + j, &buf)) == NULL){
				perror("Reading Block Failed!\n");
				return -1;
			}
		}

		for (j = 0; j < up; j++){
			for (k = 0; k < 56; k += 8){
				a = convert(blk[j] + k);
				//b = convert(blk[j]+k+4);
				if(pre != a){
                    cpy(blk[7] + ptr, a);
                    ptr += 4;
                    printf("%d ", a);
                    pre = a;
				}

				if (ptr == 56){
					cpy(blk[7] + ptr, 0);
					cpy(blk[7] + ptr + 4, bptr + 1);
					writeBlockToDisk(blk[7], bptr, &buf);
					bptr++;
					blk[7] = getNewBlockInBuffer(&buf);
					ptr = 0;
				}

			}
			freeBlockInBuffer(blk[j], &buf);
		}
	}
	if (ptr < 64){
		for (; ptr <64; ptr += 4){
			cpy(blk[7] + ptr, 0);
		}
		writeBlockToDisk(blk[7], bptr, &buf);
	}
	return 0;
}

int NLJ()
{
	int i, j, k, l, o, p;
	int a, b, c, d;
	int ptr = 0, bptr = ADDR_START_RESULT;
	int up1, up2;
	blk[7] = getNewBlockInBuffer(&buf); //result

	for (i = ADDR_START_R; i < ADDR_START_R + 16; i += 4)
	{
		if (buf.numFreeBlk == 0)
		{
			perror("No Free Block!\n");
			return -1;
		}
		if (i + 4 > ADDR_START_R + 15)
		{
			up1 = ADDR_START_R + 16 - i;
		}
		else
			up1 = 4;
		for (k = 0; k < up1; k++)
		{
			if ((blk[k] = readBlockFromDisk(i + k, &buf)) == NULL)
			{
				perror("Reading Block Failed!\n");
				return -1;
			}
		}
		for (j = ADDR_START_S; j < ADDR_START_S + 32; j += 3)
		{
			if (j + 3 > ADDR_START_S + 31)
			{
				up2 = ADDR_START_S + 32 - j;
			}
			else
				up2 = 3;
			for (k = 4; k < up2 + 4; k++)
			{
				if ((blk[k] = readBlockFromDisk(j + k - 4, &buf)) == NULL)
				{
					perror("Reading Block Failed!\n");
					return -1;
				}
			}
			for (k = 0; k < up1; k++)
			{
				for (l = 0; l < 56; l += 8)
				{
					a = convert(blk[k] + l);
					b = convert(blk[k] + l + 4);
					for (o = 4; o < 4 + up2; o++)
					{
						for (p = 0; p < 56; p += 8)
						{
							c = convert(blk[o] + p);
							d = convert(blk[o] + p + 4);
							if (a == c)
							{
								cpy(blk[7] + ptr, a);
								cpy(blk[7] + ptr + 4, b);
								cpy(blk[7] + ptr + 8, d);
								printf("%d,%d,%d\n", a, b, d);
								ptr += 12;
							}

							if (ptr == 60)
							{
								//cpy(blk[7]+ptr,0);
								cpy(blk[7]+ptr,bptr+1);
								writeBlockToDisk(blk[7], bptr, &buf);
								bptr++;
								blk[7] = getNewBlockInBuffer(&buf);
								ptr = 0;
							}
						}
						freeBlockInBuffer(blk[o], &buf);
					}
				}
			}
		}
		for (k = 0; k < up1; k++)
		{
			freeBlockInBuffer(blk[k], &buf);
		}
	}
	if (ptr < 64)
	{
		for (; ptr <64; ptr += 4)
		{
			cpy(blk[7] + ptr, 0);
		}
		writeBlockToDisk(blk[7], bptr, &buf);
	}
	return 0;
}





int main(int argc, char **argv)
{
    //createdata();
    if(!initBuffer(BUFFER_SIZE,BLOCK_SIZE,&buf))
    {
        perror("Buffer Initialization Failed!\n");
        return -1;
    }
    //select();
    //projection();
    NLJ();

    return 0;
}
