#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#ifndef PROJECT_INCLUDE_UTILS_H_
#define PROJECT_INCLUDE_UTILS_H_
#define TRANS_DATA "transaction.dat"
#define REC_DATA "record.dat"
#define BLACK_DATA "blackrecord.dat"
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
typedef struct data {
    int test_num;
    char test_name[20];
    double test_cash_payments;
} some_random_data;
void masterWrite(FILE *ofPTR, Data Client);
void transactionWrite(FILE *ofPtr, Data transfer);
void blackRecord(FILE *ofPTR, FILE *ofPTR_2, FILE *blackrecord, Data client_data, Data transfer);
#endif  // PROJECT_INCLUDE_UTILS_H_
