#include "qipan.h"
#include "qizi.h"
#include <QMessageBox>

int c_ty[2]={1,0};
int score[2]={25,50};
int score_1[2]={10,8};
pWidget::pWidget(QWidget *parent):
    QWidget(parent),
    g_scene(new QGraphicsScene(this)),
    g_view(new gvc(g_scene, this))
{
    g_start=false;
    QVBoxLayout *vlayout=new QVBoxLayout();
    QHBoxLayout *hlayout_1=new QHBoxLayout();
    QHBoxLayout *hlayout_2=new QHBoxLayout();
    //QHBoxLayout *hlayout_3=new QHBoxLayout();
    start=new QPushButton("开始游戏");
    label_1=new QLabel("选择先后手：");
    label_2=new QLabel("选择你所要的图形：");
    label_3=new QLabel("选择你所要难度：");
    cbox_1=new QComboBox();
    cbox_2=new QComboBox();
    cbox_3=new QComboBox();
    cbox_1->addItem(QString("先手"));
    cbox_1->addItem(QString("后手"));
    cbox_2->addItem(QString("X形棋子"));
    cbox_2->addItem(QString("圆形棋子"));
    cbox_2->addItem(QString("特殊棋子"));
    cbox_3->addItem(QString("AI难度"));
    cbox_3->addItem(QString("高手难度"));
    cbox_3->addItem(QString("简易难度"));


    g_scene->setSceneRect(0,0,LENGTH+1,HIGH+1);
    g_view->setBackgroundBrush(QBrush((Qt::gray)));
    g_view->setRenderHint(QPainter::Antialiasing);   //设定反走样
//测试能否画出一个外框
//    g_scene->addLine(0, 0, LENGTH, 0);
//    g_scene->addLine(LENGTH, 0, LENGTH, HIGH);
//    g_scene->addLine(0, HIGH, LENGTH, HIGH);
//    g_scene->addLine(0, 0, 0, HIGH);
    for(int i=0;i<=LTIMES;i++)
        g_scene->addLine(0.0, i*(HIGH/HTIMES), LENGTH, i*(HIGH/HTIMES),QPen(Qt::black));
    for(int j=0;j<=HTIMES;j++)
        g_scene->addLine(j*(LENGTH/LTIMES), 0, j*(LENGTH/LTIMES),HIGH,QPen(Qt::black));
    setFixedSize(LENGTH+30,HIGH+80);
    setWindowTitle("井字棋");
    g_ok=false;

//测试是否能够画出一个棋子
//    qizi *qz=new qizi(2);
//    g_scene->addItem(qz);
//    qz->setPos(getPoint(1,1));
    vlayout->addWidget(g_view);
    hlayout_1->addStretch();
    hlayout_1->addWidget(start);
    hlayout_1->addStretch();
    vlayout->addLayout(hlayout_1);
    hlayout_2->addWidget(label_1);
    hlayout_2->addWidget(cbox_1);
    hlayout_2->addStretch();
    hlayout_2->addWidget(label_2);
    hlayout_2->addWidget(cbox_2);
    hlayout_2->addStretch();
    hlayout_2->addWidget(label_3);
    hlayout_2->addWidget(cbox_3);
    vlayout->addLayout(hlayout_2);
    setLayout(vlayout);

    connect(start,SIGNAL(clicked()),this,SLOT(gamestart()));
    connect(g_view,SIGNAL(changeAble()),this,SLOT(clickg()));
}

