#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    // set widgets
    connectPortLabel = new QLabel(this);
    speedPortLabel = new QLabel(this);
    connectPortSelect = new QComboBox(this);
    speedPortSelect = new QComboBox(this);
    ledPushon = new QPushButton(QString::fromUtf8("Activate Led"), this);
    ledPushoff = new QPushButton(QString::fromUtf8("DeActivate Led"), this);
    bconnect = new QPushButton(QString::fromUtf8("Connect"),this);
    bdisconnect = new QPushButton(QString::fromUtf8("Disconnect"), this);
    auto serialPortInfos = QSerialPortInfo::availablePorts();

    //customize widgets
    QFont font("Liberation Sans", 12, QFont::Bold);
    connectPortLabel->setText(QString::fromUtf8("Connection port:"));
    speedPortLabel->setText(QString::fromUtf8("Connection speed: "));
    connectPortSelect->setFont(font);
    for(const QSerialPortInfo &serialPortInfo : serialPortInfos){
        QStringList list;
        list << serialPortInfo.portName();
        connectPortSelect->addItem(serialPortInfo.portName());
    }
    //connectPortSelect->setEditable(true);
    speedPortSelect->setFont(font);
    speedPortSelect->addItem(QString::fromUtf8("9600"));
    speedPortSelect->addItem(QString::fromUtf8("19200"));
    speedPortSelect->addItem(QString::fromUtf8("57600"));
    speedPortSelect->addItem(QString::fromUtf8("115200"));

    //layout
    QHBoxLayout *hlayout1 = new QHBoxLayout;
    QHBoxLayout *hlayout2 = new QHBoxLayout;
    QHBoxLayout *hlayout3 = new QHBoxLayout;
    QHBoxLayout *hlayout4 = new QHBoxLayout;
    QVBoxLayout *vlayout1 = new QVBoxLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout;

    //set widget on layout
    hlayout1->addWidget(connectPortLabel);
    hlayout1->addWidget(connectPortSelect);
    hlayout2->addWidget(speedPortLabel);
    hlayout2->addWidget(speedPortSelect);
    hlayout3->addWidget(bconnect);
    hlayout3->addWidget(bdisconnect);
    vlayout1->addLayout(hlayout1);
    vlayout1->addLayout(hlayout2);
    vlayout1->addLayout(hlayout3);

    hlayout4->addWidget(ledPushon);
    hlayout4->addWidget(ledPushoff);

    mainLayout->addLayout(vlayout1);
    mainLayout->addLayout(hlayout4);
    setLayout(mainLayout);

    // connect signals and slots
    connect(bconnect, SIGNAL(clicked()), this, SLOT(getConnect()));
    connect(bdisconnect, SIGNAL(clicked()), this, SLOT(getDisconnect()));
    connect(ledPushon, SIGNAL(clicked()), this, SLOT(ledCommandOn()));
    connect(ledPushoff, SIGNAL(clicked()), this, SLOT(ledCommandOff()));

    // set window
    setWindowTitle(QString::fromUtf8("ArduCo - Soft"));
    adjustSize();

    //serialport
    spPort = new QSerialPort(this);

}

MainWindow::~MainWindow()
{

}

void MainWindow::getConnect(){
    //QString name;
    //name = connectPortSelect->currentText();
    spPort->setBaudRate(speedPortSelect->currentText().toInt());
    spPort->setPortName(connectPortSelect->currentText());
    if(spPort->open(QIODevice::ReadWrite)){
        bconnect->setText("connected");
    } else {
        QMessageBox::critical(this, tr("Error"), spPort->errorString());
    }

}

void MainWindow::getDisconnect(){
    if(spPort->isOpen())
        spPort->close();
    bconnect->setText("connect");

}

void MainWindow::ledCommandOn(){
        spPort->write("H");
}

void MainWindow::ledCommandOff(){
        spPort->write("L");
}
