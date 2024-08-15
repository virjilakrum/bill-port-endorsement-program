#ifndef INVOICE_H
#define INVOICE_H

#include <time.h>

#define MAX_CUSTOMER_NAME 100
#define MAX_PRODUCT_NAME 100
#define MAX_PRODUCTS 10
#define MAX_INVOICES 100

typedef struct {
    char name[MAX_PRODUCT_NAME];
    double price;
    int quantity;
} Product;

typedef struct {
    int invoice_number;
    char customer_name[MAX_CUSTOMER_NAME];
    time_t date;
    Product products[MAX_PRODUCTS];
    int product_count;
    double total_amount;
} Invoice;

// Fatura oluşturma fonksiyonu
Invoice create_invoice(int invoice_number, const char* customer_name);

// Ürün ekleme fonksiyonu
int add_product_to_invoice(Invoice* invoice, const char* product_name, double price, int quantity);

// Fatura toplam tutarını hesaplama fonksiyonu
void calculate_invoice_total(Invoice* invoice);

// Fatura görüntüleme fonksiyonu
void display_invoice(const Invoice* invoice);

// Fatura iptal etme fonksiyonu
void cancel_invoice(Invoice* invoice);

#endif // INVOICE_H
