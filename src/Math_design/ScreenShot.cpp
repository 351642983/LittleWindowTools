#include "ScreenShot.h"
#include "windows.h"
#include <QImage>
#include <shlobj.h>
#include <string.h>
#include <cstring>
#include <QHostInfo>

QStringList getInitJson(QStringList json,QString init,int g_type)
{
    QStringList list;

    if(g_type==1)
    {
        int j=0;
        while(j<json.length())
        {
            if(json.at(j).at(json.at(j).length()-1)=='\\')
            {
                QString it=(json.at(j)+"\""+json.at(j+1));
                json.replace(j,it);
                json.removeAt(j+1);
            }
            else j++;
        }
    }



    for(int i=0;i<json.length();i++)
    {
        if(json.at(i)==init)
        {
           list<<json.at(i+2);
        }
    }
    return list;
}
//BOOL CopyToClipboard(const char* pszData, const int nDataLen)
//{
//    if(::OpenClipboard(NULL))
//    {
//        ::EmptyClipboard();
//        HGLOBAL clipbuffer;
//        char *buffer;
//        clipbuffer = ::GlobalAlloc(GMEM_DDESHARE, nDataLen+1);
//        buffer = (char *)::GlobalLock(clipbuffer);
//        strcpy(buffer, pszData);
//        ::GlobalUnlock(clipbuffer);
//        ::SetClipboardData(CF_TEXT, clipbuffer);
//        ::CloseClipboard();
//        return TRUE;
//    }
//    return FALSE;
//}
//BOOL CopyTextToClipBoard(LPCTSTR szStringData)
//{
//  BOOL bRet = FALSE;

//  size_t tBytesLen = (_tcslen(szStringData) + 1)  * sizeof(TCHAR); //�����ֽڳ���
//  LPTSTR hglbCopy = (LPTSTR)GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE | GMEM_ZEROINIT, tBytesLen); //�����ڴ�
//  if(hglbCopy != NULL)
//  {
//    LPTSTR lpszDst = (LPTSTR)GlobalLock(hglbCopy); //�����ڴ�
//    memcpy(lpszDst, szStringData, tBytesLen); //��������
//    GlobalUnlock(hglbCopy); //�����ڴ�

//    // Place the handle on the clipboard.
//    if(OpenClipboard(NULL))
//    {
//      EmptyClipboard();

//     #if (defined _UNICODE || defined UNICODE)
//      SetClipboardData(CF_UNICODETEXT, hglbCopy);
//     #else
//      SetClipboardData(CF_TEXT, hglbCopy);
//     #endif

//      CloseClipboard();

//      bRet = TRUE;
//    }
//  }

//  return bRet;
//}

//Unicode
void  SetClipboardByUnicode(std::wstring strText)
{
    // �򿪼�����
    if (!OpenClipboard(NULL)|| !EmptyClipboard())
    {
        printf("�򿪻���ռ��а����\n");
        return ;
    }

    HANDLE hHandle;//�������GlobalAlloc�����������ڴ����ľ��
    //hHandle = GlobalAlloc(GMEM_MOVEABLE, strText.length()+1);//�����
    hHandle = GlobalAlloc(GMEM_MOVEABLE, ((wcslen(strText.c_str()))*sizeof(TCHAR))*2);

    if (hHandle)//����������ʧ��,�򷵻�NULL
    {
        LPWSTR lpStr = (LPWSTR)GlobalLock(hHandle);
        wcscpy(lpStr, strText.c_str());
        GlobalUnlock(hHandle);//�������
        SetClipboardData(CF_UNICODETEXT, hHandle);//���ü��а�����
        CloseClipboard();//�رռ��а�
    }
}
BOOL StringToClipBoard(const char* srcString)
{
    BOOL bResult = FALSE;
    DWORD dwLength = strlen(srcString);
    HANDLE hGlobalMemory = GlobalAlloc(GHND, dwLength + 1); // �����ڴ�
    LPBYTE lpGlobalMemory = (LPBYTE)GlobalLock(hGlobalMemory); // �����ڴ�
    if ( NULL != lpGlobalMemory )
    {
        strcpy((char*)lpGlobalMemory, srcString);
        ::GlobalUnlock(hGlobalMemory); // �����ڴ�����
        ::OpenClipboard(NULL); // �򿪼�����
        ::EmptyClipboard(); // ��ռ�����
        ::SetClipboardData(CF_TEXT, hGlobalMemory); // ���ڴ��е����ݷ��õ�������
        ::CloseClipboard();

        bResult = TRUE;
    }
    return bResult;
}
int CopyFileToClipboard(const char szFileName[])
{
    UINT uDropEffect;
    HGLOBAL hGblEffect;
    LPDWORD lpdDropEffect;
    DROPFILES stDrop;
    HGLOBAL hGblFiles;
    LPSTR lpData;
    uDropEffect = RegisterClipboardFormat(L"Preferred DropEffect");
    hGblEffect = GlobalAlloc(GMEM_ZEROINIT | GMEM_MOVEABLE | GMEM_DDESHARE,sizeof(DWORD));
    lpdDropEffect = (LPDWORD)GlobalLock(hGblEffect);
    *lpdDropEffect = DROPEFFECT_COPY;//����; ��������DROPEFFECT_MOVE
    GlobalUnlock(hGblEffect);
    stDrop.pFiles = sizeof(DROPFILES);
    stDrop.pt.x = 0;
    stDrop.pt.y = 0;
    stDrop.fNC = FALSE;
    stDrop.fWide = FALSE;
    hGblFiles = GlobalAlloc(GMEM_ZEROINIT | GMEM_MOVEABLE | GMEM_DDESHARE,\
                            sizeof(DROPFILES)+strlen(szFileName)+2);
    lpData = (LPSTR)GlobalLock(hGblFiles);
    memcpy(lpData,&stDrop,sizeof(DROPFILES));
    strcpy(lpData+sizeof(DROPFILES),szFileName);
    GlobalUnlock(hGblFiles);
    OpenClipboard(NULL);
    EmptyClipboard();
    SetClipboardData(CF_HDROP,hGblFiles);
    SetClipboardData(uDropEffect,hGblEffect);
    CloseClipboard();

    return 1;
}
//hBitMap = CopySelectRectBitmap(lpszPath);


