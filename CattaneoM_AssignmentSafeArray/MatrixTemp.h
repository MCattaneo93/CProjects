/*
 * MatrixTemp.h
 *
 *  Created on: Oct 23, 2020
 *      Author: mcatt
 */

#ifndef MATRIXTEMP_H_
#define MATRIXTEMP_H_
#include "SafeArray.h"
template <typename T> class Matrix
{
	SA *p;
public:
	Matrix(int low_r, int high_r, int low_c, int high_c){

		p = new SA[high_r - low_r + 1];
	}
};



#endif /* MATRIXTEMP_H_ */
