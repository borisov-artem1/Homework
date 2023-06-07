#include "utils.h"
#ifndef HOMEWORK_READ_WRITE_DATA_H
#define HOMEWORK_READ_WRITE_DATA_H
#define FORMAT_STRING_REC_SCAN_PATTERN "%d%20s%20s%20s%20s%20lf%20lf%20lf"
#define FORMAT_STRING_REC_PRINT_PATTERN "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n"
#define FORMAT_STRING_TRANS_SCAN_PATTERN "%d %lf"
#define FORMAT_STRING_TRANS_PRINT_PATTERN "%-3d%-6.2f\n"

int fscan_rec_file (FILE *rec_file, Data *rec_struct);
int fscan_trans_file(FILE *trans_file, Data *trans_struct);
int scan_rec_data(Data *rec_struct);
void write_rec_data(FILE *file, Data rec_struct);
int scan_trans_data(Data *trans_struct);
void write_trans_data(FILE *trans_file, Data trans_struct);
#endif //HOMEWORK_READ_WRITE_DATA_H