ScreenShot::ScreenShot()
{

    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    //bug�޸�����������ǰ����ʾ
    setWindowState(Qt::WindowActive|Qt::WindowFullScreen);
    //��Ϣ��
    widthInfo = 100;
    heightInfo = 55;
    //��ʾ��
    widthTip = 300;
    heightTip = 100;

    initScreenShot();
    setWindowTitle("������ʾ��");
    g_type=0;
    g_htmlFinished=false;
}

void ScreenShot::menuSelect()
{
    acSave = new QAction(tr("���Ϊ"),this);
    acSave1 = new QAction(tr("���浽ճ����"),this);
    acCal = new QAction(tr("��ѡ"),this);
    quitAction = new QAction(tr("�˳�"),this);
    contextMenu = new QMenu(this);

    connect(acSave,SIGNAL(triggered()),this,SLOT(savePicture()));
    connect(acCal,SIGNAL(triggered()),this,SLOT(cancelSelectedRect()));
    connect(acSave1,SIGNAL(triggered()),this,SLOT(addtoCo()));
    connect(quitAction,SIGNAL(triggered()),this,SLOT(hide()));
}
void ScreenShot::setType(int g_num)
{
    g_type=g_num;
}

void ScreenShot::savePicture()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this,tr("����ͼƬ"),QDir::currentPath(),tr("Images (*.jpg *.png *.bmp)"));
    if(fileName.isNull())
        return;

    shotPicture.save(fileName);
    hide();
}
void ScreenShot::addtoCo()
{
    if(currentShotState == finishShot || currentShotState == finishMoveShot || currentShotState == finishControl){
        QDir *temp = new QDir;
        QString theaddress="D:/g_rank";
        if(!temp->exists(theaddress))
        {
            if(!temp->mkdir(theaddress))
            {
                   theaddress= "C:/g_rank";
                   temp->mkdir(theaddress);
            }

        }
        delete temp;
        if(g_type==0)
        {
            QString szqFileName=theaddress+"/1.png";
            QFile::remove(szqFileName);
            shotPicture.save(szqFileName);
            CopyFileToClipboard(szqFileName.toStdString().c_str());
        }
        else if(g_type==1)
        {
            QHostInfo info = QHostInfo::fromName(QString("www.baidu.com"));
            if(!info.addresses().isEmpty())
            {
                QString szqFileName=theaddress+"/2.png";
                QFile::remove(szqFileName);
                shotPicture.save(szqFileName);

    //            std::string app_id = "10878236";
    //            std::string api_key = "eU0rYIgBZkZTmdWe74kNgzBW";
    //            std::string secret_key = "Tq2Msb3gW6ovzFfKCmjuUf2u3G778Y0P";

    //            aip::Ocr client(app_id, api_key, secret_key);
    //            Json::Value result;

    //            std::string image;
    //            aip::get_file_content(szqFileName.toStdString().c_str(), &image);

    //            // ����ͨ������ʶ��, ͼƬ����Ϊ����ͼƬ
    //            result = client.general_basic(image, aip::null);
    //            // ����п�ѡ����
    //            std::map<std::string, std::string> options;
    //            options["language_type"] = "CHN_ENG";
    //            options["detect_direction"] = "true";
    //            options["detect_language"] = "true";
    //            options["probability"] = "true";
    //            // ����������ͨ������ʶ��, ͼƬ����Ϊ����ͼƬ
    //            result = client.general_basic(image, options);
    //            QMessageBox::about(NULL,"��ʾ",result["words_result"][0]);

                QByteArray ba;
                QBuffer buf(&ba);
                shotPicture.save(&buf, "png");
                QByteArray byteArr;
                buf.close();



                nam = new QNetworkAccessManager(this);
                QUrl url;
                prepareGetHtml("https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=eU0rYIgBZkZTmdWe74kNgzBW&client_secret=Tq2Msb3gW6ovzFfKCmjuUf2u3G778Y0P");
                while(!g_htmlFinished)
                    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
                jsonList=szHtmlInfo.split("\"");
                QStringList jsonAccess_token=getInitJson(jsonList,"access_token",0);
                QNetworkRequest request;
                url.setUrl("https://aip.baidubce.com/rest/2.0/ocr/v1/general_basic?access_token="+jsonAccess_token.at(0));
                //QMessageBox::about(NULL,"����",jsonAccess_token.at(0));
                request.setUrl(url);
                request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));
                byteArr.append("image=");
                byteArr.append(QUrl::toPercentEncoding(ba.toBase64()));
                connect(nam, SIGNAL(finished(QNetworkReply*)),this, SLOT(recognitionRequestFinished(QNetworkReply*)));
                nam->post(request,byteArr);
                g_htmlFinished-false;
            }
            else
            {
                 QMessageBox::about(NULL,"����","�Բ��������豸δ�����޷�ʹ�ý�ͼʶ�����ֹ���");
            }

        }


        emit finishPicture(shotPicture); //�����ʱ����finishPicture�ź�
        hide();

    }
}
void ScreenShot::prepareGetHtml(QString url)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    manager->get(QNetworkRequest(QUrl(url)));
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getHtmlFinished(QNetworkReply*)));

}
void ScreenShot::getHtmlFinished(QNetworkReply *reply)
{
    g_htmlFinished=true;
    szHtmlInfo=reply->readAll();
}

