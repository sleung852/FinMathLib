#include "charts.h"
#include "testing.h"

using namespace std;

// Pie Chart

/**
 *  Write the necessary junk for the top of the chart
 */
static void writeTopBoilerPlateOfPieChart( ostream& out ) {
    out<<"<html>\n";
    out<<"<head>\n";
    out<<"<!--Load the AJAX API-->\n";
    out<<"<script type=\"text/javascript\"";
    out<<"src=\"https://www.google.com/jsapi\">";
    out<<"</script>\n";
    out<<"<script type=\"text/javascript\">\n";
    out<<"google.load('visualization', '1.0',";
    out<<" {'packages':['corechart']});\n";
    out<<"google.setOnLoadCallback(drawChart);\n";
    out<<"function drawChart() {\n";
    out<<"var data=new google.visualization.DataTable();";
    out<<"\n";
    out<<"data.addColumn('string', 'Label');\n";
    out<<"data.addColumn('number', 'Value');\n";
}
/**
 *  Write the intesting bit of the Pie Chart
 */
static void writeDataOfPieChart( ostream& out,
                   const vector<string>& labels,
                   const vector<double>& values) {
    out<< "data.addRows([\n";
    int nLabels = labels.size();
    for (int i=0; i<nLabels; i++) {
        string label = labels[i];
        double value = values[i];
        out<<"['"<<label<<"', "<<value<<"]";
        if (i!=nLabels-1) {
            out<<",";
        }
        out<<"\n";
    }
    out<<"]);\n";
}

/**
 *  Write the boring bit at the bottom of a pie chart
 */
static void writeBottomBoilerPlateOfPieChart(
		ostream & out ) {
    out<<"var options = {'title':'A Pie Chart',\n";
    out<<"'width':400,\n";
    out<<"'height':300\n";
    out<<"};\n";
    out<<"var chart = new google.visualization.PieChart(";
    out<<"document.getElementById('chart_div'));\n";
    out<<"chart.draw(data, options);\n";
    out<<"}\n";
    out<<"</script>\n";
    out<<"</head>\n";
    out<<"<body>\n";
    out<<"<div id='chart_div'>\n";
    out<<"</body>\n";
    out<<"</html>";
}