void pWidget::gamestart()
{
    //QMessageBox::about(NULL,QString("提醒"),QString("%1").arg(random_num(1,3)));
    if(!g_start)
    {
        g_start=true;
        start->setText("结束游戏");
        for(int i=0;i<LTIMES;i++)
        {
            for(int j=0;j<HTIMES;j++)
            {
                juzheng[i][j]=0;
            }
        }
        cbox_1->setEnabled(false);
        cbox_2->setEnabled(false);
        cbox_3->setEnabled(false);
        if(cbox_2->currentIndex()==2)
        {
            qizi::g_run=true;
            cbox_2->setCurrentIndex(0);
            cbox_2->setItemText(0,"特殊棋子");
        }
        else
        {
            qizi::g_run=false;
        }
        if(cbox_1->currentIndex()==1)
            diannaoplay();

    }
    else
    {
        gameover();
    }


}
void pWidget::diannaoplay()
{
    if(empty())
    {
        if(!g_start)
            return;
        int x,y;
        if(cbox_3->currentIndex()!=2)
            setSuitableAI(x,y);
        else getcXY(x,y);
        addqizi(x,y,c_ty[cbox_2->currentIndex()]);
        if(!empty())
            gameover();
//        int z=checkWin();
//        if(z!=0)
//        {
//            QMessageBox::about(NULL,QString("提醒"),QString(((z==cbox_2->currentIndex())?QString("玩家"):QString("电脑"))+"获得胜利"));
//            gameover();
//        }
    }
    else
    {
        gameover();
    }
}
void pWidget::getcXY(int &x,int &y)
{
    x=random_num(1,LTIMES);
    y=random_num(1,HTIMES);
    static int x1,y1;
    if(cbox_3->currentIndex()==0)
    {
        if((returnInt()==1&&juzheng[1][1])||returnInt()==2)
        {
            x=(random_num(1,2)==1)?1:HTIMES;
            y=(random_num(1,2)==1)?1:HTIMES;
            x1=x;
            y1=y;
        }
        else if(returnInt()==1)
        {
            x=2;
            y=2;
            return;
        }
        else if(returnInt()==0)
        {
            x=2;
            y=2;
            return;
        }
        else if(returnInt()==4)
        {
            if(!juzheng[x1-1][0])
            {
                x=x1;
                y=1;
                return;
            }
            else if(!juzheng[0][y1-1])
            {
                x=1;
                y=y1;
                return;
            }
        }
    }
    while(juzheng[x-1][y-1])
    {
        if(cbox_3->currentIndex()==0)
        {
            if(!((returnInt()==1&&juzheng[1][1])||returnInt()==2))
            {
                x=random_num(1,LTIMES);
                y=random_num(1,HTIMES);
                x1=x;
                y1=y;
            }
            else
            {
                x=(random_num(1,2)==1)?1:HTIMES;
                y=(random_num(1,2)==1)?1:HTIMES;
            }
        }
        else
        {
            x=random_num(1,LTIMES);
            y=random_num(1,HTIMES);
        }

    }
}
void pWidget::gameover()
{
    qizi::g_start1=0;
    QString s1;
    QMessageBox::about(NULL,QString("提醒"),s1.sprintf("结束游戏 \n玩家得分：%d\n电脑得分：%d",g_score[cbox_2->currentIndex()],g_score[c_ty[cbox_2->currentIndex()]]));
    if(qizi::g_run)
    {
        cbox_2->setItemText(0,"X形棋子");
        cbox_2->setCurrentIndex(2);
    }
    g_scene->clear();
    for(int i=0;i<LTIMES;i++)
    {
        for(int j=0;j<HTIMES;j++)
        {
            juzheng[i][j]=0;
        }
    }
    start->setText("开始游戏");
    for(int i=0;i<=LTIMES;i++)
        g_scene->addLine(0.0, i*(HIGH/HTIMES), LENGTH, i*(HIGH/HTIMES),QPen(Qt::black));
    for(int j=0;j<=HTIMES;j++)
        g_scene->addLine(j*(LENGTH/LTIMES), 0, j*(LENGTH/LTIMES),HIGH,QPen(Qt::black));
    g_start=false;
    cbox_1->setEnabled(true);
    cbox_2->setEnabled(true);
    cbox_3->setEnabled(true);

}

pWidget::~pWidget()
{
    delete g_scene;
    delete g_view;
    delete start;
    delete label_1;
    delete label_2;
    delete cbox_1;
    delete cbox_2;
}
QPointF pWidget::getPoint(int x, int y)
{
    return QPointF((LENGTH/LTIMES/2)+(x-1)*LENGTH/LTIMES,(HIGH/HTIMES/2)+(y-1)*HIGH/HTIMES);
}
//未知名bug
int pWidget::checkWin()
{
    int i,j,k;
    g_score[0]=0;
    g_score[1]=0;
    bool down=(cbox_2->currentIndex()==0);
    for(down?k=2:k=1;down?k>=1:k<=2;down?k--:k++)
    {
        for(i=0;i<LTIMES;i++)
        {
            bool g_test=false;
            int g_fen=0;
            for(j=0;j<HTIMES;j++)
            {

                if(juzheng[i][j]!=k)
                {
                    g_test=true;
                    break;
                }
                g_fen++;
                if(g_fen>=2)
                    g_score[k-1]+=score[k-1];
                else if(g_fen==1)
                    g_score[k-1]+=score_1[k-1];
            }
            if(!g_test)
                return k;
        }
        for(j=0;j<HTIMES;j++)
        {
            bool g_test=false;
            int g_fen=0;
            for(i=0;i<LTIMES;i++)
            {
                if(juzheng[i][j]!=k)
                {
                    g_test=true;
                    break;
                }
                g_fen++;
                if(g_fen>=2)
                    g_score[k-1]+=score[k-1];
                else if(g_fen==1)
                    g_score[k-1]+=score_1[k-1];
            }
            if(!g_test)
                return k;
        }
    }
    for(down?k=2:k=1;down?k>=1:k<=2;down?k--:k++)
    {
        bool g_test=false;
        int g_fen=0;
        for(i=0;i<LTIMES;i++)
        {
            if(juzheng[i][i]!=k)
            {
                g_test=true;
                break;
            }
            g_fen++;
            if(g_fen>=2)
                g_score[k-1]+=score[k-1];
            else if(g_fen==1)
                g_score[k-1]+=score_1[k-1];
        }
        if(!g_test)
            return k;
        g_test=false;
        for(i=0,j=LTIMES-1;i<LTIMES;i++,j--)
        {
            if(juzheng[i][j]!=k)
            {
                g_test=true;
                break;
            }
            g_fen++;
            if(g_fen>=2)
                g_score[k-1]+=score[k-1];
            else if(g_fen==1)
                g_score[k-1]+=score_1[k-1];
        }
        if(!g_test)
            return k;
    }
    return 0;
}

