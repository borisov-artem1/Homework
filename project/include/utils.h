#ifndef PROJECT_INCLUDE_UTILS_H_
#define PROJECT_INCLUDE_UTILS_H_
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#define TRANS_DAT "transaction.dat"
#define REC_DAT "record.dat"
#define BLACK_DAT "blackrecord.dat"
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

typedef struct Some_data {
    int test_number;
    char test_name[20];
    double test_cash_payments;
} some_data;


void masterWrite(FILE *ofPTR, Data Client);
void transactionWrite(FILE *ofPtr, Data transfer);
void blackRecord(FILE *ofPTR, FILE *ofPTR_2, FILE *blackrecord, Data client_data, Data transfer);
void test_rw();
void write_to_file(const char *filename, some_data *expected_data);
void read_from_file(const char *filename, some_data *data);
#endif  // PROJECT_INCLUDE_UTILS_H_
