/*
License: MIT License (http://www.opensource.org/licenses/mit-license.php)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

/* (C) 2013 Graeme Hattan & Bernd Porr */
/* (C) 2018-2021 Bernd Porr */
/* (C) 2022 Ross Gardiner */

#include "Fir1.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdexcept>

/*!
 * Initialise the filter from coefficients, assigned as array
 * @param _coefficients coeffs to be assigned
 * @param number_of_taps nr of taps (array length)
 */
Fir1::Fir1(double *_coefficients, unsigned number_of_taps) :
	coefficients(new double[number_of_taps]),
	buffer(new double[number_of_taps]()),
	taps(number_of_taps) {
	for(unsigned int i=0;i<number_of_taps;i++) {
		coefficients[i] = _coefficients[i];
		buffer[i] = 0;
	}
}

/*!
 * Initalise the filter with empty coefficients
 * @param number_of_taps nr of taps (filter order)
 */
Fir1::Fir1(unsigned number_of_taps) :
	coefficients(new double[number_of_taps]),
	buffer(new double[number_of_taps]),  
	taps(number_of_taps) {
	zeroCoeff();
	reset();
}

/*!
 * Initialise the filter with a std::vector of coefficients
 * @param _coefficients
 */
void Fir1::initWithVector(std::vector<double> _coefficients) {
	coefficients = new double[_coefficients.size()];
	buffer = new double[_coefficients.size()]();
	taps = ((unsigned int)_coefficients.size());
	for(unsigned long i=0;i<_coefficients.size();i++) {
		coefficients[i] = _coefficients[i];
		buffer[i] = 0;
	}
}	

/*!
 * Initialise the filter coefficients with a text file where each line is has one coefficient
 * @param coeffFile text file for initialisation
 * @param number_of_taps nr of fiter taps (order)
 */
Fir1::Fir1(const char* coeffFile, unsigned number_of_taps) {

	std::vector<double> tmpCoefficients;

	FILE* f=fopen(coeffFile,"rt");
	if (!f) {
		throw std::invalid_argument("Could not open file.");
	}
	for(unsigned int i=0;(i<number_of_taps)||(number_of_taps==0);i++) {
		double v = 0;
		int r = fscanf(f,"%lf\n",&v);
		if (r < 1) break;
		tmpCoefficients.push_back(v);
	}
	fclose(f);
	initWithVector(tmpCoefficients);
}

/*!
 * Filter destructor
 */
Fir1::~Fir1()
{
	delete[] buffer;
	delete[] coefficients;
}


/*!
 * sets all tap outputs to zero
 */
void Fir1::reset()
{
	memset(buffer, 0, sizeof(double)*taps);
	offset = 0;
}

/*!
 * Sets all coeffs to zero
 */
void Fir1::zeroCoeff() {
	memset(coefficients, 0, sizeof(double)*taps);
	offset = 0;
}

/*!
 * Copies a coeffs to coeff_data array
 * @param coeff_data
 * @param number_of_taps
 */
void Fir1::getCoeff(double* coeff_data, unsigned number_of_taps) const {
	
	if (number_of_taps < taps)
		throw std::out_of_range("Fir1: target of getCoeff: too many weights to copy into target");
 
	memcpy(coeff_data, coefficients, taps * sizeof(double));
	if (number_of_taps > taps)
		memset(&coeff_data[taps], 0, (number_of_taps - taps)*sizeof(double));
}

