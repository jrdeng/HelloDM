#include "dmwrapper.h"

DmWrapper::DmWrapper(const QString &c, QObject *parent) :
    QObject(parent)
{
    dm = new QAxObject(c, this);
}

DmWrapper::~DmWrapper()
{

}

bool DmWrapper::isLoaded()
{
    return ver().length() > 0;
}

QString DmWrapper::ver()
{
    return dm->dynamicCall("Ver()").toString();
}

int DmWrapper::getLastError()
{
    return dm->dynamicCall("GetLastError()").toInt();
}

int DmWrapper::getMousePointWindow()
{
    return dm->dynamicCall("GetMousePointWindow()").toInt();
}

QString DmWrapper::getWindowTitle(int hWnd)
{
    return dm->dynamicCall("GetWindowTitle(int)", hWnd).toString();
}

bool DmWrapper::bindWindow(int hwnd, const QString &display, const QString &mouse, const QString &keypad, int mode)
{
    return dm->dynamicCall("BindWindow(int, QString, QString, QString, int)", hwnd, display, mouse, keypad, mode).toInt() == 1;
}

bool DmWrapper::setPath(const QString &path)
{
    return dm->dynamicCall("SetPath(QString)", path).toInt() == 1;
}

bool DmWrapper::loadPic(const QString &picName)
{
    return dm->dynamicCall("LoadPic(QString)", picName).toInt() == 1;
}

bool DmWrapper::freePic(const QString &picName)
{
    return dm->dynamicCall("FreePic(QString)", picName).toInt() == 1;
}

int DmWrapper::findPic(int x1, int y1, int x2, int y2, const QString &picName, int &outX, int &outY, int dir, double sim, const QString &deltaColor)
{
    QString dmRet = dm->dynamicCall("FindPicE(int, int, int, int, QString, QString, double, int)", x1, y1, x2, y2, picName, deltaColor, sim, dir).toString();
    if (!dmRet.isEmpty() && dmRet.split("|").size() == 3) {
        QStringList retList = dmRet.split("|");
        int index = retList.at(0).toInt();
        outX = retList.at(1).toInt();
        outY = retList.at(2).toInt();
        return index;
    } else {
        outX = -1;
        outY = -1;
        return -1;
    }
}

int DmWrapper::findPic(const QRect &rect, const QString &picName, QPoint &outPoint, int dir, double sim, const QString &deltaColor)
{
    int outX = -1;
    int outY = -1;
    int index = findPic(rect.left(), rect.top(), rect.right(), rect.bottom(), picName, outX, outY, dir, sim, deltaColor);
    outPoint.setX(outX);
    outPoint.setY(outY);

    return index;
}

bool DmWrapper::moveTo(int x, int y)
{
    return dm->dynamicCall("MoveTo(int, int)", x, y).toInt() == 1;
}

bool DmWrapper::moveTo(const QPoint &pos)
{
    return moveTo(pos.x(), pos.y());
}

bool DmWrapper::leftClick()
{
    return commonMethod("LeftClick()");
}

bool DmWrapper::leftClick(int x, int y)
{
    if (moveTo(x, y)) {
        return leftClick();
    }
    return false;
}

bool DmWrapper::leftClick(const QPoint &pos)
{
    return leftClick(pos.x(), pos.y());
}

bool DmWrapper::rightClick()
{
    return commonMethod("RightClick()");
}

QString DmWrapper::readString(int hwnd, const QString &address, int type, int len)
{
    return dm->dynamicCall("ReadString(int, QString, int, int)", hwnd, address, type, len).toString();
}

bool DmWrapper::commonMethod(const QString &method)
{
    return dm->dynamicCall(method.toLatin1().data()).toInt() == 1;
}

