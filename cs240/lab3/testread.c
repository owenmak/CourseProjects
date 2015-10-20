#include "defs_itf.h"
#include "reader.c"

int main() {
	char input1[] = " ab\"s\"  ";
	char input2[] = " \"hello Yeah\" ";
	char input3[] = " \"ohmyO\"";
	if(rd_parse_string(input1, 0, strlen(input1)) == NULL)
		putchar('.');
	else
		putchar('E');
	if(rd_parse_string(input2, 0, strlen(input2)) != NULL) {
		if(strcmp(rd_parse_string(input2, 0, strlen(input2)), "hello Yeah") == 0)
			putchar('.');
		else
			putchar('E');
	}
	else
		putchar('E');
	if(rd_parse_string(input3, 0, strlen(input3)) != NULL) {
		if(strcmp(rd_parse_string(input3, 0, strlen(input3)), "ohmyO") == 0)
			putchar('.');
		else
			putchar('E');
	}
	else
		putchar('E');
	int err;
	char input4[] = " -1.233";
	char input5[] = " a.212";
	char input6[] = " 23232.0";
	rd_parse_number(input4,0,strlen(input4), &err);
	if(err == 0)
		putchar('.');
	else
		putchar('E');
	err = 0;
	rd_parse_number(input5, 0, strlen(input5), &err);
	if(err == 1)
		putchar('.');
	else
		putchar('E');
	err = 0;
	rd_parse_number(input6,0,strlen(input6), &err);
	if(err == 0)
	 	putchar('.');
	else
		putchar('E');
	char input7[] = "\",\",hahaha,";
	char input8[] = "\"yello,";
	if(rd_num_fields(input7,strlen(input7)) == 2)
		putchar('.');
	else
		putchar('E');
     if(rd_num_fields(input8,strlen(input8)) == -1)
         putchar('.');
     else
         putchar('E');
     if(rd_field_length(input7,0,strlen(input7)) == 3)
         putchar('.');
     else
         putchar('E');
     if(rd_field_length(input8,0,strlen(input8)) == -1)
         putchar('.');
     else
         putchar('E');

}
