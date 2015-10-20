#include "q_defs.h"

char **column_n;
char *column_t;
int columnNum;

char *trimMsg(char* msg, int len) {
	char* str = (char*)malloc(sizeof(char) * (len + 1));
	int newLen = 0;
	for(int i = 0; i < len; i++) {
		if(*(msg + i) != ' ') {
			*(str+newLen) = *(msg+i);
			newLen++;
		}
	}
	*(str+newLen) = '\0';
	return str;
}

info *fixMessage(char *message, int len, char **column_names, char *column_type, int num_columns) {
	info *d = (info*)malloc(sizeof(info));
	char *msg;
	msg = trimMsg(message, len);
	d->conditional = (char*)malloc(sizeof(char) * 3);
	for(int i = 0; i < len; i++) {
		if(*(msg+i) == '=' || *(msg+i) == '<' || *(msg+i) == '>') {
			d->colName = (char*)malloc(sizeof(char) * (i+1));
			d->value = (data*)malloc(sizeof(data));
			for(int j = 0; j < i; j++)
				d->colName[j] = *(msg+j);
			d->colName[i] = '\0';
			for(int j = 0; j < num_columns; j++) {
				if(strcmp(d->colName,column_names[j]) == 0) {
					d->valueType = *(column_type+j);
					if(d->valueType == 'S')
						d->value->str = (char*) malloc(sizeof(char) * (len-i));
					break;
				}
			}
			if(*(msg+i) == '=') {
				strcpy(d->conditional, "=");
				if(d->valueType == 'S')
					strcpy(d->value->str, msg+i+1);
				else
					d->value->db = atof(msg+i+1);
				free(msg);
				break;
			}
			else if(*(msg+i) == '<') {
				if(*(msg+i+1) == '=') {
					strcpy(d->conditional, "<=");
					if(d->valueType == 'S')
						strcpy(d->value->str,msg+i+2);
					else
						d->value->db = atof(msg+i+2);
				}
				else {
					strcpy(d->conditional, "<");
					if(d->valueType == 'S')
						strcpy(d->value->str, msg+i+1);
					else
						d->value->db = atof(msg+i+1);
				}
				free(msg);
				break;
			}
			else if(*(msg+i) == '>') {
				if(*(msg+i+1) == '=') {
					strcpy(d->conditional, ">=");
					if(d->valueType == 'S')
						strcpy(d->value->str,msg+i+2);
					else {
						d->value->db = atof(msg+i+2);
					}
				}
				else {
					strcpy(d->conditional, ">");
					if(d->valueType == 'S')
						strcpy(d->value->str, msg+i+1);
					else
						d->value->db = atof(msg+i+1);
				}
				free(msg);
				break;
			}
		}
	}
	return d;
}

Tree *insertTree(char *query_text, int startIndex, int endIndex,int count, char **column_names, char *column_type, int num_columns) {
	if(startIndex > endIndex)
		return NULL;
	Tree *t = t_make();
	int temp = 0;
	int index = 0;
	for(int i = startIndex; i <= endIndex; i++) {
		if(*(query_text + i) == '|' || *(query_text + i) == '&')
			temp++;
		if(temp == 2 * (count/2) + 1) {
			index = i;
			break;
		}
	}	
	if(*(query_text + index) == '&') {
		t->data = (char*) malloc (sizeof(char) * 4);
		strcpy(t->data,"AND");
		*((char*)(t->data) + 3) = '\0';
	}
	else if(*(query_text + index) == '|') {
		t->data = (char*) malloc (sizeof(char) * 3);
		strcpy(t->data,"OR");
		*((char*)(t->data) + 2) = '\0';
	}
	else {
		t->data = fixMessage(query_text + startIndex, endIndex - startIndex, column_names, column_type, num_columns);
		t->left = NULL;
		t->right = NULL;
		return t;
	}
	t->left = insertTree(query_text,startIndex, index - 1, count / 2, column_names, column_type, num_columns);
	t->right = insertTree(query_text, index + 2, endIndex, (count-1) / 2, column_names, column_type, num_columns);
	return t;
}


