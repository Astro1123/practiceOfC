#ifndef DATA_H
#define DATA_H

typedef struct {
	int i;
} Data;

Data make_data(int i);
Data make_null_data(void);
void print_data(Data data);
bool compare_data(Data data1, Data data2);

#endif /* DATA_H */