#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vm.h"


struct ram *new_ram()
{
	struct ram *ram;
	ram = (struct ram*)malloc(sizeof(struct ram));
	if(ram == NULL) {
		fprintf(stderr, "Can't alloc memory for ram.\n");
		return NULL;
	}

	memset(ram->m, '\0', MAX_RAM);
	
	return ram;
}


void load_code(struct ram *ram, const char *filename)
{
	FILE *fp;
	size_t n;
	size_t total = 0;
	char buff[MAX_RAM];

	fp = fopen(filename, "rb");
	if(fp == NULL) {
		fprintf(stderr, "Can't open file %s\n", filename);
	}

	while((n = fread(buff, 1, MAX_RAM, fp))) {
		total += n;
		if(total >= MAX_RAM) {
			fprintf(stderr, "file toot big to read whole file\n");
			break;
		}
		memcpy(ram->m + MAX_STACK, buff, n);
	}

	fclose(fp);
}


int get_ins(struct ram *ram, int pos, struct ins *ins)
{

	if((pos + 2) > MAX_RAM) {
		fprintf(stderr, "memory overflow\n");
		return 1;
	}

	ins->ins = ram->m[pos];
	ins->arg1 = ram->m[pos + 1];
	ins->arg2 = ram->m[pos + 2];
	
	return 0;
}


int ram_load(struct ram *ram, char addr, char *value)
{
	*value = ram->m[(int)addr];
	return 0;
}


int ram_store(struct ram *ram, char addr, char value)
{
	ram->m[(int)addr] = value;
	return 0;
}


void free_ram(struct ram *ram)
{
	free(ram->m);
	free(ram);
}
