int hexdump(void *strt, void *stp) {
	unsigned int start = (unsigned int)strt;
	unsigned int  stop = (unsigned int)stp;
	if(start > stop) {
		unsigned temp = start;
		start = stop;
		stop = temp;
	}
	unsigned int strt_comp = 0xFFFFFFF0;
	unsigned int stp_comp = 0x0000000F;
	start = strt_comp & start;
	
	char *addr[16];

	stop = stp_comp | stop;
	printf("\nDumping from address 0x%0x to 0x%0x\n\n", strt, stp);
	printf("\tAdresses\t\tValues in memory\t\tPrintable\n");
	
	for(int i = 0; i < 16; i++) {
		addr[i] = start + i;
	}


	for(int i = 0; i < (stop - start + 1) / 16; i++) {
		printf("%#08x - %#08x\t", addr[0], addr[15]);
		for(int j = 0; j < 16; j++) {
			if(addr[j] < strt || addr[j] > stp)
				printf("..");
			else {
				//if (*addr[j] <= 0)
				//	printf("00");
				//else{
					printf("%02x", *addr[j] & 0x000000FF );
				//}
			}
			if((j + 1) % 4  == 0)
				printf(" ");
		}
		printf("\t");
		printf("*");

		for(int k = 0; k < 16; k++) {
			if(addr[k] < strt || addr[k] > stp)
				printf(" ");
			else {
				if(isprint(*addr[k]))
					printf("%c", *addr[k]);
				else
					printf(".");
			}
		}
		for(int j = 0; j < 16; j++) {
			addr[j] = addr[j] + 16;
		}
		printf("*");
		printf("\n");
	}
}
