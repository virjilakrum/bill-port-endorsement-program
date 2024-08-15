#include <stdio.h>
#include <string.h>
#include "finance/revenue.h"

int main() {
    printf("Bill-Port Muhasebe Programına Hoş Geldiniz!\n");

    Company sample_company;
    strcpy(sample_company.company_name, "Örnek Şirket");
    sample_company.annual_revenue = 0.0;

    double transactions[] = {1000.0, 2000.0, 3000.0, 4000.0, 5000.0};
    int transaction_count = sizeof(transactions) / sizeof(transactions[0]);

    double total_revenue = calculate_revenue(&sample_company, transactions, transaction_count);
    update_company_revenue(&sample_company, total_revenue);

    printf("%s şirketinin yıllık cirosu: %.2f TL\n", sample_company.company_name, sample_company.annual_revenue);

    return 0;
}