void ScreenShot::recognitionRequestFinished(QNetworkReply* reply){
    QNetworkReply::NetworkError err = reply->error();
    //qDebug()<<reply->readAll();
    if(err != QNetworkReply::NoError) {
        qDebug() << "Failed: " << reply->errorString();
    }else {
        // ��ȡ��������
//        QJsonParseError json_error;
//        QJsonDocument parse_doucment = QJsonDocument::fromJson(reply->readAll(), &json_error);
//        if(parse_doucment.isObject()){
//            QJsonObject obj = parse_doucment.object();
//            int wordsNum = obj.take("words_result_num").toInt();
//            if(wordsNum > 0){
//                QString res;
//                QJsonArray jsonArr = obj.take("words_result").toArray();
//                for(int i=0;i<wordsNum;i++){
//                   res.append(jsonArr[i].toObject().take("words").toString());
//                   res.append("<br>");
//                }
//                ui->textEdit_2->setText(res);
//                if(!res.isEmpty()&&ui->checkBox_3->isChecked()){
//                    QClipboard *board = QApplication::clipboard();
//                    board->setText(res);
//                }
//            }else{
//                QMessageBox::information(NULL, "��ʾ", "�޷�ʶ��ͼƬ����");
//            }
        //QMessageBox::about(NULL,"����",reply->readAll());
        QByteArray txt=reply->readAll();
        //QStringList jsonTempSet=QTextCodec::codecForName("utf-8")->toUnicode(txt).split("{\"words\":\"");
//        for(int i=0;i<jsonTempSet.length();i++)
//        {
//            if(i!=jsonTempSet.length()-1)
//                jsonTempSet.replace(i,jsonTempSet.at(i).left(jsonTempSet.at(i).length()-3));
//            else jsonTempSet.replace(i,jsonTempSet.at(i).left(jsonTempSet.at(i).length()-4));
//        }

        QStringList jsonTemp=getInitJson(QTextCodec::codecForName("utf-8")->toUnicode(txt).split("\""),"words",1);
        //QStringList jsonTemp1=QTextCodec::codecForName("utf-8")->toUnicode(txt).split(QRegExp("(((/()|(/{)|(/[))\")|(\"((/)|(/})|(/])))"));
        //QMessageBox::about(NULL,"����",QTextCodec::codecForName("utf-8")->toUnicode(txt)+"\r\n"+jsonTemp.join(""));
        QString it;
            for(int i=0;i<jsonTemp.length();i++)
            {
                it+=jsonTemp.at(i)+"\r\n";
                //QMessageBox::about(this,"ll",jsonTemp.at(i));
            }
            it.replace("\\\\","\\");
            it.replace("\\\"","\"");
         SetClipboardByUnicode(it.toStdWString());
         //QMessageBox::about(NULL,"����1231",it);

        }






}