// Line Chart
// 7.7.8
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
		ostream & out ) {
    out<<"var options = {\n";
    out<<"title: 'A Line Chart',\n";
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

/**
 *   Write a pie chart
 */
void pieChart( const string& file,
               const vector<string>& labels,
               const vector<double>& values ) {
    ofstream out;
    out.open(file.c_str());
    writeTopBoilerPlateOfPieChart(out);
    writeDataOfPieChart( out, labels, values );
    writeBottomBoilerPlateOfPieChart( out );
    out.close();
}

/**
 *   Write a line chart
 */
void lineChart( const string& file,
               const vector<double>& xvalues,
               const vector<double>& yvalues,
               string xlabel,
               string ylabel) {
    ofstream out;
    out.open(file.c_str());
    writeTopBoilerPlateOfLineChart(out);
    writeDataOfLineChart(out, xvalues, yvalues, xlabel, ylabel);
    writeBottomBoilerPlateOfLineChart(out);
    out.close();
}


// 7.7.10
/**
 *   Write a histogram
 */

void writeDataOfHist(ostream &out, const vector<double> &values, int n, string label) {
    double bar_size = (max(values.begin(), values.end()) - min(values.begin(), values.end()))/n;
    vector<double> ranges(n, 0.0);
    vector<double> bars(n, 0.0);
    for (int i=0; i<values.size(); i++) {
        bars[int(values.at(i)/bar_size)] += 1;
        ranges[i] = 0.0 + static_cast<double>(i)*bar_size;
    }
    
    out << "['" << label.c_str() << "', 'Frequency'],\n";
    for (size_t i=0; i<n; i++) {
        out << "['" << ranges.at(i) << "', " << bars.at(i) << "]";
        if (i!=(ranges.size()-1)) {
            out << ",";
        }
        out << "\n";
    }
    out << "]);\n";

}


void hist(const string& file,
			const vector<double>& values,
			int n,
            string label) {
    ofstream out;
    out.open(file.c_str());
    writeTopBoilerPlateOfLineChart(out);
    writeDataOfHist(out, values, n, label);
    writeBottomBoilerPlateOfLineChart(out);
    out.close();
}


////////////////////////
//
//   TEMPORARY FUNCTIONS THAT OCCURRED WHILE
///  DEVELOPING THE SOLUTION, NORMALLY I'D DELETE THESE
//   AT THE END OF DEVELOPMENT
//
////////////////////////

/**
 *   While developing the code we wrote these (temporary) functions. We'd
 *   delete this from our final library.
 */
static void writeFixedPieChartData( ostream& out) {
    out<<"data.addRows([\n";
    out<<"['Bananas', 100],\n";
    out<<"['Apples', 200],\n";
    out<<"['Kumquats', 150]\n";
    out<<"]);\n";
}

static void testFixedPieChart() {
    ofstream out;
    out.open("FixedPieChart.html");
    writeTopBoilerPlateOfPieChart(out);
    writeFixedPieChartData( out );
    writeBottomBoilerPlateOfPieChart( out );
    out.close();
}

static void writeFixedLineChartData( ostream& out) {
    out<<"['Year', 'Sales'],\n";
    out<<"['2004',  1000],\n";
    out<<"['2005',  1170],\n";
    out<<"['2006',  660],\n";
    out<<"['2007',  1030]\n";
    out<<"]);\n";
}

static void testFixedLineChart() {
    ofstream out;
    out.open("FixedLineChart.html");
    writeTopBoilerPlateOfLineChart(out);
    writeFixedLineChartData( out );
    writeBottomBoilerPlateOfLineChart( out );
    out.close();
}

///////////////////////////////////////////
//
//   Tests for charts
//
///////////////////////////////////////////


static void testPieChart() {
    // this test is unsatisfactory in that it requires manual
    // checking, you'll have to hunt for the file it generates and then
    // view it in a web browser
    vector<string> labels(10);
    vector<double> vals(10);
    for (int i=0; i<10; i++) {
        stringstream ss;
        ss<<"A Label "<<i;
        labels[i] =ss.str();
        vals[i]=(double)i;
    }
    pieChart( "myPieChart.html",
              labels,
              vals );
}

static void testPieChartData() {
    // this test automates the checking
    stringstream out;
    vector<string> labels(3);
    vector<double> vals(3);
    for (int i=0; i<3; i++) {
        stringstream ss;
        ss<<"A Label "<<i;
        labels[i] =ss.str();
        INFO( labels[i] );
        vals[i]=(double)i;
    }
    writeDataOfPieChart( out,
              labels,
              vals );
    string asString = out.str();

    stringstream expected;
    expected<<"data.addRows([\n";
    expected<<"['A Label 0', 0],\n";
    expected<<"['A Label 1', 1],\n";
    expected<<"['A Label 2', 2]\n";
    expected<<"]);\n";
    string expectedStr = expected.str();
    ASSERT( asString==expectedStr );
}

static void testLineChart() {
    vector<double> x_val({1,2,3,4,5,6,7,8,9,10});
    vector<double> y_val(10, 0.0);
    for (size_t i=0; i<x_val.size(); i++) {
        y_val[i] = x_val[i] * x_val[i];
    }
    string xlabel("X");
    string ylabel("X_Squared");

    lineChart( "myLineChart.html",
                x_val,
                y_val,
                xlabel,
                ylabel);
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
    writeDataOfLineChart(in_ss, x_val, y_val, xlabel, ylabel);

    stringstream expected_ss;
    expected_ss<<"['X', 'X_Squared'],\n";
    expected_ss<<"['1', 1],\n";
    expected_ss<<"['2', 4],\n";
    expected_ss<<"['3', 9],\n";
    expected_ss<<"['4', 16]\n";
    expected_ss<<"]);\n";
    DEBUG_PRINT("INPUT SS");
    DEBUG_PRINT(in_ss.str());
    DEBUG_PRINT("EXPECTED SS");
    DEBUG_PRINT(expected_ss.str());
    ASSERT( in_ss.str() == expected_ss.str());
}

static void testHist() {
    vector<double> val({3.0, 4.4, 12.3, 3.2, 1.3, 6.5, 4.5, 8.8, 13});
    string label("Values");

    hist( "myHist.html",
        val,
        5,
        label);
    }

void testCharts() {
    TEST( testFixedPieChart );
    TEST( testPieChart );
    TEST( testPieChartData );

    TEST( testFixedLineChart);
    TEST( testLineChart );
    setDebugEnabled(true);
    TEST( testLineChartData);
    setDebugEnabled(false);
    TEST( testHist);


}