#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#if QT_VERSION >= 0x050000
#include <QtWidgets> /* tous les widgets de Qt5 */
#else
#include <QtGui> /* tous les widgets de Qt4 */
#endif
#include <QSerialPort>
#include <QSerialPortInfo>

class MainWindow : public QWidget
{
    Q_OBJECT
    // public member
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // private member
private:
   // QSerialPortInfo *sPortInfo;

    // 1. Point widgets
    QLabel      *connectPortLabel;
    QLabel      *speedPortLabel;
    QComboBox   *connectPortSelect;
    QComboBox   *speedPortSelect;
    QPushButton *ledPushon;
    QPushButton *ledPushoff;
    QPushButton *bconnect;
    QPushButton *bdisconnect;
    QSerialPort *spPort;
    // 2. Customize widgets

    // 3. Point layout
    // 4. Put widget on layout
    // 5. Connect signals and slots
 private slots:
    void getConnect();
    void getDisconnect();
    void ledCommandOn();
    void ledCommandOff();
    // 6. customize window

    // 7. Define slots
    // 8. Define class method
};

#endif // MAINWINDOW_H
