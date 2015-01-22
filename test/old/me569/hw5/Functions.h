#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <vector>
#include <memory>

#include "Branch.h"

typedef shared_ptr<vector<int> > shr_vec_int;

template <class T>
void mean( Branch<T>* b1, Branch<T>* b2, shr_vec_int dim );

template <class T>
void subtract( Branch<T>* b1, Branch<T>* b2, Branch<T>* b3, shr_vec_int dim );

int PerInd( int i, int sz );

double subtract( double& d1, double& d2 );

double divide( double& d1, double& d2 );

double func_tauRSMAG( double& d1, double& d2 );


#endif

