//
// Created by Adnan Hajro on 29. 10. 2025..
//

#include <stdlib.h>
#include <math.h>
#include "sum_algorithms.h"

double do_sum(double* restrict var, long ncells)
{
   double sum = 0.0;
   for (long i = 0; i < ncells; i++){
      sum += var[i];
   }
   return sum;
}

long double do_longdouble_sum(double* restrict var, long ncells)
{
   long double sum = 0.0L;
   for (long i = 0; i < ncells; i++){
      sum += (long double)var[i];
   }
   return sum;
}

double do_pair_sum(double* restrict var, long ncells)
{
   if (ncells == 0) return 0.0;
   if (ncells == 1) return var[0];
   
   // Create a temporary array for pairwise summation
   double *temp = (double *)malloc(ncells * sizeof(double));
   
   // Copy input data
   for (long i = 0; i < ncells; i++){
      temp[i] = var[i];
   }
   
   long size = ncells;
   while (size > 1) {
      long new_size = (size + 1) / 2;
      for (long i = 0; i < new_size; i++){
         if (2*i + 1 < size) {
            temp[i] = temp[2*i] + temp[2*i + 1];
         } else {
            temp[i] = temp[2*i];
         }
      }
      size = new_size;
   }
   
   double result = temp[0];
   free(temp);
   return result;
}

double do_kahan_sum(double* restrict var, long ncells)
{
   double sum = 0.0;
   double compensation = 0.0;
   
   for (long i = 0; i < ncells; i++){
      double y = var[i] - compensation;
      double t = sum + y;
      compensation = (t - sum) - y;
      sum = t;
   }
   return sum;
}

double do_knuth_sum(double* restrict var, long ncells)
{
   double sum = 0.0;
   double correction = 0.0;
   
   for (long i = 0; i < ncells; i++){
      double adjusted_value = var[i] - correction;
      double new_sum = sum + adjusted_value;
      correction = (new_sum - sum) - adjusted_value;
      sum = new_sum;
   }
   return sum;
}