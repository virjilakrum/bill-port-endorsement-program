#ifndef REVENUE_H
   #define REVENUE_H

   typedef struct {
       char company_name[100];
       double annual_revenue;
   } Company;

   double calculate_revenue(Company* company, double* transactions, int transaction_count);
   void update_company_revenue(Company* company, double new_revenue);

   #endif // REVENUE_H
