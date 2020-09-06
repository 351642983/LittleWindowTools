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

//  size_t tBytesLen = (_tcslen(szStringData) + 1)  * sizeof(TCHAR); //数据字节长度
//  LPTSTR hglbCopy = (LPTSTR)GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE | GMEM_ZEROINIT, tBytesLen); //分配内存
//  if(hglbCopy != NULL)
//  {
//    LPTSTR lpszDst = (LPTSTR)GlobalLock(hglbCopy); //锁定内存
//    memcpy(lpszDst, szStringData, tBytesLen); //拷贝数据
//    GlobalUnlock(hglbCopy); //解锁内存

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
    // 打开剪贴板
    if (!OpenClipboard(NULL)|| !EmptyClipboard())
    {
        printf("打开或清空剪切板出错！\n");
        return ;
    }

    HANDLE hHandle;//保存调用GlobalAlloc函数后分配的内存对象的句柄
    //hHandle = GlobalAlloc(GMEM_MOVEABLE, strText.length()+1);//错误的
    hHandle = GlobalAlloc(GMEM_MOVEABLE, ((wcslen(strText.c_str()))*sizeof(TCHAR))*2);

    if (hHandle)//若函数调用失败,则返回NULL
    {
        LPWSTR lpStr = (LPWSTR)GlobalLock(hHandle);
        wcscpy(lpStr, strText.c_str());
        GlobalUnlock(hHandle);//解除锁定
        SetClipboardData(CF_UNICODETEXT, hHandle);//设置剪切板数据
        CloseClipboard();//关闭剪切板
    }
}
BOOL StringToClipBoard(const char* srcString)
{
    BOOL bResult = FALSE;
    DWORD dwLength = strlen(srcString);
    HANDLE hGlobalMemory = GlobalAlloc(GHND, dwLength + 1); // 分配内存
    LPBYTE lpGlobalMemory = (LPBYTE)GlobalLock(hGlobalMemory); // 锁定内存
    if ( NULL != lpGlobalMemory )
    {
        strcpy((char*)lpGlobalMemory, srcString);
        ::GlobalUnlock(hGlobalMemory); // 锁定内存块解锁
        ::OpenClipboard(NULL); // 打开剪贴板
        ::EmptyClipboard(); // 清空剪贴板
        ::SetClipboardData(CF_TEXT, hGlobalMemory); // 将内存中的数据放置到剪贴板
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
    *lpdDropEffect = DROPEFFECT_COPY;//复制; 剪贴则用DROPEFFECT_MOVE
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
    //bug修复，窗口在最前端显示
    setWindowState(Qt::WindowActive|Qt::WindowFullScreen);
    //信息框
    widthInfo = 100;
    heightInfo = 55;
    //提示框
    widthTip = 300;
    heightTip = 100;

    initScreenShot();
    setWindowTitle("截屏显示框");
    g_type=0;
    g_htmlFinished=false;
}

void ScreenShot::menuSelect()
{
    acSave = new QAction(tr("另存为"),this);
    acSave1 = new QAction(tr("保存到粘贴板"),this);
    acCal = new QAction(tr("重选"),this);
    quitAction = new QAction(tr("退出"),this);
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
    fileName = QFileDialog::getSaveFileName(this,tr("保存图片"),QDir::currentPath(),tr("Images (*.jpg *.png *.bmp)"));
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

    //            // 调用通用文字识别, 图片参数为本地图片
    //            result = client.general_basic(image, aip::null);
    //            // 如果有可选参数
    //            std::map<std::string, std::string> options;
    //            options["language_type"] = "CHN_ENG";
    //            options["detect_direction"] = "true";
    //            options["detect_language"] = "true";
    //            options["probability"] = "true";
    //            // 带参数调用通用文字识别, 图片参数为本地图片
    //            result = client.general_basic(image, options);
    //            QMessageBox::about(NULL,"提示",result["words_result"][0]);

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
                //QMessageBox::about(NULL,"测试",jsonAccess_token.at(0));
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
                 QMessageBox::about(NULL,"提醒","对不起，您的设备未联网无法使用截图识别文字功能");
            }

        }


        emit finishPicture(shotPicture); //当完成时发送finishPicture信号
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
        // 获取返回内容
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
//                QMessageBox::information(NULL, "提示", "无法识别图片内容");
//            }
        //QMessageBox::about(NULL,"测试",reply->readAll());
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
        //QMessageBox::about(NULL,"测试",QTextCodec::codecForName("utf-8")->toUnicode(txt)+"\r\n"+jsonTemp.join(""));
        QString it;
            for(int i=0;i<jsonTemp.length();i++)
            {
                it+=jsonTemp.at(i)+"\r\n";
                //QMessageBox::about(this,"ll",jsonTemp.at(i));
            }
            it.replace("\\\\","\\");
            it.replace("\\\"","\"");
         SetClipboardByUnicode(it.toStdWString());
         //QMessageBox::about(NULL,"测试1231",it);

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
    result = QPixmap::grabWindow(QApplication::desktop()->winId()); //抓取当前屏幕的图片

    return result;
}

