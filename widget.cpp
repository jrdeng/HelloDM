#include "widget.h"
#include "ui_widget.h"
#include "dmwrapper.h"

#include <QMessageBox>
#include <Windows.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    dm(0)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    Q_UNUSED(event);

    if (!dm) {
        return;
    }

    if (event->key() == Qt::Key_F1) {
        int hWnd = dm->getMousePointWindow();
        QString title = dm->getWindowTitle(hWnd);
        ui->lineEdit_hwnd->setText(title);
    }
}

void Widget::on_pushButton_loadDm_clicked()
{
    if (dm) {
        return;
    }

    // load ActiveX
    CoInitializeEx(NULL, COINIT_MULTITHREADED);
    dm = new DmWrapper(ui->lineEdit_dmClsId->text(), this);

    if (dm->isLoaded()) {
        QMessageBox::information(this, "DM", QString("dm is loaded, version: %1").arg(dm->ver()));

        // disable
        ui->pushButton_loadDm->setEnabled(false);
        // enable others
        ui->lineEdit_hwnd->setEnabled(true);
    } else {
        QMessageBox::warning(this, "DM", "can not load dm, please make sure it's registered");
        delete dm;
        dm = 0;
    }
}

