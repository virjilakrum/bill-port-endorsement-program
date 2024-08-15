#include <stdio.h>
   #include <string.h>
   #include "finance/revenue.h"

   #define MAX_TRANSACTIONS 100

   int main() {
       printf("Bill-Port Muhasebe Programına Hoş Geldiniz!\n");

       Company sample_company;
       printf("Şirket adını girin: ");
       fgets(sample_company.company_name, sizeof(sample_company.company_name), stdin);
       sample_company.company_name[strcspn(sample_company.company_name, "\n")] = 0; // Yeni satır karakterini kaldır
       sample_company.annual_revenue = 0.0;

       double transactions[MAX_TRANSACTIONS];
       int transaction_count = 0;

       printf("İşlemleri girin (Bitirmek için 0 veya negatif bir değer girin):\n");
       while (transaction_count < MAX_TRANSACTIONS) {
           double transaction;
           printf("İşlem %d: ", transaction_count + 1);
           if (scanf("%lf", &transaction) != 1 || transaction <= 0) {
               break;
           }
           transactions[transaction_count++] = transaction;
       }

calculate_revenue(&sample_company, transactions, transaction_count);

       printf("%s şirketinin yıllık cirosu: %.2f TL\n", sample_company.company_name, sample_company.annual_revenue);

       return 0;
   }
