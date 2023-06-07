#ifndef PROJECT_INCLUDE_LOGIC_H_
#define PROJECT_INCLUDE_LOGIC_H_
#include "utils.h"
#define INVALID_STATUS_CODE -1
#define OPEN_FILE_ERROR "--CAN'T OPEN FILE--"
#define CASE_ERROR "--THIS CASE DOESN'T EXIST--"
#define BEGIN 0
#define END 4
#define TRANS_DAT "transaction.dat.gold"
#define REC_DAT "record.dat.gold"
#define BLACK_DAT "blackrecord.dat.gold"
enum actions {
    MASTER_WRITE_CASE = 1,
    TRANSACTION_WRITE_CASE,
    BLACK_RECORD_CASE
};
int get_case_choice(void);
void print_to_file_case(const char *name_of_file, void(*manager_to_execute)(FILE*, Data));
void print_update_black_case(const char *rec_file_name,
                             const char *trans_file_name,
                             const char *black_file_name,
                             void (*manager_to_execute)(FILE*, FILE*, FILE*, Data, Data));
void run_case_manager(void);
#endif  // PROJECT_INCLUDE_LOGIC_H_
