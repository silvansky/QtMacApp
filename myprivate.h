#ifndef MYPRIVATE_H
#define MYPRIVATE_H

#include <QWidget>

class MyPrivate : public QObject
{
    Q_OBJECT
private:
    static MyPrivate * p;
    MyPrivate();
public:
    static MyPrivate * instance();
    void emitClick();
    static void setDockBadge(const QString & badgeText);
    static void setDockOverlay(QWidget * overlay);
    static void installCustomFrame();
    static void setCustomBorderColor(const QColor & color);
    static void setCustomTitleColor(const QColor & color);
signals:
    void dockClicked();
};

#endif // MYPRIVATE_H
