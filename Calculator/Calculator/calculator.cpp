#include "calculator.h"
#include "ui_calculator.h"

double calcVal =0.0;
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
