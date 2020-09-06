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
    ScreenShot(); //���캯��
    enum shotState{initShot,beginShot,finishShot,endShot,beginMoveShot,finishMoveShot,beginControl,finishControl}; //����״̬
    //�ƶ�ѡ���е�8�����Ƶ㣬����˳ʱ�뷽������Ͽ��Ƶ㵽���п��Ƶ������Ϊ1��8
    enum controlPointEnum{moveControl0,moveControl1,moveControl2,moveControl3,moveControl4,moveControl5,moveControl6,moveControl7,moveControl8};
    QPixmap getShotPicture();   //��ȡȫ����Picture
    void setType(int);          //���ý�����Ҫ��ģʽ

public slots:
    void loadBackgroundPicture(const QPixmap &bgPicture);//���ر���Picture�ۺ���
    void loadBackgroundPicture(const QPixmap &bgPicture, int x, int y, int width, int height); //���ر���Picture�ۺ���������x,y,width,height
    void cancelSelectedRect();  //ȡ��ѡ������
    void savePicture();         //��ѡȡ��Ϊ�ķ���
    void addtoCo();
    void recognitionRequestFinished(QNetworkReply* reply);
    void getHtmlFinished(QNetworkReply*);
    signals:
        void finishPicture(const QPixmap &finishPicture); //�����ͼ���ͼƬ,�����źŸ�������

private:
    //ѡ�����8����ѡȡ
    QRect tlRect; //���ϵ�
    QRect trRect; //���ϵ�
    QRect blRect; //���µ�
    QRect brRect; //���µ�
    QRect tcRect; //���е�
    QRect bcRect; //���е�
    QRect lcRect;//���е�
    QRect rcRect; //���е�

    QStringList jsonList;
    QNetworkAccessManager *nam;

    int g_type; //�Զ������ģʽ

    QPainter painter;
    QPoint beginPoint,endPoint,moveBeginPoint,moveEndPoint;
    QRect selectedRect; //ѡ������
    QPixmap loadPicture,shotPicture;
    shotState currentShotState; //��ǰ�Ľ���״̬
    controlPointEnum controlValue; //��¼�ƶ����Ƶ��ֵ
    QAction *acSave,*acSave1; //����ͼƬ��Ϊ
    QAction *acCal; //ȡ��ѡȡ��Ϊ
    QAction *quitAction; //�˳�ѡȡ��Ϊ
    QMenu *contextMenu; //ѡ�������Ҽ��˵�
    int screenwidth; //������Ļ�Ŀ��
    int screenheight; //������Ļ�ĸ߶�
    int screenx; //ѡ����X
    int screeny; //ѡ����Y
    int widthTip,heightTip,widthInfo,heightInfo;

    QRect getSelectedRect(); //��ȡѡȡ
    QRect getRect(const QPoint &beginPoint, const QPoint &endPoint); //�����������ȡѡȡ����
    void initScreenShot(); //��ʼ��ץȫ������ز���
    bool isInSelectedRect(const QPoint &point); //�жϸõ��Ƿ���ѡ������
    void menuSelect();//��ʼ���Ҽ��˵�
    void drawTipsText(); //����Ļ�ϴ�ӡ��ʾ��Ϣ
    void drawSelectedPicture(void); //����Ļ�ϻ�ѡȡ����Ļ
    void updateBeginEndPointValue(const QRect &rect);  //���ƶ�ѡȡ�󣬶�beginPoint,endPoint������������޸�
    void checkMoveEndPoint(); //���ƶ���ѡ�������ж�
    void draw8ControlPoint(const QRect &rect);
    void updateMouseShape(const QPoint &point); //�������ĵ�ǰ״̬
    void updateMoveControlMouseShape(controlPointEnum controlValue);
    controlPointEnum getMoveControlState(const QPoint &point); //��ȡ�ƶ����Ƶ�״̬
    QRect getMoveAllSelectedRect(void); //��ȡ�ƶ�����ѡ�е�ѡ��
    QRect getMoveControlSelectedRect(void);//��ȡ�ƶ����Ƶ��ѡ��
    int getMinValue(int num1, int num2);//��ȡ�������е���Сֵ
    void drawXYWHInfo(void); //��ӡѡȡ��x,y,h,wֵ��Ϣ

    void prepareGetHtml(QString url);
    bool g_htmlFinished;
    QString szHtmlInfo;

    //��д���෽��
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);


};

#endif
