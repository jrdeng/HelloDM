#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QKeyEvent>

#include "dmwrapper.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_pushButton_loadDm_clicked();

private:
    Ui::Widget *ui;

    DmWrapper *dm;
};

#endif // WIDGET_H
