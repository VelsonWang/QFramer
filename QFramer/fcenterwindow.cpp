#include "fcenterwindow.h"
#include<QPushButton>
#include<QVBoxLayout>
#include<QQuickWidget>
#include<QWebView>
#include<QPropertyAnimation>
#include<QParallelAnimationGroup>
#include<QEasingCurve>
#include<QLabel>
#include<QTime>
#include"ftitlebar.h"

FCenterWindow::FCenterWindow(QWidget *parent)
    :QFrame(parent)
{
    qDebug("FCenterWindow init");
    initData();
    initUI();
    initConnect();
}

void FCenterWindow::initData()
{
    preindex = 0;
}

void FCenterWindow::initUI()
{
    setObjectName(QString("FCenterWindow"));
    navagationBar = new FNavgationBar();
    stackWidget = new QStackedWidget();

    navlayout = new QBoxLayout(QBoxLayout::TopToBottom);
    navlayout->addWidget(navagationBar);
    navlayout->addWidget(stackWidget);
    navlayout->setContentsMargins(0, 0 ,0 ,0);
    navlayout->setSpacing(0);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(FTitleBar::getInstace());
    mainLayout->addLayout(navlayout);
    mainLayout->setContentsMargins(0, 0 ,0 ,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
}

void FCenterWindow::swicthLayout(QBoxLayout::Direction direction)
{
    navlayout->setDirection(direction);
}


void FCenterWindow::setAlignment(Alignment_Direction direction)
{
    switch (direction) {
    case TopLeft:
        navagationBar->setObjectName(QString("FNavgationBar_bottom"));
        navagationBar->setAlignment_topLeft();
        navagationBar->resize(QSize(stackWidget->width(), navagationBar->height()));
        swicthLayout(QBoxLayout::TopToBottom);
        break;
    case TopCenter:
        navagationBar->setObjectName(QString("FNavgationBar_bottom"));
        navagationBar->setAlignment_topCenter();
        swicthLayout(QBoxLayout::TopToBottom);
        break;
    case TopRight:
        navagationBar->setObjectName(QString("FNavgationBar_bottom"));
        navagationBar->setAlignment_topRight();
        swicthLayout(QBoxLayout::TopToBottom);
        break;
    case RightTop:
        navagationBar->setObjectName(QString("FNavgationBar_left"));
        navagationBar->setAlignment_rightTop();
        swicthLayout(QBoxLayout::RightToLeft);
        navagationBar->resize(QSize(navagationBar->width(), stackWidget->height()));
        break;
    case RightCenter:
        navagationBar->setObjectName(QString("FNavgationBar_left"));
        navagationBar->setAlignment_rightCenter();
        swicthLayout(QBoxLayout::RightToLeft);
        navagationBar->resize(QSize(navagationBar->width(), stackWidget->height()));
        break;
    case RightBottom:
        navagationBar->setObjectName(QString("FNavgationBar_left"));
        navagationBar->setAlignment_rightBottom();
        swicthLayout(QBoxLayout::RightToLeft);
        navagationBar->resize(QSize(navagationBar->width(), stackWidget->height()));
        break;
    case BottomRight:
        navagationBar->setObjectName(QString("FNavgationBar_top"));
        navagationBar->setAlignment_bottomRight();
        swicthLayout(QBoxLayout::BottomToTop);
        break;
    case BottomCenter:
        navagationBar->setObjectName(QString("FNavgationBar_top"));
        navagationBar->setAlignment_bottomCenter();
        swicthLayout(QBoxLayout::BottomToTop);
        break;
    case BottomLeft:
        navagationBar->setObjectName(QString("FNavgationBar_top"));
        navagationBar->setAlignment_bottomLeft();
        swicthLayout(QBoxLayout::BottomToTop);
        break;
    case LeftBottom:
        navagationBar->setObjectName(QString("FNavgationBar_right"));
        navagationBar->setAlignment_leftBottom();
        swicthLayout(QBoxLayout::LeftToRight);
        break;
    case LeftCenter:
        navagationBar->setObjectName(QString("FNavgationBar_right"));
        navagationBar->setAlignment_leftCenter();
        swicthLayout(QBoxLayout::LeftToRight);
        break;
    case LeftTop:
        navagationBar->setObjectName(QString("FNavgationBar_right"));
        navagationBar->setAlignment_leftTop();
        swicthLayout(QBoxLayout::LeftToRight);
        break;
    default:
        break;
    }
}


void FCenterWindow::initConnect()
{
    connect(navagationBar, SIGNAL(indexChanged(int)), this, SLOT(switchscreen(int)));
}


void FCenterWindow::addWidget(const QString &tile, QWidget *widget)
{
    navagationBar->addNavgationTile(tile);
    widget->setObjectName(tile);
    stackWidget->addWidget(widget);
}

void FCenterWindow::switchscreen(const int index)
{
    int n = 0;
    if (index == stackWidget->currentIndex())
    {
        return;
    }
    else if(index > stackWidget->currentIndex())
    {
        n = 2;
    }
    else if (index < stackWidget->currentIndex())
    {
        n = 6;
    }

    stackWidget->setCurrentIndex(index);

//    QTime time;
//    time= QTime::currentTime();
//    qsrand(time.msec()+time.second()*1000);
//    int n = qrand()%9;
//    n = 0;
    switch (n) {
    case 0:
        cloudAntimation(animationTop);
        break;
    case 1:
        cloudAntimation(animationTopRight);
        break;
    case 2:
        cloudAntimation(animationRight);
        break;
    case 3:
        cloudAntimation(animationBottomRight);
        break;
    case 4:
        cloudAntimation(animationBottom);
        break;
    case 5:
        cloudAntimation(animationBottomLeft);
        break;
    case 6:
        cloudAntimation(animationLeft);
        break;
    case 7:
        cloudAntimation(animationTopLeft);
        break;
    case 8:
        cloudAntimation(animationCenter);
        break;
    default:
        break;
    }
    preindex = index;

}


void FCenterWindow::switchscreen()
{
    stackWidget->setCurrentIndex(currentIndex);
}

void FCenterWindow::cloudAntimation(animation_Direction direction)
{
    QLabel* circle = new QLabel(stackWidget->currentWidget());
    circle->setStyleSheet(QString("\
         QLabel{background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(1, 255, 255, 255), stop:0.511364 rgba(255, 255, 0, 255), stop:1 rgba(0, 137, 0, 238));}"\
                                  ));
    circle->setPixmap(stackWidget->widget(preindex)->grab());
    circle->show();
    circle->resize(stackWidget->currentWidget()->size());
    QPropertyAnimation *animation = new QPropertyAnimation(circle, "geometry");

    animation->setDuration(1000);
    animation->setStartValue(circle->geometry());
    switch (direction) {
    case animationTop:
        animation->setEndValue(QRect(circle->x(), circle->y() - 10, circle->width(), 0));
        break;
    case animationTopRight:
        animation->setEndValue(QRect(circle->width(), 0, 0, 0));
        break;
    case animationRight:
        animation->setEndValue(QRect(circle->width() + 10, 0, 0, circle->height()));
        break;
    case animationBottomRight:
        animation->setEndValue(QRect(circle->width(), circle->height(), 0, 0));
        break;
    case animationBottom:
        animation->setEndValue(QRect(0, circle->height() + 10, circle->width(), 0));
        break;
    case animationBottomLeft:
        animation->setEndValue(QRect(0, circle->height(), 0, 0));
        break;
    case animationLeft:
        animation->setEndValue(QRect(-10, 0, 0, circle->height()));
        break;
    case animationTopLeft:
        animation->setEndValue(QRect(0, 0, 0, 0));
        break;
    case animationCenter:
        animation->setEndValue(QRect(circle->width()/2, circle->height()/2, 0, 0));
        break;
    default:
        break;
    }
    animation->setEasingCurve(QEasingCurve::OutCubic);

    QPropertyAnimation* animation_opacity = new QPropertyAnimation(circle, "windowOpacity");
    animation_opacity->setDuration(1000);
    animation_opacity->setStartValue(1);
    animation_opacity->setEndValue(0);
    animation_opacity->setEasingCurve(QEasingCurve::OutCubic);

    QParallelAnimationGroup *group = new QParallelAnimationGroup;

    connect(group,SIGNAL(finished()), circle, SLOT(hide()));
    connect(group,SIGNAL(finished()), circle, SLOT(deleteLater()));
    connect(group,SIGNAL(finished()), group, SLOT(deleteLater()));
    connect(group,SIGNAL(finished()), animation, SLOT(deleteLater()));
    connect(group,SIGNAL(finished()), animation_opacity, SLOT(deleteLater()));
    group->addAnimation(animation);
    group->addAnimation(animation_opacity);
    group->start();
}
