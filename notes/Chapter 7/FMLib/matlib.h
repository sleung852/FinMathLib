#pragma once

#include <cstdlib>
#include <random>
#include "stdafx.h"

/**
 *  Computes the cumulative
 *  distribution function of the
 *  normal distribution
 */
double normcdf( double x );

/**
 *  Computes the inverse of normcdf
 */
double norminv( double x ); 

/**
 *  Computes mean of a vector
 */
double mean(const std::vector<double> &v ); 

/**
 *  Computes the standard deviation of a vector
 */
double standardDeviation(const std::vector<double> &v, bool sample=true); 

double min(std::vector<double> v);
double max(std::vector<double> v);

std::vector<double> randuniform(int n);

double normalDist(double x, double mu=0, double sigma=1);
std::vector<double> randn(int n);

double prctile(std::vector<double> v, double p);


/**
 *  Test function
 */
void testMatlib();