#include "dt.c"

void add_to_table(Table* t, char** column_name) {
	char buf[200];
	memset(&buf[0], '\0', sizeof(buf));
	int buf_i = 0, c = 0, count = 0;
	while ( (c = rd_getchar()) != EOF) {
		if (c == '\n') {
			if(count == 0) {
				int init_position = 0;
				int end_position = rd_field_length(buf, init_position, buf_i);
				while (init_position != buf_i && init_position != -1 && end_position != -1) {
					column_name[count++] = rd_parse_string(buf, init_position, end_position);
					init_position = end_position + 1;
					end_position = rd_field_length(buf, init_position, buf_i);
				}
				memset(&buf[0], '\0', sizeof(buf));
				buf_i = 0;
			}

			tbl_start_row(t, rd_num_fields(buf, buf_i + 1));
			int init_position = 0;
			int end_position = rd_field_length(buf, init_position, buf_i);
			while (init_position != buf_i && init_position != -1  && end_position != -1) {
				int i = 0;
				rd_parse_number(buf, init_position, end_position, &i);
				if (i == 1) {
					char* temp = rd_parse_string(buf, init_position, end_position);
					tbl_add_string_to_row(t, temp);
				} else {
					double temp = rd_parse_number(buf, init_position, end_position, &i);
					tbl_add_double_to_row(t, temp);
				}
				init_position = end_position + 1;
				end_position = rd_field_length(buf, init_position, buf_i);
			}
			memset(&buf[0], '\0', sizeof(buf));
			buf_i = 0;
		} else {
			buf[buf_i++] = c;
		}
	}
	tbl_done_building(t); 
	tbl_print(t);
}

int main(int argc, char** argv) {
	ca_init(argc, argv);
	Table* t = tbl_make();
	rd_open(ca_str_value("file"));
	colnames = malloc(10* sizeof(char*));
	add_to_table(t, colnames);
	Tree* tree = t_make();
	dt_build(t, tree);
	t_print( tree ,0, dt_print);
	t_free(tree, dt_free);
	tbl_free(t);
}
