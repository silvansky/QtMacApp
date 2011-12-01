#include "macintegration.h"
#include "myprivate.h"
#include <QApplication>

extern void qt_mac_set_dock_menu(QMenu *);

MacIntegration::MacIntegration(QObject *parent) :
    QObject(parent)
{
    connect(MyPrivate::instance(), SIGNAL(dockClicked()), SIGNAL(dockClicked()));
    connect(qApp, SIGNAL(focusChanged(QWidget*,QWidget*)), SLOT(onFocusChanged(QWidget*,QWidget*)));

    MyPrivate::installCustomFrame();
    MyPrivate::setCustomBorderColor(QColor(126, 161, 177));
    MyPrivate::setCustomTitleColor(QColor(255, 255, 255));

    // init menus
    _macMenuBar = new QMenuBar(NULL);

    _windowMenu = new QMenu;
    _windowMenu->menuAction()->setText("Window");
    _macMenuBar->addMenu(_windowMenu);

    closeAction = new QAction("Close Window", _windowMenu);
    closeAction->setShortcut(QKeySequence("Ctrl+W"));
    connect(closeAction, SIGNAL(triggered()), SLOT(onCloseAction()));
    _windowMenu->addAction(closeAction);

    minimizeAction = new QAction("Minimize", _windowMenu);
    minimizeAction->setShortcut(QKeySequence("Ctrl+M"));
    connect(minimizeAction, SIGNAL(triggered()), SLOT(onMinimizeAction()));
    _windowMenu->addAction(minimizeAction);

    zoomAction = new QAction("Zoom", _windowMenu);
    connect(zoomAction, SIGNAL(triggered()), SLOT(onZoomAction()));
    _windowMenu->addAction(zoomAction);

    _dockMenu = new QMenu;
    _dockMenu->addAction("Test!");
    qt_mac_set_dock_menu(_dockMenu);
}

void MacIntegration::setDockBadge(const QString & text)
{
    MyPrivate::setDockBadge(text);
}

void MacIntegration::setDockOverlay(QWidget * overlay)
{
    MyPrivate::setDockOverlay(overlay);
}

QMenu * MacIntegration::dockMenu()
{
    return _dockMenu;
}

void MacIntegration::requestAttention()
{
    MyPrivate::requestAttention();
}

void MacIntegration::onCloseAction()
{
    if (QApplication::activeWindow())
        QApplication::activeWindow()->close();
}

void MacIntegration::onMinimizeAction()
{
    if (QApplication::activeWindow())
        QApplication::activeWindow()->showMinimized();
}

void MacIntegration::onZoomAction()
{
    if (QApplication::activeWindow())
        if (QApplication::activeWindow()->isMaximized())
            QApplication::activeWindow()->showNormal();
        else
            QApplication::activeWindow()->showMaximized();
}

void MacIntegration::onFocusChanged(QWidget * old, QWidget * now)
{
    Q_UNUSED(old)
    if (now)
    {
        closeAction->setEnabled(true);
        minimizeAction->setEnabled(true);
    }
    else
    {
        closeAction->setEnabled(false);
        minimizeAction->setEnabled(false);
    }
}
