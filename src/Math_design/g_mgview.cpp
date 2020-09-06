
#include "g_mgview.h"

QTime limitshow,onelimit,speedlimit;
bool g_allr[4]={false};
bool g_end=false;
int g_fps=0;
int z1=0,z=0;

g_mgview::g_mgview(QWidget *parent):
    QWidget(parent),
    g_scene(new QGraphicsScene(this)),
    g_view(new QGraphicsView(g_scene, this))
{
    timer=new QTimer;
    gw=new gamewidget;

    button[0]=new QPushButton(("生成迷宫路径"));
    button[1]=new QPushButton(("排行榜"));
    button[2]=new QPushButton(("返回对话框"));
    QHBoxLayout *hs[3];
    QVBoxLayout *v1[2];
    hs[0]=new QHBoxLayout;
    hs[1]=new QHBoxLayout;
    hs[2]=new QHBoxLayout;
    v1[0]=new QVBoxLayout;
    v1[1]=new QVBoxLayout;

    te=new QTextEdit;
    te->setReadOnly(true);
    word[0]=new QLabel(("输出信息框："));
    word[1]=new QLabel(("时间："));
    lcdnumber=new QLCDNumber;
    gm=new g_mgmath(1);
    showpath=false;
    g_thepathnum=0;

    hs[1]->addStretch();
    hs[1]->addWidget(button[0]);
    hs[1]->addStretch();
    hs[1]->addWidget(button[1]);
    hs[1]->addStretch();
    hs[1]->addWidget(button[2]);
    hs[1]->addStretch();
    v1[0]->addWidget(this);
    v1[0]->addLayout(hs[1]);
    hs[0]->addLayout(v1[0]);
    v1[1]->addWidget(word[0]);
    v1[1]->addWidget(te);
    hs[2]->addWidget(word[1]);
    hs[2]->addWidget(lcdnumber);
    v1[1]->addLayout(hs[2]);
    hs[0]->addLayout(v1[1]);


    connect(button[0],SIGNAL(clicked()),this,SLOT(recreate_mg()));
    connect(button[1],SIGNAL(clicked()),this,SLOT(openoption()));
    connect(button[2],SIGNAL(clicked()),this,SLOT(closePost()));


    g_scene->setSceneRect(0,0,800,600);
    g_view->setBackgroundBrush(QBrush((Qt::gray)));

    //test;;

    thefram.addRect(QRectF(QPointF(0,0),QPointF(800,0)));
    thefram.addRect(QRectF(QPointF(800,0),QPointF(800,600)));
    thefram.addRect(QRectF(QPointF(0,600),QPointF(800,600)));
    thefram.addRect(QRectF(QPointF(0,0),QPointF(0,600)));
    //矩阵建立
//    for(int z=0;z<4;z++)
//        wc[z]=new g_mgmath(2);
//    wc[0]->addLine(0, 0, 800, 0);
//    wc[1]->addLine(800, 0, 800, 600);
//    wc[2]->addLine(0, 600, 800, 600);
//    wc[3]->addLine(0, 0, 0, 600);
    g_scene->addLine(0, 0, 800, 0);
    g_scene->addLine(800, 0, 800, 600);
    g_scene->addLine(0, 600, 800, 600);
    g_scene->addLine(0, 0, 0, 600);
    int i[2],j[2];
    for(i[0]=0;i[0]<HEINUM-1;i[0]++)
    {
        for(j[0]=0;j[0]<LENNUM;j[0]++)
        {
            QPainterPath pp;
            pp.addRect(QRectF(QPointF((j[0])*LENTH+1.0,(i[0]+1)*LENTH),QPointF((j[0]+1)*LENTH-1.0,(i[0]+1)*LENTH)));
            alpath<<pp;
        }
    }
    QTime dieTime = QTime::currentTime().addMSecs(100);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    for(i[1]=0;i[1]<LENNUM-1;i[1]++)
    {
        for(j[1]=0;j[1]<HEINUM;j[1]++)
        {
            QPainterPath pp;
            pp.addRect(QRectF(QPointF((i[1]+1)*LENTH,j[1]*LENTH+1.0),QPointF((i[1]+1)*LENTH,(j[1]+1)*LENTH-1.0)));
            alpath<<pp;
        }
    }

    g_view->resize(840,640);
    g_view->show();
    setFixedSize(840,640);
    gw->setLayout(hs[0]);
    gw->setWindowTitle("迷宫算法");
    gw->setFixedSize(820+150,640+70);
    gw->show();

    for(int y=0;y<alpath.count();y++)
    {
        acheckp<<alpath.at(y);
    }


    g_scene->addLine(0, 0, 800, 0,QPen(Qt::black));
    for(int i=1;i<=600/LENTH;i++)
        g_scene->addLine(0.0, i*LENTH, 800, i*LENTH,QPen(Qt::black));
    g_scene->addLine(0, 0, 0, 600,QPen(Qt::black));
    for(int j=1;j<=800/LENTH;j++)
        g_scene->addLine(j*LENTH, 0, j*LENTH,600,QPen(Qt::black));


    connect(timer,SIGNAL(timeout()),this,SLOT(refresh()));

    timer->start();
    limitshow=QTime::currentTime();
    onelimit=QTime::currentTime();
    speedlimit=QTime::currentTime();
    timeRun=0;
    for(int u=0;u<3;u++)
        button[u]->setEnabled(false);
    QMessageBox::StandardButton rb = QMessageBox::question(NULL, "生成选择", "您是否想看迷宫的生成过程？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(rb == QMessageBox::Yes)
    {
           g_showcr=true;
    }
    else g_showcr=false;
    createmg();
    g_scene->addItem(gm);



}
g_mgview::~g_mgview()
{
//    delete []gk;
//    delete []gl;
//    delete []wc;
    delete gw;
    delete []word;
    delete te;
    delete gm;
    delete lcdnumber;
    delete []button;
    delete g_view;
    delete g_scene;
    delete timer;

}

void g_mgview::refresh()
{
    g_fps++;
    if(limitshow<QTime::currentTime())
    {
        limitshow=QTime::currentTime().addMSecs(300);
        te->setText(QString("Fps:%1\n").arg(g_fps*3.33));
        g_fps=0;
    }
    if(onelimit<QTime::currentTime())
    {
        setFocus();
        onelimit=QTime::currentTime().addSecs(1);
        lcdnumber->display(++timeRun);
    }
    if(speedlimit<QTime::currentTime())
    {
        speedlimit=QTime::currentTime().addMSecs(1000/MG_RUNFPS);
        if(inendPoint())
        {
            disconnect(timer,SIGNAL(timeout()),this,SLOT(refresh()));

            if(!showpath)
            {



                bool isOK;

                QString text = QInputDialog::getText(NULL, "游戏结束",
                                                     QString("你的最后得分是:%1\n请输入你的名字").arg(int(100000/(lcdnumber->value()))),
                                                     QLineEdit::Normal,
                                                     "",
                                                     &isOK);
                if(isOK)
                {

                    text.remove(" ");
                    ranks *s=new ranks;
                    s->showrank(2);
                    s->insertrank(text.toLatin1().data(),int(100000/(lcdnumber->value())),2);
                    delete s;
                    QProcess::startDetached(QCoreApplication::applicationFilePath().remove(QString("_")+QString(VERSION)), QStringList());
                    QTime dieTime = QTime::currentTime().addMSecs(500);
                    while( QTime::currentTime() < dieTime )
                        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
                    ranks *s1=new ranks;
                    s1->showrank(2);
                    s1->show();
                    s1->activateWindow();
                    gw->close();
                    close();
                }
                else
                {

                    QMessageBox::about(NULL, "迷宫排行榜", "已选择取消对该数据的上传");
                    QProcess::startDetached(QCoreApplication::applicationFilePath().remove(QString("_")+QString(VERSION)), QStringList());
                    exit(0);
                }

            }
            else
            {
                QMessageBox::about(NULL, "迷宫算法游戏结束", "由于生成了路径,已取消分数的上传");
                QProcess::startDetached(QCoreApplication::applicationFilePath().remove(QString("_")+QString(VERSION)), QStringList());
                exit(0);
            }

        }
        if(!isCotain())
        {
            gm->nextCarry();
        }
        else gm->backCarry();
    }




}

QPainterPath g_mgview::returnLine(int x,int y,int dirt)
{
    if(dirt==1)
    {
        return alpath.at((LENNUM*(y-2))+x-1);
    }
    else if(dirt==2)
    {
        return alpath.at((LENNUM*(HEINUM-1))+(x-1)*HEINUM+y-1);
    }
    else if(dirt==3)
    {
        return alpath.at((LENNUM*(y-1))+x-1);
    }
    else
    {
        return alpath.at((LENNUM*(HEINUM-1))+(x-2)*HEINUM+y-1);
    }
}
int g_mgview::changep(int x,int y,int dirt)
{
    if(dirt==1)
    {
        return ((LENNUM*(y-2))+x-1);
    }
    else if(dirt==2)
    {
        return ((LENNUM*(HEINUM-1))+(x-1)*HEINUM+y-1);
    }
    else if(dirt==3)
    {
        return ((LENNUM*(y-1))+x-1);
    }
    else
    {
        return ((LENNUM*(HEINUM-1))+(x-2)*HEINUM+y-1);
    }
}

bool g_mgview::isCotain()
{


    for(int z=0;z<acheckp.count();z++)
    {
        if(acheckp.at(z)==QPainterPath())
            continue;
        if(gm->collidesWithPath(acheckp.at(z)))
            return true;
    }


    if(gm->collidesWithPath(thefram))
         return true;

    return false;
}

void g_mgview::createmg()
{
    while(!gm->isrunover())
    {
        //取消注释可以看见迷宫的生成过程
        if(g_showcr)
        {
            QTime dieTime = QTime::currentTime().addMSecs(1);
            while( QTime::currentTime() < dieTime )
                QCoreApplication::processEvents(QEventLoop::AllEvents, 10);
        }
        nextStep();
    }
    if(gm->isrunover()&&!g_end)
    {

        for(int u=0;u<3;u++)
            button[u]->setEnabled(true);
        g_end=true;
        g_scene->addEllipse(gm->checkp.x()*LENTH-LENTH/2-LENTH/4,gm->checkp.y()*LENTH-LENTH/2-LENTH/4,LENTH/2,LENTH/2,QPen(Qt::blue),QBrush(Qt::green));
        theend.addEllipse(gm->checkp.x()*LENTH-LENTH/2,gm->checkp.y()*LENTH-LENTH/2,LENTH/2,LENTH/2);
        gm->turnp<<gm->checkp;
//        thepath<<gm->checkp;
//        for(int z=0;z<thepath.count()-1;z++)
//        {
//            g_scene->addLine(thepath.at(z).x()*LENTH-LENTH/2,thepath.at(z).y()*LENTH-LENTH/2,thepath.at(z+1).x()*LENTH-LENTH/2,thepath.at(z+1).y()*LENTH-LENTH/2,QPen(Qt::red));
//        }
    }

}
void g_mgview::nextStep()
{
    if(!gm->isrunover())
    {
        QList<int> thedirt=gm->thePointdirt(gm->checkp.x(),gm->checkp.y());
//        static int g_themodel=g_thepathnum;

        if(thedirt.first()!=0)
        {
//            if(g_themodel!=g_thepathnum)
//            {
//                g_themodel=g_thepathnum;
//                //thepath.clear();
//                thepath<<gm->checkp;
//            }
//            else
//            {
//                thepath<<gm->checkp;
//            }

            z=thedirt.at(gm->random_num(1,thedirt.count())-1);
            if(z1!=z)
            {
                gm->turnp<<gm->checkp;
                gm->haveTurnp->append(gm->checkp);

            }
            g_scene->addPath(returnLine(gm->checkp.x(),gm->checkp.y(),z),QPen(Qt::gray));
            //信息可以储存
            //位置,方向？如何判断可走？x,y z;两点？两点判断函数233
            //删除条件？黑名单法，这个格子的位置都全部都被使用了。
            //搜索条件：哪个位置多找哪个。方向优先
            //删除：两点间颜色，路径储存点删除。
            acheckp.replace(changep(gm->checkp.x(),gm->checkp.y(),z),QPainterPath());
            if(z==1)
            {
                if(!gm->isHaveExist(gm->checkp.x(),gm->checkp.y()))
                    gm->addHaveXY(gm->checkp.x(),gm->checkp.y());
                gm->InsetHaveDirt(gm->checkp.x(),gm->checkp.y(),1);
                if(!gm->isHaveExist(gm->checkp.x(),gm->checkp.y()-1))
                    gm->addHaveXY(gm->checkp.x(),gm->checkp.y()-1);
                gm->InsetHaveDirt(gm->checkp.x(),gm->checkp.y()-1,3);

                gm->checkp.ry()-=1;
                gm->g_check[gm->checkp.x()-1][gm->checkp.y()-1]=true;


            }
            else if(z==2)
            {
                if(!gm->isHaveExist(gm->checkp.x(),gm->checkp.y()))
                    gm->addHaveXY(gm->checkp.x(),gm->checkp.y());
                gm->InsetHaveDirt(gm->checkp.x(),gm->checkp.y(),2);
                if(!gm->isHaveExist(gm->checkp.x()+1,gm->checkp.y()))
                    gm->addHaveXY(gm->checkp.x()+1,gm->checkp.y());
                gm->InsetHaveDirt(gm->checkp.x()+1,gm->checkp.y(),4);
                gm->checkp.rx()+=1;
                gm->g_check[gm->checkp.x()-1][gm->checkp.y()-1]=true;

            }
            else if(z==3)
            {

                if(!gm->isHaveExist(gm->checkp.x(),gm->checkp.y()))
                    gm->addHaveXY(gm->checkp.x(),gm->checkp.y());
                gm->InsetHaveDirt(gm->checkp.x(),gm->checkp.y(),3);
                if(!gm->isHaveExist(gm->checkp.x(),gm->checkp.y()+1))
                    gm->addHaveXY(gm->checkp.x(),gm->checkp.y()+1);
                gm->InsetHaveDirt(gm->checkp.x(),gm->checkp.y()+1,1);
                gm->checkp.ry()+=1;
                gm->g_check[gm->checkp.x()-1][gm->checkp.y()-1]=true;
            }
            else if(z==4)
            {
                if(!gm->isHaveExist(gm->checkp.x(),gm->checkp.y()))
                    gm->addHaveXY(gm->checkp.x(),gm->checkp.y());
                gm->InsetHaveDirt(gm->checkp.x(),gm->checkp.y(),4);
                if(!gm->isHaveExist(gm->checkp.x()-1,gm->checkp.y()))
                    gm->addHaveXY(gm->checkp.x()-1,gm->checkp.y());
                gm->InsetHaveDirt(gm->checkp.x()-1,gm->checkp.y(),2);

                gm->checkp.rx()-=1;
                gm->g_check[gm->checkp.x()-1][gm->checkp.y()-1]=true;

            }
            z1=z;

        }
        else if(!g_end)
        {
            //if(gm->thePointdirt(gm->turnp.first().x(),gm->turnp.first().y()).first()==0)
            if(gm->thePointdirt(gm->turnp.at(g_thepathnum).x(),gm->turnp.at(g_thepathnum).y()).first()==0)
            {
//                    thepath<<gm->turnp.last();
                g_thepathnum+=1;
                //gm->turnp.takeFirst();
            }
            else
            {
                //gm->checkp=gm->turnp.first();

                gm->checkp=gm->turnp.at(g_thepathnum);
            }

        }


    }
    else if(!g_end)
    {
        g_end=true;
        g_scene->addEllipse(gm->checkp.x(),gm->checkp.y(),LENTH/2,LENTH/2,QPen(Qt::blue));
        theend.addEllipse(gm->checkp.x(),gm->checkp.y(),LENTH/2,LENTH/2);
//        gm->getFinalPoint()->setX(gm->checkp.x());
//        gm->getFinalPoint()->setY(gm->checkp.y());
        gm->setTheFinalPoint(gm->checkp.x(),gm->checkp.y());

        gm->addHaveXY(gm->checkp.x(),gm->checkp.y());
        gm->InsetHaveDirt(gm->checkp.x(),gm->checkp.y(),z1);
        thepath<<QPoint(gm->checkp.x(),gm->checkp.y());
        //gm->turnp<<gm->checkp;

    }
}
bool g_mgview::inendPoint()
{
    if(gm->collidesWithPath(theend))
        return true;
    return false;
}
//一开始想要实现重绘功能,但由于比较麻烦,时间较紧张,就换成了设置到终点旁边的位置,而且下面两个函数名都未换
void g_mgview::recreate_mg()
{
//    g_scene->clear();
    //测试
    //nextStep();


    if(!showpath)
    {

        QMessageBox::StandardButton rb = QMessageBox::question(NULL, "提醒", "你确定要生成迷宫路径吗,生成后将不把排名计入排行榜中", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(rb == QMessageBox::Yes)
        {
            showpath=true;

//            gm->pos.setX(gm->turnp.at(gm->turnp.length()-2).x()*LENTH-LENTH/2);
//            gm->pos.setY(gm->turnp.at(gm->turnp.length()-2).y()*LENTH-LENTH/2);
            //drawlTor(gm->turnp.first(),gm->checkp);

            showFinalPath();



        }
    }
    else
    {
        QMessageBox::about(NULL, "迷宫", "路径已经生成，无需继续点击");
    }

    gm->update();
    setFocus();
}

void g_mgview::showFinalPath()
{
    lastPoint=new QPoint();
    Tempturn=new QList<QPoint>();
    haveUsed=new QList<QPoint>();
    haveUsed->append(QPoint(1,1));
    gm->haveCheckp->setX(1);
    gm->haveCheckp->setY(1);


    findNextStep();

}
int changeDiretion[5]=
{
    0,
    3,
    4,
    1,
    2
};
void g_mgview::findNextStep()
{
    QTime dieTime = QTime::currentTime().addMSecs(10);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 10);
    static int z1=0;
    int diret=0;
    if(gm->checkp.x()!=gm->haveCheckp->rx()||gm->checkp.y()!=gm->haveCheckp->ry())
    {
        int num=gm->getHaveDirt(gm->haveCheckp->x(),gm->haveCheckp->y())->size();
        diret=gm->getHaveDiretion(gm->haveCheckp->x(),gm->haveCheckp->y());
        QPoint init=returnDirtPoint(gm->haveCheckp->x(),gm->haveCheckp->y(),z1);

        if((gm->getHaveDirt(gm->haveCheckp->x(),gm->haveCheckp->y())->size()>0)&&gm->getHaveDirt(gm->haveCheckp->x(),gm->haveCheckp->y())->contains(z1)&&!containHaveUsed(init.x(),init.y()))
        {
            diret=z1;
            init=returnDirtPoint(gm->haveCheckp->x(),gm->haveCheckp->y(),z1);
        }
        if(containHaveUsed(init.x(),init.y()))
        {

            QList<int> tempList=*gm->getHaveDirt(gm->haveCheckp->rx(),gm->haveCheckp->ry());
            foreach(int it1,tempList)
            {
                QPoint rTemp=returnDirtPoint(gm->haveCheckp->x(),gm->haveCheckp->y(),it1);
                if(!containHaveUsed(rTemp.x(),rTemp.y()))
                {
                    init=rTemp;
                    diret=it1;
                    break;
                }
            }
        }

        if(diret!=0)
        {

            init=returnDirtPoint(gm->haveCheckp->x(),gm->haveCheckp->y(),diret);
            if(!containHaveUsed(init.x(),init.y()))
                haveUsed->append(QPoint(init.x(),init.y()));
            if(num==1)
            {
                drawlTor(*gm->haveCheckp,init,QPen(Qt::gray));
            }
            else
            {
                drawlTor(*gm->haveCheckp,init,QPen(Qt::red));
            }
//            QString info="";
//            for(int i=0;i<num;i++)
//                info.sprintf("%s %d",info.toStdString().c_str(),gm->getHaveDirt(gm->haveCheckp->x(),gm->haveCheckp->y())->at(i));
//            info.sprintf("%s 大小：%d",info.toStdString().c_str(),gm->getHaveDirtList()->size());
//            QMessageBox::about(NULL, "迷宫", info);

            gm->removeHaveDirt(gm->haveCheckp->x(),gm->haveCheckp->y(),diret);
            //QPoint pTemp=returnDirtPoint(gm->haveCheckp->x(),gm->haveCheckp->y(),diret);
            gm->setHaveCheckp(diret);
            //gm->removeHaveDirt(pTemp.x(),pTemp.y(),changeDiretion[diret]);
        }
        findNextStep();
    }
    z1=diret;
}

QPoint g_mgview::returnDirtPoint(int x,int y,int z)
{
    if(z==1)
    {
        return QPoint(x,y-1);
    }
    else if(z==2)
    {
        return QPoint(x+1,y);
    }
    else if(z==3)
    {
        return QPoint(x,y+1);
    }
    else if(z==4)
    {
        return QPoint(x-1,y);
    }
    return QPoint(x,y);
}

bool g_mgview::containTempTurn(int x,int y)
{
    foreach(QPoint it,*Tempturn)
    {
        if(it.rx()==x&&it.ry()==y)
        {
            return true;
        }
    }
    return false;
}

void g_mgview::drawlTor(QPoint x,QPoint y,QPen c)
{
    g_scene->addLine(x.x()*LENTH-LENTH/2,x.y()*LENTH-LENTH/2,y.x()*LENTH-LENTH/2,y.y()*LENTH-LENTH/2,c);
}

void g_mgview::openoption()
{
    ranks *s1=new ranks;
    s1->showrank(2);
    s1->show();
    setFocus();

}

void g_mgview::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_W)
    {
        gm->currentDirt=UPMOVE;
        gm->lastDirt=UPMOVE;
        g_allr[0]=true;
    }
    else if(event->key()==Qt::Key_D)
    {
        gm->currentDirt=RIGHTMOVE;
        gm->lastDirt=RIGHTMOVE;
        g_allr[1]=true;
    }
    else if(event->key()==Qt::Key_S)
    {
        gm->currentDirt=DOWNMOVE;
        gm->lastDirt=DOWNMOVE;
        g_allr[2]=true;
    }
    else if(event->key()==Qt::Key_A)
    {
        gm->currentDirt=LEFTMOVE;
        gm->lastDirt=LEFTMOVE;
        g_allr[3]=true;
    }

}
void g_mgview::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_W)
    {
        g_allr[0]=false;
    }
    else if(event->key()==Qt::Key_D)
    {
        g_allr[1]=false;
    }
    else if(event->key()==Qt::Key_S)
    {
        g_allr[2]=false;
    }
    else if(event->key()==Qt::Key_A)
    {
        g_allr[3]=false;
    }
    if(!g_allr[0]&&!g_allr[1]&&!g_allr[2]&&!g_allr[3])
    {
        gm->currentDirt=NOMOVE;
    }

}

void g_mgview::closePost()
{
    QProcess::startDetached(QCoreApplication::applicationFilePath().remove(QString("_")+QString(VERSION)), QStringList());
    exit(0);
}
