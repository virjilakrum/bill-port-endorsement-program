#include "revenue.h"

   double calculate_revenue(Company* company, double* transactions, int transaction_count) {
       double total_revenue = 0.0;
       for (int i = 0; i < transaction_count; i++) {
           total_revenue += transactions[i];
       }
       return total_revenue;
   }

   void update_company_revenue(Company* company, double new_revenue) {
       company->annual_revenue = new_revenue;
   }
