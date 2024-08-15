#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_handler.h"

int save_invoices_to_csv(const char* filename, Invoice* invoices, int invoice_count) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Dosya açılamadı: %s\n", filename);
        return 0;
    }

    fprintf(file, "Fatura No,Müşteri,Tarih,Toplam Tutar\n");
    for (int i = 0; i < invoice_count; i++) {
        fprintf(file, "%d,%s,%ld,%.2f\n",
                invoices[i].invoice_number,
                invoices[i].customer_name,
                invoices[i].date,
                invoices[i].total_amount);
    }

    fclose(file);
    return 1;
}

int load_invoices_from_csv(const char* filename, Invoice* invoices, int* invoice_count) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Dosya açılamadı: %s\n", filename);
        return 0;
    }

    char line[MAX_LINE];
    fgets(line, MAX_LINE, file); // Başlık satırını atla

    *invoice_count = 0;
    while (fgets(line, MAX_LINE, file) && *invoice_count < MAX_INVOICES) {
        Invoice* invoice = &invoices[*invoice_count];
        sscanf(line, "%d,%[^,],%ld,%lf",
               &invoice->invoice_number,
               invoice->customer_name,
               &invoice->date,
               &invoice->total_amount);
        (*invoice_count)++;
    }

    fclose(file);
    return 1;
}

int save_company_to_csv(const char* filename, const Company* company) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Dosya açılamadı: %s\n", filename);
        return 0;
    }

    fprintf(file, "Şirket Adı,Yıllık Ciro\n");
    fprintf(file, "%s,%.2f\n", company->company_name, company->annual_revenue);

    fclose(file);
    return 1;
}

int load_company_from_csv(const char* filename, Company* company) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Dosya açılamadı: %s\n", filename);
        return 0;
    }

    char line[MAX_LINE];
    fgets(line, MAX_LINE, file); // Başlık satırını atla

    if (fgets(line, MAX_LINE, file)) {
        sscanf(line, "%[^,],%lf", company->company_name, &company->annual_revenue);
    }

    fclose(file);
    return 1;
}
