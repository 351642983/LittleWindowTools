#include "Enmin.h"

Enmin::Enmin(QWidget *parent)
    :QWidget(parent)
{
    QVBoxLayout *mainLayout=new QVBoxLayout();

    QHBoxLayout *hlayout1=new QHBoxLayout();
    l1=new QLabel("图片位置：");
    le1=new QLineEdit();
    le1->setReadOnly(true);
    pb1=new QPushButton("选择");
    hlayout1->addWidget(l1);
    hlayout1->addWidget(le1);
    hlayout1->addWidget(pb1);
    //测试前可否
    mainLayout->addLayout(hlayout1);

    QHBoxLayout *hlayout1_2=new QHBoxLayout();
    QLabel *l1_2=new QLabel("文件夹位置：");
    le3=new QLineEdit();
    le3->setReadOnly(true);
    QPushButton *pb1_2=new QPushButton("选择");
    hlayout1_2->addWidget(l1_2);
    hlayout1_2->addWidget(le3);
    hlayout1_2->addWidget(pb1_2);
    //测试前可否
    mainLayout->addLayout(hlayout1_2);



    l2=new QLabel("压缩后图片保存路径：");
    mainLayout->addWidget(l2);

    QHBoxLayout *hlayout2=new QHBoxLayout();
    le2=new QLineEdit();
    pb2=new QPushButton("选择");
    hlayout2->addWidget(le2);
    hlayout2->addWidget(pb2);
    mainLayout->addLayout(hlayout2);

    QHBoxLayout *hlayout3=new QHBoxLayout();
    l3=new QLabel("图片压缩质量：");
    sb=new QSlider();
    sb->setFixedWidth(250);
    sb->setOrientation(Qt::Horizontal);//设置水平方向
    sb->setValue(50);
    sb->setRange(1,100);
    connect(sb, SIGNAL(valueChanged(int)), this, SLOT(changeLabel4(int)));
    l4=new QLabel("中等");
    l4->setStyleSheet("color:blue");
    hlayout3->addWidget(l3);
    hlayout3->addWidget(sb);
    hlayout3->addWidget(l4);
    mainLayout->addLayout(hlayout3);

    QHBoxLayout *hlayout4=new QHBoxLayout();
    l5=new QLabel("(图片越大压缩的效果越明显,太小则不一定压缩)");
    hlayout4->addWidget(l5);
    mainLayout->addLayout(hlayout4);

    QHBoxLayout *hlayout5=new QHBoxLayout();
    pb3=new QPushButton("压缩图片");
    hlayout5->addStretch();
    QPushButton *pb4=new QPushButton("压缩文件夹中图片");
    hlayout5->addWidget(pb4);
    hlayout5->addStretch();
    hlayout5->addWidget(pb3);
    hlayout5->addStretch();
    mainLayout->addLayout(hlayout5);



    setLayout(mainLayout);

    setWindowTitle("压缩图片工具");
    setFixedSize(400,200);
    setWindowFlags(Qt::WindowCloseButtonHint);

    connect(pb1,SIGNAL(clicked()),this,SLOT(openSelectDialog()));
    connect(pb1_2,SIGNAL(clicked()),this,SLOT(openSelectDialogDir()));
    connect(pb2,SIGNAL(clicked()),this,SLOT(openDownDir()));
    connect(pb3,SIGNAL(clicked()),this,SLOT(handlePicture()));
    connect(pb4,SIGNAL(clicked()),this,SLOT(handlePictureDir()));

}
Enmin::~Enmin()
{



}
void Enmin::openDownDir()
{
    QString dir = QFileDialog::getExistingDirectory(this,tr("选择放置压缩图片文件夹"),
                                                    le2->text(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
            if(dir.length() == 0) {
                    //实现弹窗的功能QMessageBox::information(NULL, QString::fromUtf8("注意"), QString::fromUtf8("你没有选择任何文件夹."));
            } else {
        //写入UTF-8文字，编码
                    le2->setText(dir);

            }
}
void Enmin::handlePicture()
{
    QFileInfo fi(le1->text());

    QString format;
    QString saveType;
    if(fi.suffix()==".jpg")
        saveType="JPG";
    else if(fi.suffix()==".png")
        saveType="PNG";
    else if(fi.suffix()==".bmp")
        saveType="BMP";
    else if(fi.suffix()==".tif")
        saveType="TIFF";
    else if(fi.suffix()==".gif")
        saveType="GIF";

    QImage result;
    result.load(le1->text(),saveType.toStdString().c_str());

    format=le2->text()+"//"+fi.completeBaseName()+"-压缩."+"jpg"/*+fi.suffix()*/;
    bool g_isSuccess=result.save(format, /*saveType.toStdString().c_str()*/"JPG", sb->value());
    if(g_isSuccess)
        QMessageBox::about(NULL, "提示", "压缩图片成功");
    else QMessageBox::about(NULL, "提示", "压缩图片失败");
}
void Enmin::handlePictureDir()
{
    if(fileinfolist==NULL)
    {
        QMessageBox::about(NULL, "提示", "文件夹选择框为空,不能压缩图片");
        return;
    }
    bool g_isSuccess=true;
    foreach(QFileInfo fi,*fileinfolist)
    {

        QString format;
        QString saveType;
        if(fi.suffix()==".jpg")
            saveType="JPG";
        else if(fi.suffix()==".png")
            saveType="PNG";
        else if(fi.suffix()==".bmp")
            saveType="BMP";
        else if(fi.suffix()==".tif")
            saveType="TIFF";
        else if(fi.suffix()==".gif")
            saveType="GIF";

        QImage result;
        result.load(fi.absoluteFilePath(),saveType.toStdString().c_str());

        format=fi.absolutePath()+"//"+fi.completeBaseName()+"-压缩."+"jpg"/*+fi.suffix()*/;
        if(!result.save(format, /*saveType.toStdString().c_str()*/"JPG", sb->value()))
        {
            g_isSuccess=false;
        }

    }
    if(g_isSuccess)
        QMessageBox::about(NULL, "提示", "压缩图片所有文件成功");
    else QMessageBox::about(NULL, "提示", "压缩图片失败或部分失败");
}
void Enmin::openSelectDialog()
{
    QString path;
        path =QFileDialog::getOpenFileName(this,
                                              tr("选择要压缩的图像"),
                                              le1->text(),
                                              tr("Images (*.png *.bmp *.tif *.jpg *.gif *.jpeg)"));
    if(path.length() == 0) {
                //QMessageBox::information(NULL, QString::fromUtf8("注意"), QString::fromUtf8("你没有选择任何文件."));
        } else {
            le1->setText(path);
            QFileInfo fi( path );
            le2->setText(fi.path());
        }
}

void Enmin::openSelectDialogDir()
{
    QString path=QFileDialog::getExistingDirectory(NULL,tr("选择文件夹"),le3->text(),QFileDialog::ShowDirsOnly);
    QDir *dir=new QDir(path);
    QStringList filter;
    filter<<"*.jpg"<<"*.jpeg"<<".png"<<".bmp"<<".tif"<<".gif";
    dir->setNameFilters(filter);
    fileinfolist=new QList<QFileInfo>(dir->entryInfoList(filter));
    le3->setText(path);
}
void Enmin::changeLabel4(int value)
{
    if(value<33)
    {
        l4->setText("极差");
        l4->setStyleSheet("color:red");
    }
    else if(value<66)
    {
        l4->setText("中等");
        l4->setStyleSheet("color:blue");
    }
    else
    {
        l4->setText("较好");
        l4->setStyleSheet("color:green");
    }
}
