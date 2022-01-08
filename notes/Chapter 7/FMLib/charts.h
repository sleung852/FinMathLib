#pragma once

#include "stdafx.h"


/**
 *   Write a pie chart
 */
void pieChart( std::string& file,
			   std::vector<std::string>& labels,
		 	   std::vector<double>& values );

void lineChart(const std::string& file,
				const std::vector<double>& xvalues,
				const std::vector<double>& yvalues,
				std::string xlabel,
				std::string ylabel);

void hist(const std::string& file,
				const std::vector<double>& values,
				int n);

/**
 *   Run unit tests for the charts package
 */
void testCharts();