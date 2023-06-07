#ifndef PROJECT_INCLUDE_UTILS_H_
#define PROJECT_INCLUDE_UTILS_H_
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
typedef struct masterRecord {
    int Number;
    char Name[20];
    char Surname[20];
    char addres[30];
    char TelNumber[15];
    double indebtedness;
    double credit_limit;
    double cash_payments;
} Data;

void printing_data_fields(char* data_fields[], int amount_of_client_fields);
void manager_rec_dat(FILE *record_file, Data Client);
void manager_trans_dat(FILE *trans_file, Data transfer);
void manager_black_dat(FILE *rec_file,
                       FILE *trans_file,
                       FILE *black_file,
                       Data rec_struct,
                       Data trans_struct);
void summing_data_fields(Data *rec_struct, Data *trans_struct);
#endif  // PROJECT_INCLUDE_UTILS_H_
