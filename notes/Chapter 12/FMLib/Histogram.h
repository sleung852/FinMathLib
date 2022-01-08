#pragma once

#include "stdafx.h"
#include "LineChart.h"

class Histogram : public Chart {
public:
    Histogram();
    void setNumBuckets( int n );
    // void setTitle( const std::string& title );
    void setData( const std::vector<double>& v );
    void writeAsHTML( std::ostream& out ) const;
    void writeAsHTML( const std::string& file ) const;
private:
    int numBuckets;
    // std::string title;
    std::vector<double> data;
};


void testHistogram();