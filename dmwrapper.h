#ifndef DMWRAPPER_H
#define DMWRAPPER_H

#include <QAxObject>
#include <QRect>

class DmWrapper : public QObject
{
    Q_OBJECT

public:
    explicit DmWrapper(const QString &c, QObject *parent = 0);
    ~DmWrapper();

    bool isLoaded();

    /**!
     * dm COM methods
     *
     */
    // string Ver()
    QString ver();

    // long  GetLastError()
    int getLastError();

    // long GetMousePointWindow()
    int getMousePointWindow();

    // string GetWindowTitle(hwnd)
    QString getWindowTitle(int hWnd);

    // long BindWindow(hwnd,display,mouse,keypad,mode)
    bool bindWindow(int hwnd, const QString &display = "normal", const QString &mouse = "windows", const QString &keypad = "windows", int mode = 0);

    // long SetPath(path)
    bool setPath(const QString &path);

    // long LoadPic(pic_name)
    bool loadPic(const QString &picName);

    // long FreePic(pic_name)
    bool freePic(const QString &picName);

    // string FindPic(x1, y1, x2, y2, pic_name, delta_color,sim, dir)
    int findPic(int x1, int y1, int x2, int y2, const QString &picName, int &outX, int &outY, int dir = 0, double sim = 0.9, const QString &deltaColor = "000000");
    int findPic(const QRect &rect, const QString &picName, QPoint &outPoint, int dir = 0, double sim = 0.9, const QString &deltaColor = "000000");

    // long MoveTo(x,y)
    bool moveTo(int x, int y);
    bool moveTo(const QPoint &pos);

    // long LeftClick()
    bool leftClick();
    bool leftClick(int x, int y);
    bool leftClick(const QPoint &pos);

    // long RightClick()
    bool rightClick();

    // string ReadString(hwnd,addr,type,len)
    QString readString(int hwnd, const QString &address, int type, int len);

private:
    // common methods without parameters(and return 0 for failed, 1 for success)
    bool commonMethod(const QString &method);

private:
    QAxObject *dm;
};

#endif // DMWRAPPER_H