void pWidget::clickg()
{
    if(g_ok)
        return;
    if(g_start)
    {
        int x=0,y=0;
        getXY(g_view->x,g_view->y,x,y);
        if(empty())
        {
            if(!juzheng[x-1][y-1])
            {
                addqizi(x,y,cbox_2->currentIndex());
                if(g_start)
                    diannaoplay();
            }
        }
        else gameover();
    }

}
bool pWidget::empty()
{
    for(int i=0;i<LTIMES;i++)
    {
        for(int j=0;j<HTIMES;j++)
        {
            if(!juzheng[i][j])
            {
                return true;
            }
        }
    }
    return false;

}

void pWidget::addqizi(int x,int y,int ty)
{
    if(empty())
    {
        qizi *qz=new qizi(ty);
        g_scene->addItem(qz);
        qz->setPos(getPoint(x,y));
        juzheng[x-1][y-1]=ty+1;
        int z=checkWin();
        if(z!=0)
        {
            QMessageBox::about(NULL,QString("提醒"),QString(((z==cbox_2->currentIndex()+1)?QString("玩家"):QString("电脑"))+"获得胜利"));
            gameover();
        }
    }
    else gameover();
}

void pWidget::getXY(int s,int z,int &x, int &y)
{

    for(int j=1;j<=HTIMES;j++)
    {
        if(((j-1)*HIGH/HTIMES<z)&&(j*HIGH/HTIMES>z))
        {
            y=j;
            break;
        }
    }
    for(int i=1;i<=LTIMES;i++)
    {
        if(((i-1)*LENGTH/LTIMES<s)&&(i*LENGTH/LTIMES>s))
        {
            x=i;
            break;
        }
    }
}
int pWidget::returnInt()
{
    if(cbox_3->currentIndex()!=0)
        return -1;
    int g_count=0;
    for(int i=0;i<LTIMES;i++)
    {
        for(int j=0;j<HTIMES;j++)
        {
            if(juzheng[i][j])
               g_count++;
        }
    }
    return g_count;
}

