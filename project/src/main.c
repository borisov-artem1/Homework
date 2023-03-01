#include "utils.h"
int main(void) {
    int choice = 0;
    FILE *Ptr = NULL;
    FILE *Ptr_2 = NULL;
    FILE *blackrecord = NULL;
    Data client_data;
    Data transfer;
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
            case 1:
                Ptr = fopen(REC_DAT, "r+");
                if (Ptr == NULL) {
                    puts("Not acess");
                } else {
                    masterWrite(Ptr, client_data);
                    fclose(Ptr);
                }
                break;
            case 2:
                Ptr = fopen(TRANS_DAT, "r+");
                if (Ptr == NULL) {
                    puts("Not acess");
                } else {
                    transactionWrite(Ptr, transfer);
                    fclose(Ptr);
                }
                break;
            case 3:
                Ptr = fopen(REC_DAT, "r");
                Ptr_2 = fopen(TRANS_DAT, "r");
                blackrecord = fopen(BLACK_DAT, "w");
                if (Ptr == NULL || Ptr_2 == NULL || blackrecord == NULL) {
                    puts("exit");
                } else {
                    blackRecord(Ptr, Ptr_2, blackrecord, client_data, transfer);
                    fclose(Ptr);
                    fclose(Ptr_2);
                    fclose(blackrecord);
                }
                break;
            default:
                puts("error");
        }
        printf("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
    }
    return 0;
}
