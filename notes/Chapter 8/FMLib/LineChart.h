#ifndef F206E193_2D01_407F_889F_BD1BFF2A16D1
#define F206E193_2D01_407F_889F_BD1BFF2A16D1

#include "stdafx.h"

class LineChart {
public:
    void setTitle( const std::string& title );
    void addEntry( double xvalue,
                   double yvalue );
    void setLabels( const std::string& xlabel,
                    const std::string& ylabel);
    void writeAsHTML( std::ostream& out ) const;
    void writeAsHTML(const std::string& file ) const;
private:
    std::string title;
    std::string xlabel;
    std::string ylabel;
    std::vector<double> xvalues;
    std::vector<double> yvalues;
};

void testLineChart();

#endif /* F206E193_2D01_407F_889F_BD1BFF2A16D1 */
