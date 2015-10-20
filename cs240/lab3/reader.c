#include"reader.h"
#include"defs_itf.h"
FILE * fp;

void rd_open(char *fn) {
	fp = fopen(fn, "r");
}

int rd_getchar() {
	return fgetc(fp);
}

char *rd_parse_string(char buf[], int from, int to) {
	int stringStart;
	int stringEnd;
	for(int i = from; i < to; i++) {
		if(buf[i] != ' ') {
			stringStart = i;
			break;
		}
	}
	for(int j = to - 1; j >= from; j--) {
		if(buf[j] != ' ') {
			stringEnd = j;
			break;
		}
	}
	char * string = (char *) calloc(stringEnd - stringStart + 2, sizeof(char));
	for(int i = stringStart; i <= stringEnd; i++) {
		string[i-stringStart] = buf[i];
	}
	string[stringEnd - stringStart + 1] = '\0';
	for(int i = 1; i < stringEnd - stringStart; i++) {
		if(string[i] == '"')
			return NULL;
	}
	
	if(string[0] == '"' && string[stringEnd - stringStart] == '"') {
		string[stringEnd - stringStart] = '\0';
		return string+1;
//		char str[stringEnd - stringStart];
//		for(int i = 0; i < stringEnd - stringStart - 1; i++)
//			str[i] = string[i+1];
//		str[stringEnd - stringStart - 1] = '\0';
//		return str;
	}
	else if(string[0] != '"' && string[stringEnd - stringStart] != '"') {
		return string;
	}
	else
		return NULL;

/*
	int quoteStart = -1;
	int quoteEnd = -1;
	int stringStart = -1;
	int stringEnd = -1;
	int wordInvalid = 1;
	for(int i = from; i < to; i++) {
		if((buf[i] >= 'a' && buf[i] <= 'z') || (buf[i] >= 'A' && buf[i] <= 'Z')) {
			wordInvalid = 0;
		}
		if(buf[i] == '"')
			if(quoteStart == -1) {
				quoteStart = i;
			}
			else {
				quoteEnd = i;
				break;
			}
	}
	if(wordInvalid || (quoteEnd == -1 && quoteStart != -1) || (quoteStart == quoteEnd && quoteStart != -1)) {
		return NULL;
	}
	if(quoteStart == -1) {
		for(int i = from; i < to; i++) {
			if((buf[i] >= 'a' && buf[i] <= 'z') || (buf[i] >= 'A' && buf[i] <= 'Z')) {
				stringStart = i;
				for(int j = i; j < to; j++) {
					if((buf[j] >= 'a' && buf[j] <= 'z') || (buf[j] >= 'A' && buf[j] <= 'Z')) {
						stringEnd = j;
					}
				}
				break;
			}
		}
		char string[140];//[stringEnd - stringStart + 2];
		int stringlen = 0;
		for(int i = stringStart; i <= stringEnd; i++) {
	//		string[i-stringStart] = buf[i];		
			string[stringlen] = buf[i];
			stringlen++;
		}
//		string[stringEnd - stringStart + 1] = '\0';
		string[stringlen] = '\0';
		return string;
	}
	else {
		for(int i = from; i < to; i++) {
			if(buf[i] != ' ') {
				if(buf[i] != '"') {
					return NULL;
				}
				break;
			}
		}
		for(int i = to-1; i >= from; i--) {
			if(buf[i] != ' ') {
				if(buf[i] != '"') {
					return NULL;
				}
				break;
			}
		} 
		char string[140]; //[quoteEnd - quoteStart];
		int stringlen = 0;
		for(int i = quoteStart + 1; i <= quoteEnd - 1; i++) {
//			string[i-quoteStart-1] = buf[i];
			string[stringlen] = buf[i];
			stringlen++;
		}
//		string[quoteEnd -quoteStart - 1] = '\0';
		string[stringlen] = '\0';
		return string;
	} */
}

double rd_parse_number(char buf[], int from, int to, int *err) {
	char doubleNum[to-from];
	int charInvalid = 0;
	double sign = 1.0;
	int isNull = 1;
	int length = 0;
	int signNum = 0;
	int dotNum = 0;
	for(int i = from; i < to; i++) {
		if(buf[i] >= '0' && buf[i] <= '9')
			isNull = 0;
		if(buf[i] == '-' || buf[i] == '+')
			signNum++;
		if(buf[i] == '.')
			dotNum++;
		if((buf[i] > '9' || buf[i] < '0') && buf[i] != '-' && buf[i] != '+' && buf[i] != '.' && buf[i] != ' ') {
			*err = 1;
			return 0.0;
		}
	}
	if(dotNum > 1 || signNum > 1 || isNull) {
		*err = 1;
		return 0.0;
	}
	if(dotNum == 1) {
		for(int i = from; i < to; i++) {
			if(buf[i] == '.') {
				if(buf[i-1] > '9' || buf[i-1] <'0' || buf[i+1] > '9' || buf[i+1] < '0') {
					*err = 1;
					return 0.0;
				}
			}
		}
	}

	if(signNum == 1) {
		for(int i = from; i < to; i++) {
			if(buf[i] == '+' || buf[i] == '-') {
				if(buf[i+1] > '9' || buf[i+1] < '0' || (buf[i-1] <= '9' && buf[i-1] >= '0')) {
					*err = 1;
					return 0.0;
				}
				if(buf[i] == '-')
					sign = -1.0;
			}
		}
	}
	for(int i = from; i < to; i++) {
		if(buf[i] <= '9' && buf[i] >= '0') {
			if(i != from && (buf[i-1] != ' ' && buf[i-1] != '+' && buf[i-1] != '-' && buf[i-1]!= '.')) {
				*err = 1;
				return 0.0;
			}
			for(int j = i; j < to; j++) {
				if((buf[j] > '9' || buf[j] < '0') && buf[j] != '.') {
					if(buf[j+1] >= '0' && buf[j+1] <= '9') {
						charInvalid = 1;
						break;
					}
				}
			}
			break;
		}
	}
	if(charInvalid) {
		*err = 1;
		return 0.0;
	}
	for (int j = from; j < to; j++) {
		if(buf[j] <= '9' && buf[j] >= '0') {
			doubleNum[length] = buf[j];
			length++;
		}
		if(buf[j] == '.') {
			if(j != from)
				if(buf[j - 1] >= '0' && buf[j - 1] <= '9') {
					doubleNum[length] = buf[j];
					length++;
				}
		}
	}
	doubleNum[length] = '\0';
	*err = 0;
	return atof(doubleNum) * sign;
}

int rd_num_fields(char buf[], int end ) {
	int quoteNum = 0;
	int commaNum = 0;
	for(int i = 0; i < end; i++) {
		if(buf[i] == '"')
			quoteNum++;
		if(buf[i] == ',') {
			if(quoteNum % 2 == 0)
				commaNum++;
		}
	}
	if(quoteNum % 2 !=0)
		return -1;
	else
		return commaNum;
}

int rd_field_length(char buf[], int cur, int end) {
	int quoteNum = 0;
	for(int i = cur; i <= end; i++) {
		if(buf[i] == '"')
			quoteNum++;
		if(buf[i] == ',') {
			if(quoteNum % 2 == 0)
				return i;
		}
		if(buf[i] = '\0' || i == end) {
			if(quoteNum % 2 ==0)
				return i;
		}
	}
	return -1;
}
