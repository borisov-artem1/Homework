#include "read_write_data.h"

static char* client_data_fields[8] = {
        "Number account: ",
        "Client name: ",
        "Surname: ",
        "Addres client: ",
        "Client Telnum: ",
        "Client indebtedness: ",
        "Client credit limit: ",
        "Client cash payments: "
};
void printing_data_fields(char* data_fields[], int amount_of_client_fields) {
    for (int i = 0; i < amount_of_client_fields; i++) {
        printf("%d %s\n", i + 1, data_fields[i]);
    }
}
void manager_rec_dat(FILE *record_file, Data Client) {
    printing_data_fields(client_data_fields, 8);
    fseek(record_file, 0, SEEK_END);
    while (scan_rec_data(&Client) == 8 || scan_rec_data(&Client) != EOF) {
        int ch;
        if ((ch = getchar()) != '\n' && ch != EOF) {
            scanf("%*[^\n]");
            break;
        }
        write_rec_data(record_file, Client);
        printing_data_fields(client_data_fields, 8);
    }
}
void manager_trans_dat(FILE *trans_file, Data transfer) {
    char *trans_data_fields[2] = {client_data_fields[0], client_data_fields[7]};
    fseek(trans_file, 0, SEEK_END);
    printing_data_fields(trans_data_fields, 2);
    while (scan_trans_data(&transfer) == 2 || scan_trans_data(&transfer) != EOF) {
        int ch;
        if ((ch = getchar()) != '\n' && ch != EOF) {
            scanf("%*[^\n]");
            break;
        }
        write_trans_data(trans_file, transfer);
        printing_data_fields(trans_data_fields, 2);
    }
}
void manager_black_dat(FILE *rec_file,
                       FILE *trans_file,
                       FILE *black_file,
                       Data rec_struct,
                       Data trans_struct) {
    fseek(black_file, 0, SEEK_END);
    while (fscan_rec_file(rec_file, &rec_struct) == 8 || fscan_rec_file(rec_file, &rec_struct) != EOF) {
        while (fscan_trans_file(trans_file, &trans_struct) == 2 || fscan_trans_file(trans_file, &trans_struct) != EOF) {
            summing_data_fields(&rec_struct, &trans_struct);
        }
        write_rec_data(black_file, rec_struct);
        rewind(trans_file);
    }
}
void summing_data_fields(Data *rec_struct, Data *trans_struct) {
    if (rec_struct->Number == trans_struct->Number && trans_struct->cash_payments != 0) {
        rec_struct->credit_limit += trans_struct->cash_payments;
    }
}
