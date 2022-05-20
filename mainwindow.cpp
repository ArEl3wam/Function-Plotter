#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "FunctionPlotterFunctions.cpp"
#include <QMessageBox>
#include <string>
#include <sstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


const char* ConvertDoubleToString(double value){
    std::stringstream ss;
    ss << value;
    const char* str = ss.str().c_str();
    return str;
}

void MainWindow::on_Solve_clicked()
{

    //taking parameters
    QString eq = ui->equationLine->text();
    QString maxi = ui->maximumLine->text();
    QString mini = ui->minimumLine->text();
    std::string equation = eq.toStdString();
    std::string maximum= maxi.toStdString();
    std::string minimum =mini.toStdString();


    double maxiNum =maxi.toDouble();
    double miniNum=mini.toDouble();
    double increment = (maxiNum-miniNum)/1000;
    //QMessageBox::information(this,tr("maximum number is"),tr(ConvertDoubleToString(increment)));

    double temp = miniNum;
    QVector<double> xValues;
    xValues.push_back(temp);
    QVector<double> yValues;
    yValues.push_back(equationSolver(postfix(replacer(equation,minimum))));
    for(int i=0; i<1000; i++){
        temp+=increment;
        std::string dummy = std::to_string(temp);
        xValues.push_back(temp);
        double tempY=equationSolver(postfix(replacer(equation,dummy)));
        yValues.push_back(tempY);

    }
    ui->customPlot->replot();
    MainWindow::makePlot(xValues, yValues);

    //double num= equationSolver(postfix(replacer(equation,maximum)));
    //QString qstring = QString::number(num);
    //QMessageBox::information(this,tr("maximum number is"),tr(ConvertDoubleToString(equationSolver(postfix(replacer(equation,maximum))))));
    //cout << equationSolver(postfix(replacer(equation,minimum))) << endl;
    //cout << equationSolver(postfix(replacer(equation,maximum)));
}

void MainWindow::makePlot(QVector<double> xValues , QVector<double>yValues){

    // generate some data:
    /*QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }*/
    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(xValues, yValues);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(xValues[0], xValues[xValues.size()-1]);
    ui->customPlot->yAxis->setRange(-20, 20);
    ui->customPlot->replot();

}
