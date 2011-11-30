#ifndef MACINTEGRATION_H
#define MACINTEGRATION_H

#include <QMenuBar>

class MacIntegration : public QObject
{
    Q_OBJECT
public:
    explicit MacIntegration(QObject *parent = 0);
    void setDockBadge(const QString & text);
    void setDockOverlay(QWidget * overlay);
    QMenu * dockMenu();
signals:
    void dockClicked();
protected slots:
    void onCloseAction();
    void onMinimizeAction();
    void onZoomAction();
    void onFocusChanged(QWidget * old, QWidget * now);
private:
    QMenu * _dockMenu;
    QMenuBar * _macMenuBar;
    QMenu * _windowMenu;
    QAction * closeAction;
    QAction * minimizeAction;
    QAction * zoomAction;
};

#endif // MACINTEGRATION_H
