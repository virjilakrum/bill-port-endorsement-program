#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "finance/revenue.h"
#include "finance/invoice.h"
#include "utils/file_handler.h"

#define MAX_INVOICES 100
#define INVOICES_FILE "invoices.csv"
#define COMPANY_FILE "company.csv"

void print_menu() {
    printf("\n--- Bill-Port Muhasebe Programı ---\n");
    printf("1. Yeni Fatura Oluştur\n");
    printf("2. Fatura Görüntüle\n");
    printf("3. Ciro Hesapla\n");
    printf("4. Verileri Kaydet\n");
    printf("5. Raporlar\n");
    printf("6. Çıkış\n");
    printf("Seçiminiz: ");
}

void print_report_menu() {
    printf("\n--- Raporlar ---\n");
    printf("1. Tarih Aralığında Ciro\n");
    printf("2. En Çok Gelir Getiren Müşteriler\n");
    printf("3. Ürün Bazlı Satış Raporu\n");
    printf("4. Ana Menüye Dön\n");
    printf("Seçiminiz: ");
}

void generate_date_range_revenue_report(Invoice* invoices, int invoice_count) {
    time_t start_date, end_date;
    char date_str[20];

    printf("Başlangıç tarihini girin (YYYY-MM-DD): ");
    scanf("%s", date_str);
    start_date = convert_date_to_time_t(date_str);

    printf("Bitiş tarihini girin (YYYY-MM-DD): ");
    scanf("%s", date_str);
    end_date = convert_date_to_time_t(date_str);

    double total_revenue = 0.0;
    for (int i = 0; i < invoice_count; i++) {
        if (invoices[i].date >= start_date && invoices[i].date <= end_date) {
            total_revenue += invoices[i].total_amount;
        }
    }

    printf("Belirtilen tarih aralığındaki toplam ciro: %.2f TL\n", total_revenue);
}

void generate_top_customers_report(Invoice* invoices, int invoice_count) {
    // Bu fonksiyonu daha sonra implement edeceğim @virjilakrum 🏗️
    printf("Bu özellik henüz implement edilmedi.\n");
}

void generate_product_sales_report(Invoice* invoices, int invoice_count) {
    // Bu fonksiyonu daha sonra implement edeceğim @virjilakrum 🏗️
    printf("Bu özellik henüz implement edilmedi.\n");
}

int main() {
    Company company;
    Invoice invoices[MAX_INVOICES];
    int invoice_count = 0;
    int next_invoice_number = 1;

    // Mevcut verileri yükle
    if (load_company_from_csv(COMPANY_FILE, &company)) {
        printf("Şirket bilgileri yüklendi.\n");
    } else {
        printf("Şirket adını girin: ");
        fgets(company.company_name, sizeof(company.company_name), stdin);
        company.company_name[strcspn(company.company_name, "\n")] = 0;
        company.annual_revenue = 0.0;
    }

    if (load_invoices_from_csv(INVOICES_FILE, invoices, &invoice_count)) {
        printf("Faturalar yüklendi.\n");
        for (int i = 0; i < invoice_count; i++) {
            if (invoices[i].invoice_number >= next_invoice_number) {
                next_invoice_number = invoices[i].invoice_number + 1;
            }
        }
    }

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
                if (save_invoices_to_csv(INVOICES_FILE, invoices, invoice_count) &&
                    save_company_to_csv(COMPANY_FILE, &company)) {
                    printf("Veriler başarıyla kaydedildi.\n");
                } else {
                    printf("Veri kaydetme sırasında bir hata oluştu.\n");
                }
                break;
            case 5: {
                int report_choice;
                do {
                    print_report_menu();
                    scanf("%d", &report_choice);
                    getchar(); // Boş karakteri oku

                    switch (report_choice) {
                        case 1:
                            generate_date_range_revenue_report(invoices, invoice_count);
                            break;
                        case 2:
                            generate_top_customers_report(invoices, invoice_count);
                            break;
                        case 3:
                            generate_product_sales_report(invoices, invoice_count);
                            break;
                        case 4:
                            printf("Ana menüye dönülüyor...\n");
                            break;
                        default:
                            printf("Geçersiz seçim. Lütfen tekrar deneyin.\n");
                    }
                } while (report_choice != 4);
                break;
            }
            case 6:
                printf("Programdan çıkılıyor...\n");
                // Çıkmadan önce verileri otomatik kaydet
                save_invoices_to_csv(INVOICES_FILE, invoices, invoice_count);
                save_company_to_csv(COMPANY_FILE, &company);
                break;
            default:
                printf("Geçersiz seçim. Lütfen tekrar deneyin.\n");
        }
    } while (choice != 6);

    return 0;
}