void pWidget::setSuitableAI(int &x, int &y)
{
    int q=-1,k=-1,i,j;
    if(cbox_3->currentIndex()==0)   //进攻难度
    {
        for(i=0;i<LTIMES;i++)
        {
            int c=0;
            bool g_able=false;
            for(j=0;j<HTIMES;j++)
            {
                if(juzheng[i][j]==cbox_2->currentIndex()+1)
                {
                    if(!g_able)
                        g_able=false;
                    q=-1;
                    k=-1;
                    break;
                }
                else if(juzheng[i][j]==c_ty[cbox_2->currentIndex()]+1)
                {
                    if(!g_able)
                        g_able=false;
                    c++;
                }
                else if(!g_able)
                {
                    g_able=true;
                    q=i;
                    k=j;
                }
                else
                {
                    q=-1;
                    k=-1;
                    break;
                }
            }
            if(c==2&&g_able&&q!=-1&&k!=-1)
            {
                x=q+1;
                y=k+1;
                return;
            }
        }
        for(j=0;j<LTIMES;j++)
        {
            int c=0;
            bool g_able=false;
            for(i=0;i<HTIMES;i++)
            {
                if(juzheng[i][j]==cbox_2->currentIndex()+1)
                {
                    if(!g_able)
                        g_able=false;
                    q=-1;
                    k=-1;
                    break;
                }
                else if(juzheng[i][j]==c_ty[cbox_2->currentIndex()]+1)
                {
                    if(!g_able)
                        g_able=false;
                    c++;
                }
                else if(!g_able)
                {
                    g_able=true;
                    q=i;
                    k=j;
                }
                else
                {
                    q=-1;
                    k=-1;
                    break;
                }
            }
            if(c==2&&g_able&&q!=-1&&k!=-1)
            {
                x=q+1;
                y=k+1;
                return;
            }
        }
        int c=0;
        bool g_able=false;
        for(i=0;i<LTIMES;i++)
        {
            if(juzheng[i][i]==cbox_2->currentIndex()+1)
            {
                if(!g_able)
                    g_able=false;
                q=-1;
                k=-1;
                break;
            }
            else if(juzheng[i][i]==c_ty[cbox_2->currentIndex()]+1)
            {
                if(!g_able)
                    g_able=false;
                c++;
            }
            else if(!g_able)
            {
                g_able=true;
                q=i;
                k=i;
            }
            else
            {
                q=-1;
                k=-1;
                break;
            }
        }
        c=0;
        g_able=false;
        for(i=0,j=LTIMES-1;i<LTIMES;i++,j--)
        {
            if(juzheng[i][j]==cbox_2->currentIndex()+1)
            {
                if(!g_able)
                    g_able=false;
                q=-1;
                k=-1;
                break;
            }
            else if(juzheng[i][j]==c_ty[cbox_2->currentIndex()]+1)
            {
                if(!g_able)
                    g_able=false;
                c++;
            }
            else if(!g_able)
            {
                g_able=true;
                q=i;
                k=j;
            }
            else
            {
                q=-1;
                k=-1;
                break;
            }
        }
        if(c==2&&g_able&&q!=-1&&k!=-1)
        {
            x=q+1;
            y=k+1;
            return;
        }
    }
    //防守难度
    for(i=0;i<LTIMES;i++)
    {
        int c=0;
        bool g_able=false;
        for(j=0;j<HTIMES;j++)
        {
            if(juzheng[i][j]==c_ty[cbox_2->currentIndex()]+1)
            {
                if(!g_able)
                    g_able=false;
                q=-1;
                k=-1;
                break;
            }
            else if(juzheng[i][j]==cbox_2->currentIndex()+1)
            {
                if(!g_able)
                    g_able=false;
                c++;
            }
            else if(!g_able)
            {
                g_able=true;
                q=i;
                k=j;
            }
            else
            {
                q=-1;
                k=-1;
                break;
            }
        }
        if(c==2&&g_able&&q!=-1&&k!=-1)
        {
            x=q+1;
            y=k+1;
            return;
        }

    }

    for(j=0;j<LTIMES;j++)
    {
        int c=0;
        bool g_able=false;
        for(i=0;i<HTIMES;i++)
        {
            if(juzheng[i][j]==c_ty[cbox_2->currentIndex()]+1)
            {
                if(!g_able)
                    g_able=false;
                q=-1;
                k=-1;
                break;
            }
            else if(juzheng[i][j]==cbox_2->currentIndex()+1)
            {
                if(!g_able)
                    g_able=false;
                c++;
            }
            else if(!g_able)
            {
                g_able=true;
                q=i;
                k=j;
            }
            else
            {
                q=-1;
                k=-1;
                break;
            }
        }
        if(c==2&&g_able&&q!=-1&&k!=-1)
        {
            x=q+1;
            y=k+1;
            return;
        }
    }

    int c=0;
    bool g_able=false;

    if(c==2&&g_able&&q!=-1&&k!=-1)
    {
        x=q+1;
        y=k+1;
        return;
    }
    for(i=0;i<LTIMES;i++)
    {
        if(juzheng[i][i]==c_ty[cbox_2->currentIndex()]+1)
        {
            if(!g_able)
                g_able=false;
            q=-1;
            k=-1;
            break;
        }
        else if(juzheng[i][i]==cbox_2->currentIndex()+1)
        {
            if(!g_able)
                g_able=false;
            c++;
        }
        else if(!g_able)
        {
            g_able=true;
            q=i;
            k=i;
        }
        else
        {
            q=-1;
            k=-1;
            break;
        }
    }
    if(c==2&&g_able&&q!=-1&&k!=-1)
    {
        x=q+1;
        y=k+1;
        return;
    }
    c=0;
    g_able=false;
    for(i=0,j=LTIMES-1;i<LTIMES;i++,j--)
    {
        if(juzheng[i][j]==c_ty[cbox_2->currentIndex()]+1)
        {
            if(!g_able)
                g_able=false;
            q=-1;
            k=-1;
            break;
        }
        else if(juzheng[i][j]==cbox_2->currentIndex()+1)
        {
            if(!g_able)
                g_able=false;
            c++;
        }
        else if(!g_able)
        {
            g_able=true;
            q=i;
            k=j;
        }
        else
        {
            q=-1;
            k=-1;
            break;
        }
    }
    if(c==2&&g_able&&q!=-1&&k!=-1)
    {
        x=q+1;
        y=k+1;
        return;
    }
    if(q==-1&&k==-1)
        getcXY(x,y);
}