void ScreenShot::loadBackgroundPicture(const QPixmap &bgPicture)
{
    int width,height;
    width = QApplication::desktop()->size().width();
    height = QApplication::desktop()->size().height();

    loadBackgroundPicture(bgPicture,0,0,width,height);
}

void ScreenShot::loadBackgroundPicture(const QPixmap &bgPicture, int x, int y, int width, int height)
{
    loadPicture = bgPicture;
    screenx = x;
    screeny = y;
    screenwidth = width;
    screenheight = height;
    initScreenShot();
}

QPixmap ScreenShot::getShotPicture()
{
    initScreenShot();
    QPixmap result = QPixmap();
    result = QPixmap::grabWindow(QApplication::desktop()->winId()); //ץȡ��ǰ��Ļ��ͼƬ

    return result;
}

void ScreenShot::paintEvent(QPaintEvent *event)
{
    QColor shadowColor;
    shadowColor= QColor(0,0,0,100); //��Ӱ��ɫ����
    painter.begin(this); //�����ػ�

    painter.setPen(QPen(Qt::blue,2,Qt::SolidLine,Qt::FlatCap));//���û���
    painter.drawPixmap(screenx,screeny,loadPicture); //������ͼƬ����������
    painter.fillRect(screenx,screeny,screenwidth,screenheight,shadowColor); //��Ӱ��Ч��

    switch(currentShotState){
    case initShot:
        drawTipsText();
        break;
    case beginShot:
    case finishShot:
        selectedRect = getRect(beginPoint,endPoint); //��ȡѡ��
        drawSelectedPicture();
        break;
    case beginMoveShot:
    case finishMoveShot:
        selectedRect = getMoveAllSelectedRect(); //��ȡѡ��
        drawSelectedPicture();
        break;
    case beginControl:
    case finishControl:
        selectedRect = getMoveControlSelectedRect();
        drawSelectedPicture();
        break;
    default:
        break;
    }
    drawXYWHInfo(); //��ӡ������Ϣ
    painter.end();  //�ػ����

    if(currentShotState == finishMoveShot || currentShotState == finishControl){
        updateBeginEndPointValue(selectedRect); //���ƶ���ѡ���󣬸���beginPoint,endPoint;Ϊ��һ���ƶ���׼������
    }

}

void ScreenShot::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape){
        initScreenShot();
        hide();
    }
}

void ScreenShot::mousePressEvent(QMouseEvent *event)
{
    //����ʼ�����϶�����ѡ������ʱ,ȷ����ʼѡȡ��beginPoint����
    if(event->button() == Qt::LeftButton && currentShotState == initShot){
        currentShotState = beginShot; //���õ�ǰ״̬ΪbeginShot״̬
        beginPoint = event->pos();
    }

    //�ƶ�ѡ���ı�ѡ��������λ��
    if(event->button() == Qt::LeftButton && isInSelectedRect(event->pos()) &&
            getMoveControlState(event->pos()) == moveControl0){
        currentShotState = beginMoveShot; //���ÿ�ʼ�ƶ�ѡȡѡ��,beginMoveShot״̬
        moveBeginPoint = event->pos();
    }
    //�ƶ����Ƶ�ı�ѡ����С
    if(event->button() == Qt::LeftButton && getMoveControlState(event->pos()) != moveControl0){
        currentShotState = beginControl; //��ʼ�ƶ����Ƶ�
        controlValue = getMoveControlState(event->pos());
        moveBeginPoint = event->pos();
    }
}

void ScreenShot::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && currentShotState == beginShot){
        currentShotState = finishShot;
        endPoint = event->pos();
        update();
    }

    if(event->button() == Qt::LeftButton && currentShotState == beginMoveShot){
        currentShotState = finishMoveShot;
        moveEndPoint = event->pos();
        update();
    }

    //��ǰ״̬ΪbeginControl״̬ʱ������״̬ΪfinishControl
    if(event->button() == Qt::LeftButton && currentShotState == beginControl){
        currentShotState = finishControl;
        moveEndPoint = event->pos();
        update();
    }
}

