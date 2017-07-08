/******************************************************************** 
* author 周翔 
* e-mail 604487178@qq.com 
* blog http://blog.csdn.net/zhx6044 
**********************************************************************/  
  
#ifndef TABWORKSPACE_H  
#define TABWORKSPACE_H  
  
#include <QTabWidget>  
#include <QTabBar>  
#include <QToolBar>  
#include <QAction>  
#include <QMenu>  
#include <QToolButton>  
  
  
  
  
class TabWorkSpace : public QTabWidget  
{  
    Q_OBJECT  
public:  
    explicit TabWorkSpace(QWidget *parent = 0);  
      
signals:  
      
public slots:  
  
protected:  
    void resizeEvent(QResizeEvent *e);  
  
  
private slots:  
    void slt_newTab();  
  
    void slt_closeTab(int index);  
  
    void slt_showTab(QAction *a);  
private:  
  
    enum RESETFLAG{NEW, CLOSE, NORMAL, SPECIAL};  
  
    QToolBar *tab_control;  
    QAction *new_tab;  
    QAction *list_tabs;  
    QWidget *padding_widget;  
  
  
    void initTabControl();  
    /** 
     * @brief resetTabBar 重置TabBar 
     */  
    void resetTabBar(RESETFLAG flag);  
  
  
    void setListTabs();  
  
  
  
  
      
};  
  
#endif // TABWORKSPACE_H  
  
/******************************************************************** 
* author 周翔 
* e-mail 604487178@qq.com 
* blog http://blog.csdn.net/zhx6044 
**********************************************************************/  
  
#include "tabworkspace.h"  
#include <QDebug>  
  
TabWorkSpace::TabWorkSpace(QWidget *parent) :  
    QTabWidget(parent)  
{  
    this->addTab(new QWidget,"utitle");  
    this->addTab(new QWidget,"utitle");  
    this->setUsesScrollButtons(true);  
    this->setTabsClosable(true);  
    this->setMovable(true);  
    initTabControl();  
    this->setCornerWidget(tab_control);  
    resetTabBar(NORMAL);  
  
    connect(this,SIGNAL(tabCloseRequested(int)),this,SLOT(slt_closeTab(int)));  
}  
  
void TabWorkSpace::resizeEvent(QResizeEvent *e)  
{  
    resetTabBar(NORMAL);  
    QTabWidget::resizeEvent(e);  
  
}  
  
void TabWorkSpace::resetTabBar(RESETFLAG flag)  
{  
    QSize size = this->size();  
    int tabsWidth = 0;  
    int tabsHeight = tabBar()->height();  
    int tabs = count();  
    if (flag == NEW || flag == NORMAL) {  
        for (int i = 0;i < tabs;++i) {  
            tabsWidth += tabBar()->tabRect(i).width();  
        }  
    } else {  
        for (int i = 0;i < tabs - 1;++i) {  
            tabsWidth += tabBar()->tabRect(i).width();  
        }  
    }  
  
    if (size.width() > tabsWidth) {  
        //  
        if (flag == SPECIAL) {  
            padding_widget->setMinimumWidth(size.width() - tabsWidth - 40);  
  
        } else {  
            padding_widget->setMinimumWidth(size.width() - tabsWidth - 35);  
        }  
        list_tabs->setVisible(false);  
    } else {  
        //  
        list_tabs->setVisible(true);  
        setListTabs();  
        qDebug() << "?";  
        padding_widget->setMinimumWidth(0);  
  
    }  
    padding_widget->setMinimumHeight(tabsHeight);  
}  
  
void TabWorkSpace::initTabControl()  
{  
    tab_control = new QToolBar();  
    QList<QAction*> actions;  
    new_tab = new QAction("+",tab_control);  
    list_tabs = new QAction("V",tab_control);  
    list_tabs->setVisible(false);  
    actions << new_tab << list_tabs;  
    tab_control->addActions(actions);  
    padding_widget = new QWidget();  
    tab_control->addWidget(padding_widget);  
    tab_control->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);  
  
    connect(new_tab,SIGNAL(triggered()),this,SLOT(slt_newTab()));  
}  
  
void TabWorkSpace::slt_newTab()  
{  
    this->addTab(new QWidget,"utitle");  
    if (!tabsClosable()) {  
        setTabsClosable(true);  
    }  
    resetTabBar(NEW);  
}  
  
void TabWorkSpace::slt_closeTab(int index)  
{  
    widget(index)->deleteLater();  
    resetTabBar(CLOSE);  
    if (count() == 2) {  
        setTabsClosable(false);  
        resetTabBar(SPECIAL);  
    }  
  
  
  
}  
  
void TabWorkSpace::setListTabs()  
{  
    QMenu *list = new QMenu();  
    int c = count();  
    for (int i = 0;i < c;++i) {  
        QAction *action = new QAction(tabText(i),list);  
        action->setProperty("index", i);  
        list->addAction(action);  
    }  
    QMenu *old = list_tabs->menu();  
    delete old;  
    list_tabs->setMenu(list);  
    connect(list,SIGNAL(triggered(QAction*)),this,SLOT(slt_showTab(QAction*)));  
  
  
  
}  
  
void TabWorkSpace::slt_showTab(QAction *a)  
{  
   // QAction *_sender = static_cast<QAction*> (sender());  
    int index = a->property("index").toInt();  
    setCurrentIndex(index);  
}  
  
  
/******************************************************************** 
* author 周翔 
* e-mail 604487178@qq.com 
* blog http://blog.csdn.net/zhx6044 
**********************************************************************/  
  
#include <QApplication>  
  
#include "tabworkspace.h"  
  
  
int main(int argc, char *argv[])  
{  
    QApplication a(argc, argv);  
  
    TabWorkSpace tws;  
    tws.resize(640,380);  
    tws.show();  
      
    return a.exec();  
}  