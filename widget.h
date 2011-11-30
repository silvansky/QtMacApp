#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#ifdef Q_WS_MAC
# include "macintegration.h"
#endif

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    
private slots:
    void on_badgeEdit_textChanged(const QString &text);

    void on_overlayButton_clicked();

private:
    Ui::Widget *ui;
#ifdef Q_WS_MAC
    MacIntegration * macIntegration;
#endif
};

#endif // WIDGET_H