void ScreenShot::mouseMoveEvent(QMouseEvent *event)
{
    //���϶�ʱ����̬�ĸ�����ѡ�������
    if(currentShotState == beginShot){
        endPoint = event->pos();
        update();
    }

    //��ȷ��ѡ���󣬶�ѡ�������ƶ�����
    if(currentShotState == beginMoveShot || currentShotState == beginControl){
        moveEndPoint = event->pos();
        update();
    }

    updateMouseShape(event->pos()); //�޸�������״
    setMouseTracking(true);
}


void ScreenShot::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(currentShotState == finishShot || currentShotState == finishMoveShot || currentShotState == finishControl){
        QDir *temp = new QDir;
        QString theaddress="D:/g_rank";
        if(!temp->exists(theaddress))
        {
            if(!temp->mkdir(theaddress))
            {
                   theaddress= "C:/g_rank";
                   temp->mkdir(theaddress);
            }
        }
        delete temp;
//        QString szqFileName=theaddress+"/1.png";
////        QMessageBox::about(NULL,(QString)"1",QString((szqFileName)));
////        QTime dieTime = QTime::currentTime().addMSecs(150);
////        while( QTime::currentTime() < dieTime )
////            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
//        shotPicture.save(szqFileName);
//        CopyFileToClipboard(szqFileName.toStdString().c_str());
//LPCTSTR szFileName = NULL;
//QStringת����tchar
//#ifdef UNICODE
//        szFileName = (wchar_t*)szqFileName.utf16();
//#else
//        QByteArray byteArray = szqFileName.toLocal8Bit();
//        szFileName = byteArray.constData();
//#endif // UNICODE


//        {
//            BOOL bRet = FALSE;

//            HBITMAP hBitmap = NULL;
//            BOOL bClipboardOpened = FALSE;
//            do
//            {
//              hBitmap = (HBITMAP)LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//              if(hBitmap == NULL)
//                break;

//              if(!OpenClipboard(NULL))
//                break;
//              bClipboardOpened = TRUE;
//              EmptyClipboard();
//              SetClipboardData(CF_BITMAP, hBitmap);
//              bRet = TRUE;
//            } while (0);

//            if(bClipboardOpened)
//            {
//              CloseClipboard();
//            }
//            if(hBitmap)
//            {
//              //DeleteObject(hBitmap);
//              hBitmap = NULL;
//            }
//        }

        if(g_type==0)
        {
            QString szqFileName=theaddress+"/1.png";
            QFile::remove(szqFileName);
            shotPicture.save(szqFileName);
            CopyFileToClipboard(szqFileName.toStdString().c_str());


        }
        else if(g_type==1)
        {
            QHostInfo info = QHostInfo::fromName(QString("www.baidu.com"));
            if(!info.addresses().isEmpty())
            {
                QString szqFileName=theaddress+"/2.png";
                QFile::remove(szqFileName);
                shotPicture.save(szqFileName);

    //            std::string app_id = "10878236";
    //            std::string api_key = "eU0rYIgBZkZTmdWe74kNgzBW";
    //            std::string secret_key = "Tq2Msb3gW6ovzFfKCmjuUf2u3G778Y0P";

    //            aip::Ocr client(app_id, api_key, secret_key);
    //            Json::Value result;

    //            std::string image;
    //            aip::get_file_content(szqFileName.toStdString().c_str(), &image);

    //            // ����ͨ������ʶ��, ͼƬ����Ϊ����ͼƬ
    //            result = client.general_basic(image, aip::null);
    //            // ����п�ѡ����
    //            std::map<std::string, std::string> options;
    //            options["language_type"] = "CHN_ENG";
    //            options["detect_direction"] = "true";
    //            options["detect_language"] = "true";
    //            options["probability"] = "true";
    //            // ����������ͨ������ʶ��, ͼƬ����Ϊ����ͼƬ
    //            result = client.general_basic(image, options);
    //            QMessageBox::about(NULL,"��ʾ",result["words_result"][0]);

                QByteArray ba;
                QBuffer buf(&ba);
                shotPicture.save(&buf, "png");
                QByteArray byteArr;
                buf.close();




                nam = new QNetworkAccessManager(this);
                QUrl url;
                prepareGetHtml("https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=eU0rYIgBZkZTmdWe74kNgzBW&client_secret=Tq2Msb3gW6ovzFfKCmjuUf2u3G778Y0P");
                while(!g_htmlFinished)
                    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
                jsonList=szHtmlInfo.split("\"");
                QStringList jsonAccess_token=getInitJson(jsonList,"access_token",0);
                QNetworkRequest request;
                url.setUrl("https://aip.baidubce.com/rest/2.0/ocr/v1/general_basic?access_token="+jsonAccess_token.at(0));
                request.setUrl(url);
                request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));
                byteArr.append("image=");
                byteArr.append(QUrl::toPercentEncoding( ba.toBase64()));
                connect(nam, SIGNAL(finished(QNetworkReply*)),this, SLOT(recognitionRequestFinished(QNetworkReply*)));
                nam->post(request,byteArr);
            }
            else
            {
                 QMessageBox::about(NULL,"����","�Բ��������豸δ�����޷�ʹ�ý�ͼʶ�����ֹ���");
            }


        }


        emit finishPicture(shotPicture); //�����ʱ����finishPicture�ź�
        hide();
    }
}

