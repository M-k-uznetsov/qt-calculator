#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cctype>
#include <cmath>

#define SEPARATOR '.'

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    
    //!!! ИСПРАВЛЕНО Не надо писать this там, где он не нужен
    
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("MainWindow"));
    resize(16, 16);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    setSizePolicy(sizePolicy);
    radioButtonSimple = new QRadioButton(this);
    radioButtonSimple->setObjectName(QString::fromUtf8("SimpleRadioButton"));
    radioButtonSimple->setGeometry(QRect(0, 0, 84, 22));
    radioButtonCompl = new QRadioButton(this);
    radioButtonCompl->setObjectName(QString::fromUtf8("EngRadioButton"));
    radioButtonCompl->setGeometry(QRect(0, 0, 105, 22));
    lineEdit = new QLineEdit(this);
    lineEdit->setObjectName(QString::fromUtf8("LineEdit"));
    lineEdit->setGeometry(QRect(0, 0, 108, 22));

    radioButtonSimple->setText(tr("Обычный")); //!!! ИСПРАВЛЕНО Строки, отображаемые в интерфейсе, желательно помещать в tr("...")
    radioButtonCompl->setText(tr("Инженерный")); //!!! ИСПРАВЛЕНО Строки, отображаемые в интерфейсе, желательно помещать в tr("...")
    QMetaObject::connectSlotsByName(this);

    setWindowTitle(tr("Калькулятор (обычный)")); //!!! ИСПРАВЛЕНО Строки, отображаемые в интерфейсе, желательно помещать в tr("...")
    setWindowOpacity(1);
    setMinimumSize(380, 450);
    setMaximumSize(380, 450);

    lineEdit->setPlaceholderText("0");
    lineEdit->setReadOnly(true);
    radioButtonSimple->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    radioButtonCompl->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred);
    radioButtonSimple->setChecked(true);
    connect(radioButtonSimple, SIGNAL(toggled(bool)), SLOT(SwitchMode()));

    CreateSimpleCalcWidget();
    CreateComplCalcWidget();
    CreateDefaultCalcWidget();
    SpawnSimpleMode();
}

MainWindow::~MainWindow() {}

void MainWindow::SwitchMode() {
    simpleCalcWidget->setParent(this);
    complCalcWidget->setParent(this);
    if (!radioButtonSimple->isChecked()) {
        
        
        delete mainLayout; //!!!КНОПКИ ОБЫЧНОГО РЕЖИМА ИСПОЛЬЗУЮТСЯ В ИНЖЕНЕРНОМ РЕЖИМЕ И ПОЭТОМУ НЕ УДАЛЯЮТСЯ
                           //!!!При удалении mainLayout удаляется только выравнивание, но не кнопки. Где удаление кнопок через delete при переключении режимов?

        
        setWindowTitle(tr("Калькулятор (инженерный)")); //!!! ИСПРАВЛЕНО Строки, отображаемые в интерфейсе, желательно помещать в tr("...")
        
        setMinimumSize(700, 500);
        setMaximumSize(700, 500);
        SpawnComplMode();
    }
    else {
        delete mainLayout; //!!!ИСПРАВЛЕНО При удалении mainLayout удаляется только выравнивание, но не кнопки. Где удаление кнопок через delete при переключении режимов?
        delete pushButtonSinh;
        delete pushButtonSin;
        delete pushButtonExp;
        delete pushButtonXSq;
        delete pushButtonCosh;
        delete pushButtonCos;
        delete pushButtonLn;
        delete pushButtonXCubed;
        delete pushButtonTanh;
        delete pushButtonTan;
        delete pushButtonLog;
        delete pushButtonXNed;
        delete pushButtonFact;
        delete pushButtonPi;
        delete pushButtonCubeRoot;
        delete pushButtonNRoot;
        setWindowTitle(tr("Калькулятор (обычный)")); //!!! ИСПРАВЛЕНО Строки, отображаемые в интерфейсе, желательно помещать в tr("...")
        setMinimumSize(400, 500);
        setMaximumSize(400, 500);
        SpawnSimpleMode();
    }
}

