#include "logic.h"
#include "utils.h"

int get_case_choice(void) {
    printf("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
    int choice = 0;
    if (scanf("%d", &choice) != 1) {
        scanf("%*[^\n]");
        return INVALID_STATUS_CODE;
    }
    return choice;
}
void print_to_file_case(const char *name_of_file, void(*manager_to_execute)(FILE*, Data)) {
    Data client_info = {0};
    FILE *opened_file = fopen(name_of_file, "r+");
    if (opened_file == NULL) {
        opened_file = fopen(name_of_file, "w");
        puts("file created");
    }
    manager_to_execute(opened_file, client_info);
    fclose(opened_file);
}
void print_update_black_case(const char *rec_file_name,
                             const char *trans_file_name,
                             const char *black_file_name,
                             void (*manager_to_execute)(FILE*, FILE*, FILE*, Data, Data)) {
    FILE *opened_rec_file = fopen(rec_file_name, "r");
    if (opened_rec_file == NULL) {
        puts(OPEN_FILE_ERROR);
        return;
    }
    FILE *opened_trans_file = fopen(trans_file_name, "r");
    if (opened_trans_file == NULL) {
        puts(OPEN_FILE_ERROR);
        fclose(opened_rec_file);
        return;
    }
    FILE *opened_black_file = fopen(black_file_name, "w");
    if (opened_black_file == NULL) {
        puts(OPEN_FILE_ERROR);
        fclose(opened_rec_file);
        fclose(opened_trans_file);
        return;
    }
    Data rec_struct = {0};
    Data trans_struct = {0};
    manager_to_execute(opened_rec_file, opened_trans_file, opened_black_file, rec_struct, trans_struct);
    fclose(opened_rec_file);
    fclose(opened_trans_file);
    fclose(opened_black_file);
}
void run_case_manager(void) {
    int case_choice = get_case_choice();
    while (case_choice > BEGIN && case_choice < END) {
        switch (case_choice) {
            case MASTER_WRITE_CASE:
                print_to_file_case(REC_DAT, manager_rec_dat);
                break;
            case TRANSACTION_WRITE_CASE:
                print_to_file_case(TRANS_DAT, manager_trans_dat);
                break;
            case BLACK_RECORD_CASE:
                print_update_black_case(REC_DAT, TRANS_DAT, BLACK_DAT, manager_black_dat);
                break;
            default:
                puts(CASE_ERROR);
        }
        case_choice = get_case_choice();
    }
}