QRect ScreenShot::getRect(const QPoint &beginPoint, const QPoint &endPoint)
{
    int x,y,width,height;
    width = qAbs(beginPoint.x() - endPoint.x());
    height = qAbs(beginPoint.y() - endPoint.y());
    x = beginPoint.x() < endPoint.x() ? beginPoint.x() : endPoint.x();
    y = beginPoint.y() < endPoint.y() ? beginPoint.y() : endPoint.y();

    return QRect(x,y,width,height);
}

void ScreenShot::initScreenShot()
{
    currentShotState = initShot;
    controlValue = moveControl0;
    beginPoint =QPoint(0,0);
    endPoint = QPoint(0,0);
    moveBeginPoint = QPoint(0,0);
    moveEndPoint = QPoint(0,0);

    tlRect = QRect(0,0,0,0); //���ϵ�
    trRect = QRect(0,0,0,0); //���ҵ�
    blRect = QRect(0,0,0,0); //���µ�
    brRect = QRect(0,0,0,0); //���µ�
    tcRect = QRect(0,0,0,0); //���е�
    bcRect = QRect(0,0,0,0); //���е�
    lcRect = QRect(0,0,0,0); //���е�
    rcRect = QRect(0,0,0,0); //���е�

    setCursor(Qt::CrossCursor);
}

bool ScreenShot::isInSelectedRect(const QPoint &point)
{
    int x,y;
    QRect selectedRect;
    if(currentShotState == initShot || currentShotState == beginShot)
        return false;

    selectedRect = getSelectedRect();
    x = point.x();
    y = point.y();

    return selectedRect.contains(x,y);
}

void ScreenShot::cancelSelectedRect()
{
    initScreenShot();
    update(); //�����ػ棬��ѡȡ����ȥ��
}

void ScreenShot::contextMenuEvent(QContextMenuEvent *event)
{
    menuSelect();

    if(isInSelectedRect(event->pos())){
        contextMenu->addAction(acSave);
        contextMenu->addAction(acSave1);
    }
    else{
        contextMenu->addAction(acCal);
        contextMenu->addAction(quitAction);
    }

    contextMenu->exec(event->pos());
}

void ScreenShot::drawTipsText()
{
    int x = (screenwidth - widthTip)/2;
    int y = (screenheight - heightTip)/2;
    QColor color = QColor(100,100,100,200);
    QRect rect = QRect(x,y,widthTip,heightTip);
    QString strTipsText = QString(tr("��ܰ��ʾ\n����϶����н���;�����������Ҽ�����;\n�����������Ҽ�ȡ��;ESC�˳�;"));

    painter.fillRect(rect,color);
    painter.setPen(QPen(Qt::white));//���û��ʵ���ɫΪ��ɫ
    painter.drawText(rect,Qt::AlignCenter,strTipsText);

}

QRect ScreenShot::getSelectedRect()
{
    if(currentShotState == beginMoveShot){
        return getMoveAllSelectedRect();
    }
    else if(currentShotState == beginControl){
        return getMoveControlSelectedRect();
    }
    else{
        return getRect(beginPoint,endPoint);
    }
}

void ScreenShot::updateBeginEndPointValue(const QRect &rect)
{
    beginPoint = rect.topLeft();
    endPoint = rect.bottomRight();

    moveBeginPoint = QPoint(0,0);
    moveEndPoint = QPoint(0,0);
}

void ScreenShot::checkMoveEndPoint()
{
    int x,y;
    QRect selectedRect = getRect(beginPoint, endPoint);
    QPoint bottomRightPoint = selectedRect.bottomRight();
    x = moveEndPoint.x() - moveBeginPoint.x();
    y = moveEndPoint.y() - moveBeginPoint.y();

    if(x + selectedRect.x() < 0){ //���ƶ���X����С����ʱ�������ѡ����ʧ��������moveEndPoint��X�������ֵ�����и�ֵ
        moveEndPoint.setX(qAbs(selectedRect.x()-moveBeginPoint.x()));
    }

    if(y + selectedRect.y() < 0){ //���ƶ���Y����С����ʱ�������ѡ����ʧ��������moveEndPoint��Y�������ֵ�����и�ֵ
        moveEndPoint.setY(qAbs(selectedRect.y() - moveBeginPoint.y()));
    }

    if(x + bottomRightPoint.x() > screenwidth){ //���ƶ�ѡ���󣬳��ֳ���������Ļ������ʱ������moveEndPoint��X���������
        moveEndPoint.setX(screenwidth - bottomRightPoint.x() + moveBeginPoint.x());
    }

    if(y + bottomRightPoint.y() > screenheight){ //���ƶ�ѡ���󣬳��ֳ���������Ļ������ʱ������moveEndPoint��Y���������ֵ
        moveEndPoint.setY(screenheight - bottomRightPoint.y() + moveBeginPoint.y());
    }
}