void ScreenShot::paintEvent(QPaintEvent *event)
{
    QColor shadowColor;
    shadowColor= QColor(0,0,0,100); //阴影颜色设置
    painter.begin(this); //进行重绘

    painter.setPen(QPen(Qt::blue,2,Qt::SolidLine,Qt::FlatCap));//设置画笔
    painter.drawPixmap(screenx,screeny,loadPicture); //将背景图片画到窗体上
    painter.fillRect(screenx,screeny,screenwidth,screenheight,shadowColor); //画影罩效果

    switch(currentShotState){
    case initShot:
        drawTipsText();
        break;
    case beginShot:
    case finishShot:
        selectedRect = getRect(beginPoint,endPoint); //获取选区
        drawSelectedPicture();
        break;
    case beginMoveShot:
    case finishMoveShot:
        selectedRect = getMoveAllSelectedRect(); //获取选区
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
    drawXYWHInfo(); //打印坐标信息
    painter.end();  //重绘结束

    if(currentShotState == finishMoveShot || currentShotState == finishControl){
        updateBeginEndPointValue(selectedRect); //当移动完选区后，更新beginPoint,endPoint;为下一次移动做准备工作
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
    //当开始进行拖动进行选择区域时,确定开始选取的beginPoint坐标
    if(event->button() == Qt::LeftButton && currentShotState == initShot){
        currentShotState = beginShot; //设置当前状态为beginShot状态
        beginPoint = event->pos();
    }

    //移动选区改变选区的所在位置
    if(event->button() == Qt::LeftButton && isInSelectedRect(event->pos()) &&
            getMoveControlState(event->pos()) == moveControl0){
        currentShotState = beginMoveShot; //启用开始移动选取选项,beginMoveShot状态
        moveBeginPoint = event->pos();
    }
    //移动控制点改变选区大小
    if(event->button() == Qt::LeftButton && getMoveControlState(event->pos()) != moveControl0){
        currentShotState = beginControl; //开始移动控制点
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

    //当前状态为beginControl状态时，设置状态为finishControl
    if(event->button() == Qt::LeftButton && currentShotState == beginControl){
        currentShotState = finishControl;
        moveEndPoint = event->pos();
        update();
    }
}

void ScreenShot::mouseMoveEvent(QMouseEvent *event)
{
    //当拖动时，动态的更新所选择的区域
    if(currentShotState == beginShot){
        endPoint = event->pos();
        update();
    }

    //当确定选区后，对选区进行移动操作
    if(currentShotState == beginMoveShot || currentShotState == beginControl){
        moveEndPoint = event->pos();
        update();
    }

    updateMouseShape(event->pos()); //修改鼠标的形状
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
//QString转换成tchar
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

    //            // 调用通用文字识别, 图片参数为本地图片
    //            result = client.general_basic(image, aip::null);
    //            // 如果有可选参数
    //            std::map<std::string, std::string> options;
    //            options["language_type"] = "CHN_ENG";
    //            options["detect_direction"] = "true";
    //            options["detect_language"] = "true";
    //            options["probability"] = "true";
    //            // 带参数调用通用文字识别, 图片参数为本地图片
    //            result = client.general_basic(image, options);
    //            QMessageBox::about(NULL,"提示",result["words_result"][0]);

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
                 QMessageBox::about(NULL,"提醒","对不起，您的设备未联网无法使用截图识别文字功能");
            }


        }


        emit finishPicture(shotPicture); //当完成时发送finishPicture信号
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

    tlRect = QRect(0,0,0,0); //左上点
    trRect = QRect(0,0,0,0); //上右点
    blRect = QRect(0,0,0,0); //左下点
    brRect = QRect(0,0,0,0); //右下点
    tcRect = QRect(0,0,0,0); //上中点
    bcRect = QRect(0,0,0,0); //下中点
    lcRect = QRect(0,0,0,0); //左中点
    rcRect = QRect(0,0,0,0); //右中点

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
    update(); //进行重绘，将选取区域去掉
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
    QString strTipsText = QString(tr("温馨提示\n鼠标拖动进行截屏;截屏区域内右键保存;\n截屏区域外右键取消;ESC退出;"));

    painter.fillRect(rect,color);
    painter.setPen(QPen(Qt::white));//设置画笔的颜色为白色
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

    if(x + selectedRect.x() < 0){ //当移动后X坐标小于零时，则出现选区丢失，则计算出moveEndPoint的X最大坐标值，进行赋值
        moveEndPoint.setX(qAbs(selectedRect.x()-moveBeginPoint.x()));
    }

    if(y + selectedRect.y() < 0){ //当移动后Y坐标小于零时，则出现选区丢失，则计算出moveEndPoint的Y最大坐标值，进行赋值
        moveEndPoint.setY(qAbs(selectedRect.y() - moveBeginPoint.y()));
    }

    if(x + bottomRightPoint.x() > screenwidth){ //当移动选区后，出现超出整个屏幕的右面时，设置moveEndPoint的X的最大坐标
        moveEndPoint.setX(screenwidth - bottomRightPoint.x() + moveBeginPoint.x());
    }

    if(y + bottomRightPoint.y() > screenheight){ //当移动选区后，出现超出整个屏幕的下面时，设置moveEndPoint的Y的最大坐标值
        moveEndPoint.setY(screenheight - bottomRightPoint.y() + moveBeginPoint.y());
    }
}

void ScreenShot::draw8ControlPoint(const QRect &rect)
{
    int x,y;
    QColor color= QColor(0,0,255); //画点的颜色设置
    QPoint tlPoint = rect.topLeft(); //左上点
    QPoint trPoint = rect.topRight(); //右上点
    QPoint blPoint = rect.bottomLeft(); //左下点
    QPoint brPoint = rect.bottomRight(); //右下点

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

    tlRect = QRect(tlPoint.x()-2,tlPoint.y()-2,6,6); //左上点
    trRect = QRect(trPoint.x()-2,trPoint.y()-2,6,6); //右上点
    blRect = QRect(blPoint.x()-2,blPoint.y()-2,6,6); //左下点
    brRect = QRect(brPoint.x()-2,brPoint.y()-2,6,6); //右下点
    tcRect = QRect(tcPoint.x()-2,tcPoint.y()-2,6,6); //上中点
    bcRect = QRect(bcPoint.x()-2,bcPoint.y()-2,6,6); //下中点
    lcRect = QRect(lcPoint.x()-2,lcPoint.y()-2,6,6);//左中点
    rcRect = QRect(rcPoint.x()-2,rcPoint.y()-2,6,6); //右中点

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
        updateMoveControlMouseShape(controlValue); //调用函数对移动8个控制点进行鼠标状态的改变
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
    checkMoveEndPoint(); //对移动选区进行判断，当移动的选区超出边界，则停止移动
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

    return QRect(x,y,w,h); //获取选区
}

int ScreenShot::getMinValue(int num1, int num2)
{
    return num1<num2?num1:num2;
}

void ScreenShot::drawSelectedPicture(void)
{
    painter.drawRect(selectedRect); //画选中的矩形框
    shotPicture = loadPicture.copy(selectedRect);  //更新选区的Picture
    if(selectedRect.width() > 0 && selectedRect.height()){
        painter.drawPixmap(selectedRect.topLeft(),shotPicture); //画选中区域的图片
    }
    draw8ControlPoint(selectedRect); //画出选区的8个控制点
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
        strTipsText = QString(tr(" 坐标信息\n x:%1 y:%2\n w:%3 h:%4")).arg(selectedRect.x(),4).arg(selectedRect.y(),4)
                .arg(selectedRect.width(),4).arg(selectedRect.height(),4);
        painter.fillRect(rect,color);
        painter.setPen(QPen(Qt::black));//设置画笔的颜色为黑色
        painter.drawText(rect,Qt::AlignLeft|Qt::AlignVCenter,strTipsText);
        break;
    default:
        break;
    }
}
