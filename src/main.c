#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "finance/revenue.h"

#define MAX_TRANSACTIONS 100

int main() {
    printf("Bill-Port Muhasebe Programına Hoş Geldiniz!\n");

    Company sample_company;
    printf("Şirket adını girin: ");
    fgets(sample_company.company_name, sizeof(sample_company.company_name), stdin);
    sample_company.company_name[strcspn(sample_company.company_name, "\n")] = 0;
    sample_company.annual_revenue = 0.0;

    double transactions[MAX_TRANSACTIONS];
    int transaction_count = 0;

    printf("İşlemleri girin (Bitirmek için 0 veya negatif bir değer girin):\n");
    char input[100];
    while (transaction_count < MAX_TRANSACTIONS) {
        printf("İşlem %d (TL): ", transaction_count + 1);
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        double transaction = atof(input);
        if (transaction <= 0) {
            break;
        }
        transactions[transaction_count++] = transaction;
    }

    calculate_revenue(&sample_company, transactions, transaction_count);

    printf("%s şirketinin yıllık cirosu: %.2f TL\n", sample_company.company_name, sample_company.annual_revenue);

    return 0;
}