void ScreenShot::draw8ControlPoint(const QRect &rect)
{
    int x,y;
    QColor color= QColor(0,0,255); //�������ɫ����
    QPoint tlPoint = rect.topLeft(); //���ϵ�
    QPoint trPoint = rect.topRight(); //���ϵ�
    QPoint blPoint = rect.bottomLeft(); //���µ�
    QPoint brPoint = rect.bottomRight(); //���µ�

    x = (tlPoint.x()+trPoint.x())/2;
    y = tlPoint.y();
    QPoint tcPoint = QPoint(x,y);

    x = (blPoint.x()+brPoint.x())/2;
    y = blPoint.y();
    QPoint bcPoint = QPoint(x,y);

    x = tlPoint.x();
    y = (tlPoint.y()+blPoint.y())/2;
    QPoint lcPoint = QPoint(x,y);

    x = trPoint.x();
    y = (trPoint.y()+brPoint.y())/2;
    QPoint rcPoint = QPoint(x,y);

    tlRect = QRect(tlPoint.x()-2,tlPoint.y()-2,6,6); //���ϵ�
    trRect = QRect(trPoint.x()-2,trPoint.y()-2,6,6); //���ϵ�
    blRect = QRect(blPoint.x()-2,blPoint.y()-2,6,6); //���µ�
    brRect = QRect(brPoint.x()-2,brPoint.y()-2,6,6); //���µ�
    tcRect = QRect(tcPoint.x()-2,tcPoint.y()-2,6,6); //���е�
    bcRect = QRect(bcPoint.x()-2,bcPoint.y()-2,6,6); //���е�
    lcRect = QRect(lcPoint.x()-2,lcPoint.y()-2,6,6);//���е�
    rcRect = QRect(rcPoint.x()-2,rcPoint.y()-2,6,6); //���е�

    painter.fillRect(tlRect,color);
    painter.fillRect(trRect,color);
    painter.fillRect(blRect,color);
    painter.fillRect(brRect,color);
    painter.fillRect(tcRect,color);
    painter.fillRect(bcRect,color);
    painter.fillRect(lcRect,color);
    painter.fillRect(rcRect,color);
}

void ScreenShot::updateMouseShape(const QPoint &point)
{
    switch(currentShotState){
    case initShot:
    case beginShot:
        setCursor(Qt::CrossCursor);
        break;
    case beginMoveShot:
        setCursor(Qt::OpenHandCursor);
        break;
    case finishShot:
    case finishMoveShot:
    case finishControl:
        if(getSelectedRect().contains(point))
            setCursor(Qt::OpenHandCursor);
        else
            updateMoveControlMouseShape(getMoveControlState(point));
        break;
    case beginControl:
        updateMoveControlMouseShape(controlValue); //���ú������ƶ�8�����Ƶ�������״̬�ĸı�
        break;
    default:
        setCursor(Qt::ArrowCursor);
        break;
    }
}

void ScreenShot::updateMoveControlMouseShape(controlPointEnum controlValue){
    switch(controlValue){
    case moveControl1:
    case moveControl5:
        setCursor(Qt::SizeFDiagCursor);
        break;
    case moveControl2:
    case moveControl6:
        setCursor(Qt::SizeVerCursor);
        break;
    case moveControl3:
    case moveControl7:
        setCursor(Qt::SizeBDiagCursor);
        break;
    case moveControl4:
    case moveControl8:
        setCursor(Qt::SizeHorCursor);
        break;
    default:
        setCursor(Qt::ArrowCursor);
        break;
    }
}

ScreenShot::controlPointEnum ScreenShot::getMoveControlState(const QPoint &point)
{
    ScreenShot::controlPointEnum result = moveControl0;
    if(currentShotState == initShot || currentShotState == beginShot)  {
        result = moveControl0;
    }
    else if(tlRect.contains(point)){
        result = moveControl1;
    }
    else if(tcRect.contains(point)){
        result = moveControl2;
    }
    else if(trRect.contains(point)){
        result = moveControl3;
    }
    else if(rcRect.contains(point)){
        result = moveControl4;
    }
    else if(brRect.contains(point)){
        result = moveControl5;
    }
    else if(bcRect.contains(point)){
        result = moveControl6;
    }
    else if(blRect.contains(point)){
        result = moveControl7;
    }
    else if(lcRect.contains(point)){
        result = moveControl8;
    }
    else{
        result = moveControl0;
    }

    return result;
}

