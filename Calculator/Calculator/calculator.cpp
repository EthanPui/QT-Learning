#include "calculator.h"
#include "ui_calculator.h"
#include <QRegularExpression>

double calcVal =0.0;
QString saveCurrentValue;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal)); // Converted calcVal which is defined as a double to QString!
    QPushButton *numButtons[10];    // Create array of 10 that holds reference to all our QPushButtons

    // Cycle through each of the QPushButtons
    // And Assign our signal and slot
    for(int i = 0; i < 10; ++i){
        QString butName = "Button" + QString::number(i); // Eg in UI we have Button0, Button1 etc
        numButtons[i] = Calculator::findChild<QPushButton *>(butName); // Add buttons to our array numButtons, by searching for the specific widget QPushButton by providing the name "butName"

        // Whenever Button is released we want to call NumPressed in calculator.h
        connect(numButtons[i], SIGNAL(released()), this,
                SLOT(NumPressed()));
    }
    connect(ui->Add, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));

    connect(ui->Equals, SIGNAL(released()), this,
            SLOT(EqualButtonPressed()));
    connect(ui->ChangeSign, SIGNAL(released()), this,
            SLOT(ChangeNumberSign()));
    connect(ui->Clear, SIGNAL(released()), this,
            SLOT(ClearButtonPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed(){
    QPushButton *button = (QPushButton *)sender();

    // Get number on the button
    QString butVal = button->text();

    //  Get value on our display
    QString displayVal = ui->Display->text();

    // Check if value is equal to zero
    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
        // Display butVal which is the button you just pressed.
        ui->Display->setText(butVal);
    }else{


        QString newVal = displayVal + butVal;
        double dbleNewVal = newVal.toDouble();

        // Set value in display up to 16 before it becomes exponents
        ui->Display->setText(QString::number(dbleNewVal, 'g', 16));
    }
}

void Calculator::MathButtonPressed(){
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;

    QString displayVal = ui->Display->text();   // Store current Value into displayVal
    calcVal = displayVal.toDouble();

    // Check Sender for what button was clicked on
    QPushButton *button = (QPushButton *)sender();

    // Get number on the button
    QString butVal = button->text();

    // Check if division button is pressed, divTrigger = true
    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){
        divTrigger = true;
    }else if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0){
        multTrigger = true;
    }else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
        addTrigger = true;
    }else {
        subTrigger = true;
    }
    // Clear Screen
    ui->Display->setText("");
}

void Calculator::EqualButtonPressed(){
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dbldisplayVal = displayVal.toDouble();

    if(addTrigger || subTrigger || multTrigger ||divTrigger){
        if(addTrigger){
            solution = calcVal + dbldisplayVal;
        }else if(subTrigger){
            solution = calcVal - dbldisplayVal;
        }else if(multTrigger){
            solution = calcVal * dbldisplayVal;
        }else{
            solution = calcVal / dbldisplayVal;
        }
    }
    ui->Display->setText(QString::number(solution));
}

void Calculator::ChangeNumberSign(){
    QString displayVal = ui->Display->text();
    QRegularExpression reg("[-]?[0-9.]*");
    QRegularExpressionMatch match = reg.match(displayVal);
    if(match.hasMatch()) {
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->Display->setText(QString::number(dblDisplayValSign));
    }
}

void Calculator::ClearButtonPressed(){

    ui->Display->setText("0");
}

void Calculator::on_MemAdd_clicked()
{
    saveCurrentValue = ui->Display->displayText();
//    QTextStream(stdout) << saveCurrentValue << "\n";
}

void Calculator::on_MemGet_clicked()
{
    ui->Display->setText(QString::number(saveCurrentValue.toDouble()));
}

void Calculator::on_MemClear_clicked()
{
    saveCurrentValue = "0.0";
}