void MainWindow::SpawnSimpleMode() {
    mainLayout = new QGridLayout;
    mainLayout->setSpacing(0);
    complCalcWidget->hide();
    mainLayout->addWidget(defaultCalcWidget, 0, 0, 1, 3);
    mainLayout->addWidget(simpleCalcWidget,  1, 0, 2, 3);

    this->setLayout(mainLayout);
    this->layout()->setContentsMargins(0, 0, 0, 0);

}

void MainWindow::SpawnComplMode() {
    CreateComplCalcWidget();
    mainLayout = new QGridLayout;
    mainLayout->setSpacing(0);
    mainLayout->addWidget(defaultCalcWidget, 0, 0, 1, 9);
    mainLayout->addWidget(complCalcWidget,   1, 0, 2, 4);
    mainLayout->addWidget(simpleCalcWidget,  1, 4, 2, 5);
    complCalcWidget->show();

    this->setLayout(mainLayout);
    this->layout()->setContentsMargins(0, 0, 0, 0);
}

void MainWindow::CreateSimpleCalcWidget() {
    
    //!!! ИСПРАВЛЕНО При создании всех объектов желательно указывать объект-родитель. (НЕ ИСПРАВЛЕНО)

    QPushButton* pushButton0 =      new QPushButton("0",this);
    QPushButton* pushButton1 =      new QPushButton("1",this);
    QPushButton* pushButton2 =      new QPushButton("2",this);
    QPushButton* pushButton3 =      new QPushButton("3",this);
    QPushButton* pushButton4 =      new QPushButton("4",this);
    QPushButton* pushButton5 =      new QPushButton("5",this);
    QPushButton* pushButton6 =      new QPushButton("6",this);
    QPushButton* pushButton7 =      new QPushButton("7",this);
    QPushButton* pushButton8 =      new QPushButton("8",this);
    QPushButton* pushButton9 =      new QPushButton("9",this);
    QPushButton* pushButtonDot =    new QPushButton(".",this);
    QPushButton* pushButtonPlus =   new QPushButton("+",this);
    QPushButton* pushButtonMinus =  new QPushButton(QString::fromUtf8("-"),this);
    QPushButton* pushButtonMult =   new QPushButton(QString::fromUtf8("\u00D7"),this);
    QPushButton* pushButtonDivide = new QPushButton(QString::fromUtf8("\u00F7"),this);
    QPushButton* pushButtonEquals = new QPushButton("=",this);
    QPushButton* pushButtonSqrt =   new QPushButton(QString::fromUtf8("\u221Ax"),this);
    QPushButton* pushButtonInvert = new QPushButton("1/x",this);
    QPushButton* PushButtonPlusMinus = new QPushButton(QString::fromUtf8("\u00B1"), this);
    pushButton0->setSizePolicy(     QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButton1->setSizePolicy(     QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButton2->setSizePolicy(     QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButton3->setSizePolicy(     QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButton4->setSizePolicy(     QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButton5->setSizePolicy(     QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButton6->setSizePolicy(     QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButton7->setSizePolicy(     QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButton8->setSizePolicy(     QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButton9->setSizePolicy(     QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonPlus->setSizePolicy(  QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonMinus->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonDot->setSizePolicy(   QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonMult->setSizePolicy(  QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonDivide->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonEquals->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonInvert->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonSqrt->setSizePolicy(  QSizePolicy::Preferred, QSizePolicy::Preferred);
    PushButtonPlusMinus->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);



    simpleCalcLayout = new QGridLayout(this);
    simpleCalcLayout->setSpacing(1);
    simpleCalcLayout->setContentsMargins(0, 0, 0, 0);

    simpleCalcLayout->addWidget(pushButton7,      0, 0, 1, 1);
    simpleCalcLayout->addWidget(pushButton8,      0, 1, 1, 1);
    simpleCalcLayout->addWidget(pushButton9,      0, 2, 1, 1);
    simpleCalcLayout->addWidget(pushButtonDivide, 0, 3, 1, 1);
    simpleCalcLayout->addWidget(pushButtonSqrt,   0, 4, 1, 1);
    simpleCalcLayout->addWidget(pushButton4,      1, 0, 1, 1);
    simpleCalcLayout->addWidget(pushButton5,      1, 1, 1, 1);
    simpleCalcLayout->addWidget(pushButton6,      1, 2, 1, 1);
    simpleCalcLayout->addWidget(pushButtonMult,   1, 3, 1, 1);
    simpleCalcLayout->addWidget(pushButtonInvert, 1, 4, 1, 1);
    simpleCalcLayout->addWidget(pushButton1,      2, 0, 1, 1);
    simpleCalcLayout->addWidget(pushButton2,      2, 1, 1, 1);
    simpleCalcLayout->addWidget(pushButton3,      2, 2, 1, 1);
    simpleCalcLayout->addWidget(pushButtonMinus,  2, 3, 1, 1);
    simpleCalcLayout->addWidget(pushButtonEquals, 3, 4, 1, 1);
    simpleCalcLayout->addWidget(pushButton0,      3, 0, 1, 2);
    simpleCalcLayout->addWidget(pushButtonDot,    3, 2, 1, 1);
    simpleCalcLayout->addWidget(pushButtonPlus,   3, 3, 1, 1);
    simpleCalcLayout->addWidget(PushButtonPlusMinus,   2, 4, 1, 1);

    simpleCalcWidget = new QWidget(this);
    simpleCalcWidget->setLayout(simpleCalcLayout);

    connect(pushButton0,      SIGNAL(clicked()), this, SLOT(NumberClicked()));
    connect(pushButton1,      SIGNAL(clicked()), this, SLOT(NumberClicked()));
    connect(pushButton2,      SIGNAL(clicked()), this, SLOT(NumberClicked()));
    connect(pushButton3,      SIGNAL(clicked()), this, SLOT(NumberClicked()));
    connect(pushButton4,      SIGNAL(clicked()), this, SLOT(NumberClicked()));
    connect(pushButton5,      SIGNAL(clicked()), this, SLOT(NumberClicked()));
    connect(pushButton6,      SIGNAL(clicked()), this, SLOT(NumberClicked()));
    connect(pushButton7,      SIGNAL(clicked()), this, SLOT(NumberClicked()));
    connect(pushButton8,      SIGNAL(clicked()), this, SLOT(NumberClicked()));
    connect(pushButton9,      SIGNAL(clicked()), this, SLOT(NumberClicked()));
    connect(pushButtonPlus,   SIGNAL(clicked()), this, SLOT(BinFnClicked()));
    connect(pushButtonMinus,  SIGNAL(clicked()), this, SLOT(BinFnClicked()));
    connect(pushButtonMult,   SIGNAL(clicked()), this, SLOT(BinFnClicked()));
    connect(pushButtonDivide, SIGNAL(clicked()), this, SLOT(BinFnClicked()));
    connect(pushButtonSqrt,   SIGNAL(clicked()), this, SLOT(UnFnClicked()));
    connect(pushButtonDot,    SIGNAL(clicked()), this, SLOT(DotClicked()));
    connect(pushButtonEquals, SIGNAL(clicked()), this, SLOT(Equals()));
    connect(pushButtonInvert, SIGNAL(clicked()), this, SLOT(UnFnClicked()));
    connect(PushButtonPlusMinus,  SIGNAL(clicked()), this, SLOT(UnFnClicked()));
}

void MainWindow::CreateComplCalcWidget() {
    pushButtonSinh     = new QPushButton("sinh",this);
    pushButtonSin      = new QPushButton("sin",this);
    pushButtonExp      = new QPushButton(QString::fromUtf8("e\u207F"),this);
    pushButtonXSq      = new QPushButton(QString::fromUtf8("x\u00B2"),this);
    pushButtonCosh     = new QPushButton("cosh",this);
    pushButtonCos      = new QPushButton("cos",this);
    pushButtonLn       = new QPushButton("ln",this);
    pushButtonXCubed   = new QPushButton(QString::fromUtf8("x\u00B3"),this);
    pushButtonTanh     = new QPushButton("tanh",this);
    pushButtonTan      = new QPushButton("tan",this);
    pushButtonLog      = new QPushButton("log",this);
    pushButtonXNed     = new QPushButton(QString::fromUtf8("x\u207F"),this);
    pushButtonFact     = new QPushButton("n!",this);
    pushButtonPi       = new QPushButton(QString::fromUtf8("\u03C0"),this);
    pushButtonCubeRoot = new QPushButton(QString::fromUtf8("\u00B3\u221A"),this);
    pushButtonNRoot    = new QPushButton(QString::fromUtf8("\u207F\u221A"),this);

    pushButtonSinh->setSizePolicy(    QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonSin->setSizePolicy(     QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonExp->setSizePolicy(     QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonXSq->setSizePolicy(     QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonCosh->setSizePolicy(    QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonCos->setSizePolicy(     QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonLn->setSizePolicy(      QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonXCubed->setSizePolicy(  QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonTanh->setSizePolicy(    QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonTan->setSizePolicy(     QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonLog->setSizePolicy(     QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonXNed->setSizePolicy(    QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonFact->setSizePolicy(    QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonPi->setSizePolicy(      QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonCubeRoot->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pushButtonNRoot->setSizePolicy(   QSizePolicy::Preferred, QSizePolicy::Preferred);

    complCalcLayout = new QGridLayout(this);
    complCalcLayout->setSpacing(0);
    complCalcLayout->setContentsMargins(0, 0, 0, 0);

    complCalcLayout->addWidget(pushButtonSinh,     0, 0, 1, 1);
    complCalcLayout->addWidget(pushButtonSin,      0, 1, 1, 1);
    complCalcLayout->addWidget(pushButtonExp,      0, 2, 1, 1);
    complCalcLayout->addWidget(pushButtonXSq,      0, 3, 1, 1);
    complCalcLayout->addWidget(pushButtonCosh,     1, 0, 1, 1);
    complCalcLayout->addWidget(pushButtonCos,      1, 1, 1, 1);
    complCalcLayout->addWidget(pushButtonLn,       1, 2, 1, 1);
    complCalcLayout->addWidget(pushButtonXCubed,   1, 3, 1, 1);
    complCalcLayout->addWidget(pushButtonTanh,     2, 0, 1, 1);
    complCalcLayout->addWidget(pushButtonTan,      2, 1, 1, 1);
    complCalcLayout->addWidget(pushButtonLog,      2, 2, 1, 1);
    complCalcLayout->addWidget(pushButtonXNed,     2, 3, 1, 1);
    complCalcLayout->addWidget(pushButtonFact,     3, 0, 1, 1);
    complCalcLayout->addWidget(pushButtonPi,       3, 1, 1, 1);
    complCalcLayout->addWidget(pushButtonCubeRoot, 3, 2, 1, 1);
    complCalcLayout->addWidget(pushButtonNRoot,    3, 3, 1, 1);


    complCalcWidget = new QWidget(this);
    complCalcWidget->setLayout(complCalcLayout);

    connect(pushButtonSin,      SIGNAL(clicked()), this, SLOT(UnFnClicked()));
    connect(pushButtonSinh,     SIGNAL(clicked()), this, SLOT(UnFnClicked()));
    connect(pushButtonCos,      SIGNAL(clicked()), this, SLOT(UnFnClicked()));
    connect(pushButtonCosh,     SIGNAL(clicked()), this, SLOT(UnFnClicked()));
    connect(pushButtonFact,     SIGNAL(clicked()), this, SLOT(UnFnClicked()));
    connect(pushButtonTan,      SIGNAL(clicked()), this, SLOT(UnFnClicked()));
    connect(pushButtonTanh,     SIGNAL(clicked()), this, SLOT(UnFnClicked()));
    connect(pushButtonLn,       SIGNAL(clicked()), this, SLOT(UnFnClicked()));
    connect(pushButtonLog,      SIGNAL(clicked()), this, SLOT(UnFnClicked()));
    connect(pushButtonXNed,     SIGNAL(clicked()), this, SLOT(BinFnClicked()));
    connect(pushButtonXSq,      SIGNAL(clicked()), this, SLOT(UnFnClicked()));
    connect(pushButtonXCubed,   SIGNAL(clicked()), this, SLOT(UnFnClicked()));
    connect(pushButtonCubeRoot, SIGNAL(clicked()), this, SLOT(UnFnClicked()));
    connect(pushButtonNRoot,    SIGNAL(clicked()), this, SLOT(BinFnClicked()));
    connect(pushButtonExp,      SIGNAL(clicked()), this, SLOT(UnFnClicked()));
    connect(pushButtonPi,       SIGNAL(clicked()), this, SLOT(NumberClicked()));

}

void MainWindow::CreateDefaultCalcWidget() {
    QPushButton* pushButtonClear =  new QPushButton(QString::fromUtf8("C"), this);

    QString StyleSheetLine = "QLineEdit {font: 26pt 'Microsoft YaHei UI';"
                             " qproperty-alignment: AlignRight;"
                             " padding: 5px;"
                             " border: none; background-color: #F2F2F2;}";

    lineEdit->setStyleSheet(StyleSheetLine);

    pushButtonClear->setSizePolicy(    QSizePolicy::Preferred, QSizePolicy::Preferred);

    defaultCalcLayout = new QGridLayout(this);
    defaultCalcLayout->setSpacing(0);
    defaultCalcLayout->setContentsMargins(0, 0, 0, 0);

    defaultCalcLayout->addWidget(lineEdit,          0, 0, 2, 5);
    defaultCalcLayout->addWidget(radioButtonSimple, 2, 0, 1, 3);
    defaultCalcLayout->addWidget(radioButtonCompl,  3, 0, 1, 3);
    defaultCalcLayout->addWidget(pushButtonClear,       2, 4, 2, 1);

    defaultCalcWidget = new QWidget(this);
    defaultCalcWidget->setLayout(defaultCalcLayout);

    connect(pushButtonClear,     SIGNAL(clicked()), this, SLOT(ClearInput()));
}

bool MainWindow::OnlyDigits() {
    return digits_only;
}

bool MainWindow::OneDot(bool b){
    dot_one = b;
}

void MainWindow::SetDigits(bool new_state) {
    digits_only = new_state;
}

void MainWindow::NumberClicked() {
    QString number = ((QPushButton*)sender())->text();
    if (number == "\u03C0") {
        constexpr double pi = 3.1415926535897932384626433832795;
        lineEdit->setText(lineEdit->text() + QString(std::to_string(pi).c_str()));
    }
    else
        lineEdit->setText(lineEdit->text() + number);
}

void MainWindow::DotClicked() {
    if(dot_one==true)
        return;
    OneDot(true);
    if (lineEdit->text().length()) {
        if (lineEdit->text().at(lineEdit->text().length() - 1) != SEPARATOR)
            lineEdit->setText(lineEdit->text() + SEPARATOR);
    } else
        lineEdit->setText("0" + SEPARATOR + lineEdit->text());
}

void MainWindow::BinFnClicked() {
    if (lineEdit->text().toStdString() == "")
        return;
    Equals();
     OneDot(false);
    if (OnlyDigits()) {
        QString symbol = ((QPushButton*)sender())->text();
        if (lineEdit->text().length()) {
            if (symbol == "x\u207F") // x^n
                lineEdit->setText(lineEdit->text() + ", x\u207F n = ");
            else if (symbol == "\u207F\u221A") // x^(1/n)
                lineEdit->setText(lineEdit->text() + ", \u207F\u221Ax n = ");
            else
                lineEdit->setText(lineEdit->text() + symbol);
            SetDigits(false);
        } else if (symbol == "-")
            lineEdit->setText(symbol + lineEdit->text());
    }
}

double fact(double N) {
    if (N < 0)
        return 0;
    if (N == 0.0)
        return 1;
    else
        return N * fact((int)floor(N) - 1);
}

void MainWindow::UnFnClicked() {
    if (lineEdit->text().toStdString() == "")
        return;
    Equals();
    SetDigits(true);
    std::string symbol = ((QPushButton*)sender())->text().toStdString();
    std::string expression = lineEdit->text().toStdString();
    double number = std::stod(expression);
    if (symbol == "\u221Ax") // sqrt
        number = std::sqrt(number);
    else if (symbol == "sin")
        number = std::sin(number);
    else if (symbol == "sinh")
        number = std::sinh(number);
    else if (symbol == "e\u207F") // exp
        number = std::exp(number);
    else if (symbol == "x\u00B2") // x^2
        number *= number;
    else if (symbol == "cosh")
        number = std::cosh(number);
    else if (symbol == "cos")
        number = std::cos(number);
    else if (symbol == "ln")
        number = std::log(number);
    else if (symbol == "\u00B3\u221A") // x^(1/3)
        number = std::cbrt(number);
    else if (symbol == "x\u00B3") // x^3
        number *= (number * number);
    else if (symbol == "tanh")
        number = std::tanh(number);
    else if (symbol == "tan")
        number = std::tan(number);
    else if (symbol == "\u00B1")
        number = -number;
    else if (symbol == "log")
        number = std::log10(number);
    else if (symbol == "n!") {
        if (std::floor(number) != number) {
            lineEdit->setText(QString("nan"));
            return;
        }
        else
            number = fact(number);
    }else if (symbol == "1/x"){
        number = 1 / number;
        expression = std::to_string(number);
        lineEdit->setText(QString(expression.c_str()));
    }
    expression = std::to_string(number);
    while (*(expression.rbegin()) == '0'){
        expression.pop_back();

    }
    if (*(expression.rbegin()) == SEPARATOR)
        expression.pop_back();
    lineEdit->setText(QString(expression.c_str()));
}

void MainWindow::ClearInput() {
    OneDot(false);
    lineEdit->clear();
    SetDigits(true);
}

void MainWindow::Equals() {
    SetDigits(true);
    std::string expression = lineEdit->text().toStdString();
    std::string search_slice = expression.substr(1);
    std::string answer = "";
    if (search_slice.find('+') != std::string::npos) {
        std::string::size_type position;
        double left_number  = std::stod(expression, &position);
        double right_number = std::stod(expression.substr(position + 1));
        double answer_number = left_number + right_number;
        answer = std::to_string(answer_number);
        lineEdit->setText(QString(answer.c_str()));
    } else if (search_slice.find('-') != std::string::npos) {
        std::string::size_type position;
        double left_number  = std::stod(expression, &position);
        double right_number = std::stod(expression.substr(position + 1));
        double answer_number = left_number - right_number;
        answer = std::to_string(answer_number);
        lineEdit->setText(QString(answer.c_str()));
    } else if (search_slice.find("\u00D7") != std::string::npos) { // *
        std::string::size_type position;
        double left_number  = std::stod(expression, &position);
        double right_number = std::stod(expression.substr(position + 2));
        double answer_number = left_number * right_number;
        answer = std::to_string(answer_number);
        lineEdit->setText(QString(answer.c_str()));
    } else if (search_slice.find("\u00F7") != std::string::npos) { // /
        std::string::size_type position;
        double left_number  = std::stod(expression, &position);
        double right_number = std::stod(expression.substr(position + 2));
        double answer_number = left_number / right_number;
        answer = std::to_string(answer_number);
        lineEdit->setText(QString(answer.c_str()));
    } else if (search_slice.find(", x\u207F n = ") != std::string::npos) { // x^n
        std::string::size_type position;
        double left_number  = std::stod(expression, &position);
        double right_number = std::stod(lineEdit->text().split(", x\u207F n = ")[1].toStdString());
        double answer_number = std::pow(left_number, right_number);
        answer = std::to_string(answer_number);
        lineEdit->setText(QString(answer.c_str()));
    } else if (search_slice.find(", \u207F\u221Ax n = ") != std::string::npos) { // x^(1/n)
        std::string::size_type position;
        double left_number  = std::stod(expression, &position);
        double right_number = std::stod(lineEdit->text().split(", \u207F\u221Ax n = ")[1].toStdString());
        double answer_number = std::pow(left_number, (1 / right_number));
        answer = std::to_string(answer_number);
        lineEdit->setText(QString(answer.c_str()));
    }
    bool fl=false;
    int i,c;
    for (i=0; answer[i]!='\0'; i++)
    if (answer[i]=='.') break;

    for (c=i+1; answer[c]!='\0'; c++)
    if (answer[c]!='0') fl=true;

    if (fl==true) OneDot(true);
    else OneDot(false);
}
