#include <stdio.h>
#include <string.h>
#include <time.h>
#include "invoice.h"

Invoice create_invoice(int invoice_number, const char* customer_name) {
    Invoice new_invoice;
    new_invoice.invoice_number = invoice_number;
    strncpy(new_invoice.customer_name, customer_name, MAX_CUSTOMER_NAME - 1);
    new_invoice.customer_name[MAX_CUSTOMER_NAME - 1] = '\0';
    new_invoice.date = time(NULL);
    new_invoice.product_count = 0;
    new_invoice.total_amount = 0.0;
    return new_invoice;
}

int add_product_to_invoice(Invoice* invoice, const char* product_name, double price, int quantity) {
    if (invoice->product_count >= MAX_PRODUCTS) {
        return 0; // Fatura dolu, ürün eklenemedi
    }

    Product new_product;
    strncpy(new_product.name, product_name, MAX_PRODUCT_NAME - 1);
    new_product.name[MAX_PRODUCT_NAME - 1] = '\0';
    new_product.price = price;
    new_product.quantity = quantity;

    invoice->products[invoice->product_count] = new_product;
    invoice->product_count++;

    return 1; // Ürün başarıyla eklendi
}

void calculate_invoice_total(Invoice* invoice) {
    invoice->total_amount = 0.0;
    for (int i = 0; i < invoice->product_count; i++) {
        invoice->total_amount += invoice->products[i].price * invoice->products[i].quantity;
    }
}

void display_invoice(const Invoice* invoice) {
    printf("Fatura No: %d\n", invoice->invoice_number);
    printf("Müşteri: %s\n", invoice->customer_name);
    printf("Tarih: %s", ctime(&invoice->date));
    printf("Ürünler:\n");
    for (int i = 0; i < invoice->product_count; i++) {
        printf("  %s - Fiyat: %.2f TL, Adet: %d\n",
               invoice->products[i].name,
               invoice->products[i].price,
               invoice->products[i].quantity);
    }
    printf("Toplam Tutar: %.2f TL\n", invoice->total_amount);
}

void cancel_invoice(Invoice* invoice) {
    invoice->invoice_number = -1; // İptal edilmiş fatura
    invoice->total_amount = 0.0;
    invoice->product_count = 0;
}
