#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "finance/revenue.h"
#include "finance/invoice.h"

#define MAX_INVOICES 100

void print_menu() {
    printf("\n--- Bill-Port Muhasebe Programı ---\n");
    printf("1. Yeni Fatura Oluştur\n");
    printf("2. Fatura Görüntüle\n");
    printf("3. Ciro Hesapla\n");
    printf("4. Çıkış\n");
    printf("Seçiminiz: ");
}

int main() {
    Company company;
    printf("Şirket adını girin: ");
    fgets(company.company_name, sizeof(company.company_name), stdin);
    company.company_name[strcspn(company.company_name, "\n")] = 0;
    company.annual_revenue = 0.0;

    Invoice invoices[MAX_INVOICES];
    int invoice_count = 0;
    int next_invoice_number = 1;

    int choice;
    do {
        print_menu();
        scanf("%d", &choice);
        getchar(); // Boş karakteri oku

        switch (choice) {
            case 1: {
                if (invoice_count >= MAX_INVOICES) {
                    printf("Maksimum fatura sayısına ulaşıldı.\n");
                    break;
                }
                char customer_name[MAX_CUSTOMER_NAME];
                printf("Müşteri adı: ");
                fgets(customer_name, sizeof(customer_name), stdin);
                customer_name[strcspn(customer_name, "\n")] = 0;

                invoices[invoice_count] = create_invoice(next_invoice_number++, customer_name);

                char product_name[MAX_PRODUCT_NAME];
                double price;
                int quantity;

                do {
                    printf("Ürün adı (veya bitirmek için 'q'): ");
                    fgets(product_name, sizeof(product_name), stdin);
                    product_name[strcspn(product_name, "\n")] = 0;

                    if (strcmp(product_name, "q") == 0) break;

                    printf("Fiyat: ");
                    scanf("%lf", &price);
                    printf("Adet: ");
                    scanf("%d", &quantity);
                    getchar(); // Boş karakteri oku

                    if (add_product_to_invoice(&invoices[invoice_count], product_name, price, quantity)) {
                        printf("Ürün eklendi.\n");
                    } else {
                        printf("Ürün eklenemedi. Fatura dolu.\n");
                        break;
                    }
                } while (1);

                calculate_invoice_total(&invoices[invoice_count]);
                company.annual_revenue += invoices[invoice_count].total_amount;

                printf("Fatura oluşturuldu:\n");
                display_invoice(&invoices[invoice_count]);

                invoice_count++;
                break;
            }
            case 2: {
                int invoice_number;
                printf("Görüntülemek istediğiniz faturanın numarasını girin: ");
                scanf("%d", &invoice_number);
                getchar(); // Boş karakteri oku

                int found = 0;
                for (int i = 0; i < invoice_count; i++) {
                    if (invoices[i].invoice_number == invoice_number) {
                        display_invoice(&invoices[i]);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    printf("Fatura bulunamadı.\n");
                }
                break;
            }
            case 3:
                printf("%s şirketinin yıllık cirosu: %.2f TL\n", company.company_name, company.annual_revenue);
                break;
            case 4:
                printf("Programdan çıkılıyor...\n");
                break;
            default:
                printf("Geçersiz seçim. Lütfen tekrar deneyin.\n");
        }
    } while (choice != 4);

    return 0;
}