QRect ScreenShot::getMoveAllSelectedRect(void)
{
    QRect result;
    QPoint tmpBeginPoint,tmpEndPoint;
    int moveX,moveY;
    checkMoveEndPoint(); //���ƶ�ѡ�������жϣ����ƶ���ѡ�������߽磬��ֹͣ�ƶ�
    moveX = moveEndPoint.x() - moveBeginPoint.x();
    moveY = moveEndPoint.y() - moveBeginPoint.y();
    tmpBeginPoint.setX(beginPoint.x() + moveX);
    tmpBeginPoint.setY(beginPoint.y() + moveY);
    tmpEndPoint.setX(endPoint.x() + moveX);
    tmpEndPoint.setY(endPoint.y() + moveY);

    result = getRect(tmpBeginPoint, tmpEndPoint);
    return result;
}

QRect ScreenShot::getMoveControlSelectedRect(void)
{
    int x,y,w,h;
    QRect rect = getRect(beginPoint,endPoint);
    QRect result;
    switch(controlValue){
    case moveControl1:
        result = getRect(rect.bottomRight(),moveEndPoint);
        return result;
        break;
    case moveControl2:
        x = rect.x();
        y = getMinValue(moveEndPoint.y(),rect.bottomLeft().y());
        w = rect.width();
        h = qAbs(moveEndPoint.y() - rect.bottomRight().y());
        break;
    case moveControl3:
        result = getRect(rect.bottomLeft(),moveEndPoint);
        return result;
        break;
    case moveControl4:
        x = getMinValue(rect.x(),moveEndPoint.x());
        y = rect.y();
        w = qAbs(rect.bottomLeft().x() - moveEndPoint.x());
        h = rect.height();
        break;
    case moveControl5:
        result = getRect(rect.topLeft(),moveEndPoint);
        return result;
        break;
    case moveControl6:
        x = rect.x();
        y = getMinValue(rect.y(),moveEndPoint.y());
        w = rect.width();
        h = qAbs(moveEndPoint.y() - rect.topLeft().y());
        break;
    case moveControl7:
        result = getRect(moveEndPoint,rect.topRight());
        return result;
        break;
    case moveControl8:
        x = getMinValue(moveEndPoint.x(),rect.bottomRight().x());
        y = rect.y();
        w = qAbs(rect.bottomRight().x() - moveEndPoint.x());
        h = rect.height();
        break;
    default:
        result = getRect(beginPoint,endPoint);
        return result;
        break;
    }

    return QRect(x,y,w,h); //��ȡѡ��
}

int ScreenShot::getMinValue(int num1, int num2)
{
    return num1<num2?num1:num2;
}

void ScreenShot::drawSelectedPicture(void)
{
    painter.drawRect(selectedRect); //��ѡ�еľ��ο�
    shotPicture = loadPicture.copy(selectedRect);  //����ѡ����Picture
    if(selectedRect.width() > 0 && selectedRect.height()){
        painter.drawPixmap(selectedRect.topLeft(),shotPicture); //��ѡ�������ͼƬ
    }
    draw8ControlPoint(selectedRect); //����ѡ����8�����Ƶ�
}

void ScreenShot::drawXYWHInfo(void)
{
    int x,y;
    QColor color = QColor(239,234,228,200);
    QRect rect;
    QString strTipsText;
    switch(currentShotState){
    case beginShot:
    case finishShot:
    case beginMoveShot:
    case finishMoveShot:
    case beginControl:
    case finishControl:
        x = selectedRect.x() + 5;
        y = selectedRect.y() > heightInfo ? selectedRect.y()-heightInfo:selectedRect.y();
        rect = QRect(x,y,widthInfo,heightInfo);
        strTipsText = QString(tr(" ������Ϣ\n x:%1 y:%2\n w:%3 h:%4")).arg(selectedRect.x(),4).arg(selectedRect.y(),4)
                .arg(selectedRect.width(),4).arg(selectedRect.height(),4);
        painter.fillRect(rect,color);
        painter.setPen(QPen(Qt::black));//���û��ʵ���ɫΪ��ɫ
        painter.drawText(rect,Qt::AlignLeft|Qt::AlignVCenter,strTipsText);
        break;
    default:
        break;
    }
}
