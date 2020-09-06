
#include <QWidget>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QTime>

class CPUTest:public QWidget
{
    Q_OBJECT
public:
    CPUTest(QWidget *parent=0);
    ~CPUTest();
private:
    QTextEdit *te;
    QLabel *lb;
    QPushButton *pb;
    QTime acumulate;


    void FinishMath();
private slots:
    void startTestCPU();
};

