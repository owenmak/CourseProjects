char* sub_string(char *in_string, int start_index, int end_index) {
	char *out_string;
	out_string = (char*)malloc(sizeof(char) * (end_index - start_index + 2));
	for(int i = start_index; i <= end_index; i++) {
			out_string[i - start_index] = in_string[i];
	}
	out_string[end_index - start_index + 1] = '\0';
	return out_string;
}
