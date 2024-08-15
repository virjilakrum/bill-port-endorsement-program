#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "../finance/invoice.h"
#include "../finance/revenue.h"

#define MAX_LINE 1024

// Faturaları CSV dosyasına kaydetme fonksiyonu
int save_invoices_to_csv(const char* filename, Invoice* invoices, int invoice_count);

// Faturaları CSV dosyasından okuma fonksiyonu
int load_invoices_from_csv(const char* filename, Invoice* invoices, int* invoice_count);

// Şirket bilgilerini CSV dosyasına kaydetme fonksiyonu
int save_company_to_csv(const char* filename, const Company* company);

// Şirket bilgilerini CSV dosyasından okuma fonksiyonu
int load_company_from_csv(const char* filename, Company* company);

#endif // FILE_HANDLER_H
