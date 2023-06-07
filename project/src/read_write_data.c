#include "read_write_data.h"
#include "utils.h"
int fscan_rec_file(FILE *rec_file, Data *rec_struct) {
    int amount_of_read_rec_fields = fscanf(rec_file,
                                           FORMAT_STRING_REC_SCAN_PATTERN,
                                           &rec_struct->Number,
                                           rec_struct->Name,
                                           rec_struct->Surname,
                                           rec_struct->addres,
                                           rec_struct->TelNumber,
                                           &rec_struct->indebtedness,
                                           &rec_struct->credit_limit,
                                           &rec_struct->cash_payments);
    return amount_of_read_rec_fields;
}
int fscan_trans_file(FILE *trans_file, Data *trans_struct) {
    int amount_of_read_trans_fields = fscanf(trans_file,
                                             FORMAT_STRING_TRANS_SCAN_PATTERN,
                                             &trans_struct->Number,
                                             &trans_struct->cash_payments);
    return amount_of_read_trans_fields;
}
int scan_rec_data(Data *rec_struct) {
    int result = scanf(FORMAT_STRING_REC_SCAN_PATTERN,
                       &rec_struct->Number,
                       rec_struct->Name,
                       rec_struct->Surname,
                       rec_struct->addres,
                       rec_struct->TelNumber,
                       &rec_struct->indebtedness,
                       &rec_struct->credit_limit,
                       &rec_struct->cash_payments);
    return result;
}
void write_rec_data(FILE *file, Data rec_struct) {
    fprintf(file,
            FORMAT_STRING_REC_PRINT_PATTERN,
            rec_struct.Number,
            rec_struct.Name,
            rec_struct.Surname,
            rec_struct.addres,
            rec_struct.TelNumber,
            rec_struct.indebtedness,
            rec_struct.credit_limit,
            rec_struct.cash_payments);
}
int scan_trans_data(Data *trans_struct) {
    int amount_of_scan_data = scanf(FORMAT_STRING_TRANS_SCAN_PATTERN,
                                    &trans_struct->Number,
                                    &trans_struct->cash_payments);
    return amount_of_scan_data;
}
void write_trans_data(FILE *trans_file, Data trans_struct) {
    fprintf(trans_file,
            FORMAT_STRING_TRANS_PRINT_PATTERN,
            trans_struct.Number,
            trans_struct.cash_payments);
}
