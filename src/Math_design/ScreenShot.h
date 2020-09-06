#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QWidget>
#include <QPixmap>
#include <QPoint>
#include <QtGui>
#include <QPainter>
#include <QBrush>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
class ScreenShot : public QWidget{

    Q_OBJECT

public:
    ScreenShot(); //构造函数
    enum shotState{initShot,beginShot,finishShot,endShot,beginMoveShot,finishMoveShot,beginControl,finishControl}; //截屏状态
    //移动选区中的8个控制点，按照顺时针方向从左上控制点到左中控制点分配编号为1～8
    enum controlPointEnum{moveControl0,moveControl1,moveControl2,moveControl3,moveControl4,moveControl5,moveControl6,moveControl7,moveControl8};
    QPixmap getShotPicture();   //获取全屏的Picture
    void setType(int);          //设置截屏所要的模式

public slots:
    void loadBackgroundPicture(const QPixmap &bgPicture);//加载背景Picture槽函数
    void loadBackgroundPicture(const QPixmap &bgPicture, int x, int y, int width, int height); //加载背景Picture槽函数，设置x,y,width,height
    void cancelSelectedRect();  //取消选择区域
    void savePicture();         //保选取行为的方法
    void addtoCo();
    void recognitionRequestFinished(QNetworkReply* reply);
    void getHtmlFinished(QNetworkReply*);
    signals:
        void finishPicture(const QPixmap &finishPicture); //完成切图后的图片,发送信号给连接者

private:
    //选区框的8个点选取
    QRect tlRect; //左上点
    QRect trRect; //右上点
    QRect blRect; //左下点
    QRect brRect; //右下点
    QRect tcRect; //上中点
    QRect bcRect; //下中点
    QRect lcRect;//左中点
    QRect rcRect; //右中点

    QStringList jsonList;
    QNetworkAccessManager *nam;

    int g_type; //自定义截屏模式

    QPainter painter;
    QPoint beginPoint,endPoint,moveBeginPoint,moveEndPoint;
    QRect selectedRect; //选择区域
    QPixmap loadPicture,shotPicture;
    shotState currentShotState; //当前的截屏状态
    controlPointEnum controlValue; //记录移动控制点的值
    QAction *acSave,*acSave1; //保存图片行为
    QAction *acCal; //取消选取行为
    QAction *quitAction; //退出选取行为
    QMenu *contextMenu; //选中区域右键菜单
    int screenwidth; //整个屏幕的宽度
    int screenheight; //整个屏幕的高度
    int screenx; //选区的X
    int screeny; //选区的Y
    int widthTip,heightTip,widthInfo,heightInfo;

    QRect getSelectedRect(); //获取选取
    QRect getRect(const QPoint &beginPoint, const QPoint &endPoint); //根据两个点获取选取坐标
    void initScreenShot(); //初始化抓全屏的相关参数
    bool isInSelectedRect(const QPoint &point); //判断该点是否在选中区域
    void menuSelect();//初始化右键菜单
    void drawTipsText(); //在屏幕上打印提示信息
    void drawSelectedPicture(void); //在屏幕上画选取的屏幕
    void updateBeginEndPointValue(const QRect &rect);  //当移动选取后，对beginPoint,endPoint坐标进行重新修改
    void checkMoveEndPoint(); //对移动的选区进行判断
    void draw8ControlPoint(const QRect &rect);
    void updateMouseShape(const QPoint &point); //更新鼠标的当前状态
    void updateMoveControlMouseShape(controlPointEnum controlValue);
    controlPointEnum getMoveControlState(const QPoint &point); //获取移动控制点状态
    QRect getMoveAllSelectedRect(void); //获取移动整个选中的选区
    QRect getMoveControlSelectedRect(void);//获取移动控制点的选区
    int getMinValue(int num1, int num2);//获取两个数中的最小值
    void drawXYWHInfo(void); //打印选取的x,y,h,w值信息

    void prepareGetHtml(QString url);
    bool g_htmlFinished;
    QString szHtmlInfo;

    //重写基类方法
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);


};

#endif
