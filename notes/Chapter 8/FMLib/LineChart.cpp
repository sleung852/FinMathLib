#include "LineChart.h"
#include <cmath>
#include "testing.h"

using namespace std;

// Copied from 7.7.8
static void writeTopBoilerPlateOfLineChart( ostream& out ) {
    out<<"<html>\n";
    out<<"<head>\n";
    out<<"<script type=\"text/javascript\" src=\"https://www.gstatic.com/charts/loader.js\"></script>\n";
    out<<"<script type=\"text/javascript\">\n";
    out<<"google.charts.load('current', {'packages':['corechart']});\n";
    out<<"google.charts.setOnLoadCallback(drawChart);\n";
    out<<"function drawChart() {\n";
    out<<"var data = google.visualization.arrayToDataTable([\n";
}

static void writeDataOfLineChart(ostream &out, const vector<double> &x_val, const vector<double> &y_val, string xlabel, string ylabel) {
    // if (x_val.size() != y_val.size()) throw ("")
    out << "['" << xlabel.c_str() << "', '" << ylabel.c_str() << "'],\n";
    for (size_t i=0; i<x_val.size(); i++) {
        out << "['" << x_val.at(i) << "', " << y_val.at(i) << "]";
        if (i!=(x_val.size()-1)) {
            out << ",";
        }
        out << "\n";
    }
    out << "]);\n";
}

static void writeBottomBoilerPlateOfLineChart(
		ostream & out,
        const string title) {
    out<<"var options = {\n";
    out<<"title: '"<< title << "',\n";
    out<<"curveType: 'function',\n";
    out<<"legend: { position: 'bottom' }\n";
    out<<"};\n";
    out<<"var chart = new google.visualization.LineChart(document.getElementById('curve_chart'));\n";
    out<<"chart.draw(data, options);\n";
    out<<"}\n";
    out<<"</script>\n";
    out<<"</head>\n";
    out<<"<body>\n";
    out<<"<div id=\"curve_chart\" style=\"width: 900px; height: 500px\"></div>\n";
    out<<"</body>\n";
    out<<"</html>";
}

/*
Core
*/

void LineChart::setTitle( const string& t ) {
    title = t;
}
void LineChart::setLabels( const string& xl,  const string& yl) {
    xlabel = xl;
    ylabel = yl;
}
void LineChart::addEntry( double xvalue,
                double yvalue ) {
    xvalues.push_back(xvalue);
    yvalues.push_back(yvalue);
                }
void LineChart::writeAsHTML( ostream& out ) const {
    writeTopBoilerPlateOfLineChart(out);
    writeDataOfLineChart(out, xvalues, yvalues, xlabel, ylabel);
    writeBottomBoilerPlateOfLineChart(out, title);
}
void LineChart::writeAsHTML(const string& file ) const{
    ofstream out;
    out.open(file.c_str());
    writeTopBoilerPlateOfLineChart(out);
    writeDataOfLineChart(out, xvalues, yvalues, xlabel, ylabel);
    writeBottomBoilerPlateOfLineChart(out, title);
    out.close();
}

/*
Test Functions
*/

// static void writeFixedLineChartData( ostream& out) {
//     out<<"['Year', 'Sales'],\n";
//     out<<"['2004',  1000],\n";
//     out<<"['2005',  1170],\n";
//     out<<"['2006',  660],\n";
//     out<<"['2007',  1030]\n";
//     out<<"]);\n";
// }

// static void testFixedLineChart() {
//     ofstream out;
//     out.open("FixedLineChart.html");
//     writeTopBoilerPlateOfLineChart(out);
//     writeFixedLineChartData( out );
//     writeBottomBoilerPlateOfLineChart( out, "Test Line Chart");
//     out.close();
// }

static void testLineChartClass() {
    vector<double> x_val({1,2,3,4,5,6,7,8,9,10});
    vector<double> y_val(10, 0.0);
    for (size_t i=0; i<x_val.size(); i++) {
        y_val[i] = x_val[i] * x_val[i];
    }
    string xlabel("X");
    string ylabel("X_Squared");

    LineChart linechart;
    linechart.setTitle("Test Line Chart");
    for (size_t i=0; i<x_val.size(); i++) {
        linechart.addEntry(x_val.at(i), y_val.at(i));
    }
    linechart.setLabels(xlabel, ylabel);
    linechart.writeAsHTML("myPieChart.html");
}

static void testLineChartData() {

    stringstream in_ss;
    vector<double> x_val({1.0,2.0,3.0,4.0});
    vector<double> y_val(4, 0.0);
    for (size_t i=0; i<x_val.size(); i++) {
        y_val[i] = x_val[i] * x_val[i];
        // DEBUG_PRINT(x_val[i] << " " << y_val[i]);
    }
    string xlabel("X");
    string ylabel("X_Squared");

    LineChart linechart;
    linechart.setTitle("Test Line Chart");
    for (size_t i=0; i<x_val.size(); i++) {
        linechart.addEntry(x_val.at(i), y_val.at(i));
    }
    linechart.setLabels(xlabel, ylabel);
    linechart.writeAsHTML(in_ss);

    stringstream expected_ss;
    writeTopBoilerPlateOfLineChart(expected_ss);
    expected_ss<<"['X', 'X_Squared'],\n";
    expected_ss<<"['1', 1],\n";
    expected_ss<<"['2', 4],\n";
    expected_ss<<"['3', 9],\n";
    expected_ss<<"['4', 16]\n";
    expected_ss<<"]);\n";
    writeBottomBoilerPlateOfLineChart( expected_ss, "Test Line Chart");
    DEBUG_PRINT("INPUT SS");
    DEBUG_PRINT(in_ss.str());
    DEBUG_PRINT("EXPECTED SS");
    DEBUG_PRINT(expected_ss.str());
    ASSERT( in_ss.str() == expected_ss.str());
}

void testLineChart() {
    TEST (testLineChartClass);
    TEST (testLineChartData);
}