Tree *q_parse(char *query_text, char **column_names, char *column_type, int num_columns) {
	if(strstr(query_text,"=") == NULL && strstr(query_text,">") == NULL && strstr(query_text,"<") == NULL)
		return NULL;
	if(strstr(query_text, "==") != NULL)
		return NULL;
	if(strstr(query_text, "=<") != NULL)
		return NULL;
	if(strstr(query_text, "=>") != NULL)
		return NULL;
	if(strstr(query_text, "<<") != NULL)
		return NULL;
	if(strstr(query_text, ">>") != NULL)
		return NULL;
	if(strstr(query_text, "< ") != NULL)
		return NULL;
	if(strstr(query_text, " <") != NULL)
		return NULL;
	if(strstr(query_text, "> ") != NULL)
		return NULL;
	if(strstr(query_text, " >") != NULL)
		return NULL;
	if(strstr(query_text, "<>") != NULL)
		return NULL;
	if(strstr(query_text, "><") != NULL)
		return NULL;
	if(strstr(query_text, "= ") != NULL)
		return NULL;
	if(strstr(query_text, " =") != NULL)
		return NULL;
	for(int i = 0; i < strlen(query_text); i++) {
		if(*(query_text+i) == '>' || *(query_text+i) == '<' || *(query_text+i) == '=') {
			if(i == 0 || i == strlen(query_text) - 1)
				return NULL;
			if(*(query_text+i-1) == '=' || *(query_text+i-1) == ' ')
				return NULL;
			if(*(query_text+i+1) == ' ' || *(query_text+i+1) == '>' || *(query_text+i+1) == '<')
				return NULL;
		}
		if(*(query_text+i) == '|') {
			if(i == 0 || i == strlen(query_text) - 1)
				return NULL;
			if((*(query_text+i+1) != '|' && *(query_text+i-1) != '|') || (*(query_text+i+1) == '|' && *(query_text+i-1) == '|'))
				return NULL;
		}
		if(*(query_text+i) == '&') {
			if(i == 0 || i == strlen(query_text) - 1)
				return NULL;
			if((*(query_text+i+1) != '&' && *(query_text+i-1) != '&') || (*(query_text+i+1) == '&' && *(query_text+i-1) == '&'))
				return NULL;
		}
	}
	for(int i = 0; i < strlen(query_text); i++) {
		if(*(query_text+i) == '>' || *(query_text+i) == '<' || *(query_text+i) == '=')
			break;
		if(i == strlen(query_text))
			return NULL;
	}
	int l = 0;
	char *tempComp = (char*) malloc(sizeof(char)*strlen(query_text));
	for(int i = 0; i < strlen(query_text); i++) {
		if(*(query_text+i) != ' ') {
			*(tempComp+l) = *(query_text+i);
			l++;
		}
	}
	if(*tempComp == '|' || *tempComp == '=' || *tempComp == '>' || *tempComp == '<' || *tempComp == '&')
		return NULL;
	if(*(tempComp+l-1) == '|' || *(tempComp+l-1) == '=' || *(tempComp+l-1) == '>' || *(tempComp+l-1) == '<' || *(tempComp+l-1) == '&')
		return NULL;
	free(tempComp);
	int count = 0;
	for(int i = 0; i < strlen(query_text); i++) {
		if(*(query_text+i) == '&') {
			if(*(query_text+i+1) == '&')
				count++;
		}
		else if(*(query_text+i) == '|') {
			if(*(query_text+i+1) == '|')
				count++;
		}
	}
	column_n = column_names;
	column_t = column_type;
	columnNum = num_columns;
	return insertTree(query_text, 0, strlen(query_text), count, column_names, column_type, num_columns);
}


void q_printHelper(Tree* t, int space) {
	if(t == NULL)
		return;
	for(int i = 0; i < space; i++)
		putchar(' ');
	if(t->left == NULL && t->right == NULL) {
		info* temp = (info*)(t->data);
		printf("%s%s",temp->colName,temp->conditional);
		if(temp->valueType == 'S')
			printf("%s\n", temp->value->str);
		else
			printf("%.2f\n", temp->value->db);
	}
	else
		printf("%s\n", (char*)t->data);
	q_printHelper(t->left,space + 1);
	q_printHelper(t->right,space + 1);
}

int q_get_type(void *query_data) {
	if(strcmp((char*)query_data,"OR") == 0)
		return 0;
	else if(strcmp((char*)query_data,"AND") == 0)
		return 1;
	else {
		info* temp = (info*)query_data;
		if(strcmp(temp->conditional, "=") == 0)
			return 2;
		else if(strcmp(temp->conditional, "<") == 0)
			return 3;
		else if(strcmp(temp->conditional, ">") == 0)
			return 4;
		else if(strcmp(temp->conditional, "<=") == 0)
			return 5;
		else if(strcmp(temp->conditional, ">=") == 0)
			return 6;
	}
}

int q_get_col_index(void *query_data){ //tre->data   data include column value type   
	info* temp = (info*)query_data;
	for(int i = 0; i < columnNum; i++) {	
		if(strcmp(temp->colName, column_n[i]) == 0) {
			if(temp->valueType == column_t[i]) {
				free(temp);
				return i;
			}
		}
	}
	free(temp);
	return -1;
}

void q_free(Tree *query) {
	if(query == NULL)
		return;
	if(strcmp((char*)query->data,"AND") == 0 || strcmp((char*)query->data,"OR") == 0) {
		free(query->data);
		q_free(query->left);
		q_free(query->right);
		free(query);
	}
	else {
		info *temp = (info*)(query->data);
		free(temp->colName);
		free(temp->conditional);
		if(temp->valueType == 'S')
			free(temp->value->str);
		free(temp->value);
		free(query->data);
		free(query);
	}
}

double q_get_double(void *query_data) {
	info* temp = (info*)query_data;
	double d = temp->value->db;
	free(temp);
	return d;
}

char *q_get_str(void *query_data) {
	info* temp = (info*)query_data;
	char* s = temp->value->str;
	free(temp);
	return s;
}

void q_print(Tree *t) {
	q_printHelper(t,0);
}
/*
int main() {
	char** columnName = (char**) malloc (sizeof(char)*30);
	columnName[0] = "ZIP";
	columnName[1] = "AMOUNT";
	columnName[2] = "OCCUPATION";
	char columnType[4]="DDS";
	char querytext[] = "ZIA";
	Tree* t = q_parse(querytext, columnName, columnType, 3);
	q_print(t);
	q_free(t);
	free(columnName);
}*/
