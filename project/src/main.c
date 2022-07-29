#include "utils.h"
#include "test_case.h"
int main(void) {
    int choice = 0;
    FILE *Ptr = NULL;
    FILE *Ptr_2 = NULL;
    FILE *blackrecord = NULL;
    Data transfer;
    Data client_data;
    client_data.Number = 0;
    client_data.indebtedness = 0;
    client_data.credit_limit = 0;
    client_data.cash_payments = 0;
    transfer.Number = 0;
    transfer.indebtedness = 0;
    transfer.credit_limit = 0;
    transfer.cash_payments = 0;
    printf("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
    while (scanf("%d", &choice) != -1) {
        switch (choice) {
            case 1: {
                Ptr = fopen(REC_DATA, "r+");
                if (Ptr == NULL) {
                    puts("Not acess");
                } else {
                    masterWrite(Ptr, client_data);
                    fclose(Ptr);
                }
                break;
            }
            case 2: {
                Ptr = fopen(TRANS_DATA, "r+");
                if (Ptr == NULL) {
                    puts("Not acess");
                } else {
                    transactionWrite(Ptr, transfer);
                    fclose(Ptr);
                }
                break;
            }
            case 3: {
                Ptr = fopen(REC_DATA, "r");
                Ptr_2 = fopen(TRANS_DATA, "r");
                blackrecord = fopen(BLACK_DATA, "w");
                if (Ptr == NULL || Ptr_2 == NULL || blackrecord == NULL) {
                    puts("exit");
                } else {
                    blackRecord(Ptr, Ptr_2, blackrecord, client_data, transfer);
                    fclose(Ptr);
                    fclose(Ptr_2);
                    fclose(blackrecord);
                    // free(Ptr);
                }
                break;
            }
            case 4: {
                test_rw_case();
                break;
            }
            default: {
                puts("error");
                break;
            }
        }
        printf("%s", "please enter action\n1 enter data "
                     "client:\n2 enter data transaction:\n3 update base\n");
    }
    return 0;
}
