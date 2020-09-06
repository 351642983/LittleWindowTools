#ifndef ENMIN_H
#define ENMIN_H
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
class Enmin:public QWidget
{
    Q_OBJECT
public:
    Enmin(QWidget *parent=0);
    ~Enmin();
private:
    QLabel *l1,*l2,*l3,*l4,*l5;
    QLineEdit *le1,*le2,*le3;
    QSlider *sb;
    QPushButton *pb1,*pb2,*pb3;
    QList<QFileInfo> *fileinfolist;


private slots:
    void changeLabel4(int);
    void openSelectDialog();
    void openSelectDialogDir();
    void openDownDir();
    void handlePicture();
    void handlePictureDir();
};

#endif // ENMIN_H
