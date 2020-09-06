#include "Enmin.h"

Enmin::Enmin(QWidget *parent)
    :QWidget(parent)
{
    QVBoxLayout *mainLayout=new QVBoxLayout();

    QHBoxLayout *hlayout1=new QHBoxLayout();
    l1=new QLabel("ͼƬλ�ã�");
    le1=new QLineEdit();
    le1->setReadOnly(true);
    pb1=new QPushButton("ѡ��");
    hlayout1->addWidget(l1);
    hlayout1->addWidget(le1);
    hlayout1->addWidget(pb1);
    //����ǰ�ɷ�
    mainLayout->addLayout(hlayout1);

    QHBoxLayout *hlayout1_2=new QHBoxLayout();
    QLabel *l1_2=new QLabel("�ļ���λ�ã�");
    le3=new QLineEdit();
    le3->setReadOnly(true);
    QPushButton *pb1_2=new QPushButton("ѡ��");
    hlayout1_2->addWidget(l1_2);
    hlayout1_2->addWidget(le3);
    hlayout1_2->addWidget(pb1_2);
    //����ǰ�ɷ�
    mainLayout->addLayout(hlayout1_2);



    l2=new QLabel("ѹ����ͼƬ����·����");
    mainLayout->addWidget(l2);

    QHBoxLayout *hlayout2=new QHBoxLayout();
    le2=new QLineEdit();
    pb2=new QPushButton("ѡ��");
    hlayout2->addWidget(le2);
    hlayout2->addWidget(pb2);
    mainLayout->addLayout(hlayout2);

    QHBoxLayout *hlayout3=new QHBoxLayout();
    l3=new QLabel("ͼƬѹ��������");
    sb=new QSlider();
    sb->setFixedWidth(250);
    sb->setOrientation(Qt::Horizontal);//����ˮƽ����
    sb->setValue(50);
    sb->setRange(1,100);
    connect(sb, SIGNAL(valueChanged(int)), this, SLOT(changeLabel4(int)));
    l4=new QLabel("�е�");
    l4->setStyleSheet("color:blue");
    hlayout3->addWidget(l3);
    hlayout3->addWidget(sb);
    hlayout3->addWidget(l4);
    mainLayout->addLayout(hlayout3);

    QHBoxLayout *hlayout4=new QHBoxLayout();
    l5=new QLabel("(ͼƬԽ��ѹ����Ч��Խ����,̫С��һ��ѹ��)");
    hlayout4->addWidget(l5);
    mainLayout->addLayout(hlayout4);

    QHBoxLayout *hlayout5=new QHBoxLayout();
    pb3=new QPushButton("ѹ��ͼƬ");
    hlayout5->addStretch();
    QPushButton *pb4=new QPushButton("ѹ���ļ�����ͼƬ");
    hlayout5->addWidget(pb4);
    hlayout5->addStretch();
    hlayout5->addWidget(pb3);
    hlayout5->addStretch();
    mainLayout->addLayout(hlayout5);



    setLayout(mainLayout);

    setWindowTitle("ѹ��ͼƬ����");
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
    QString dir = QFileDialog::getExistingDirectory(this,tr("ѡ�����ѹ��ͼƬ�ļ���"),
                                                    le2->text(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
            if(dir.length() == 0) {
                    //ʵ�ֵ����Ĺ���QMessageBox::information(NULL, QString::fromUtf8("ע��"), QString::fromUtf8("��û��ѡ���κ��ļ���."));
            } else {
        //д��UTF-8���֣�����
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

    format=le2->text()+"//"+fi.completeBaseName()+"-ѹ��."+"jpg"/*+fi.suffix()*/;
    bool g_isSuccess=result.save(format, /*saveType.toStdString().c_str()*/"JPG", sb->value());
    if(g_isSuccess)
        QMessageBox::about(NULL, "��ʾ", "ѹ��ͼƬ�ɹ�");
    else QMessageBox::about(NULL, "��ʾ", "ѹ��ͼƬʧ��");
}
void Enmin::handlePictureDir()
{
    if(fileinfolist==NULL)
    {
        QMessageBox::about(NULL, "��ʾ", "�ļ���ѡ���Ϊ��,����ѹ��ͼƬ");
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

        format=fi.absolutePath()+"//"+fi.completeBaseName()+"-ѹ��."+"jpg"/*+fi.suffix()*/;
        if(!result.save(format, /*saveType.toStdString().c_str()*/"JPG", sb->value()))
        {
            g_isSuccess=false;
        }

    }
    if(g_isSuccess)
        QMessageBox::about(NULL, "��ʾ", "ѹ��ͼƬ�����ļ��ɹ�");
    else QMessageBox::about(NULL, "��ʾ", "ѹ��ͼƬʧ�ܻ򲿷�ʧ��");
}
void Enmin::openSelectDialog()
{
    QString path;
        path =QFileDialog::getOpenFileName(this,
                                              tr("ѡ��Ҫѹ����ͼ��"),
                                              le1->text(),
                                              tr("Images (*.png *.bmp *.tif *.jpg *.gif *.jpeg)"));
    if(path.length() == 0) {
                //QMessageBox::information(NULL, QString::fromUtf8("ע��"), QString::fromUtf8("��û��ѡ���κ��ļ�."));
        } else {
            le1->setText(path);
            QFileInfo fi( path );
            le2->setText(fi.path());
        }
}

void Enmin::openSelectDialogDir()
{
    QString path=QFileDialog::getExistingDirectory(NULL,tr("ѡ���ļ���"),le3->text(),QFileDialog::ShowDirsOnly);
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
        l4->setText("����");
        l4->setStyleSheet("color:red");
    }
    else if(value<66)
    {
        l4->setText("�е�");
        l4->setStyleSheet("color:blue");
    }
    else
    {
        l4->setText("�Ϻ�");
        l4->setStyleSheet("color:green");
    }
}
