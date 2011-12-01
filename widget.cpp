#include "widget.h"
#include "ui_widget.h"
#include <QTimer>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    qApp->setQuitOnLastWindowClosed(false);
    setAttribute(Qt::WA_DeleteOnClose, false);
#ifdef Q_WS_MAC
    macIntegration = new MacIntegration(this);
    connect(macIntegration, SIGNAL(dockClicked()), SLOT(show()));
    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), macIntegration, SLOT(requestAttention()));
    timer->start(5000);
#endif
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_badgeEdit_textChanged(const QString &text)
{
#ifdef Q_WS_MAC
    macIntegration->setDockBadge(text);
#endif
}

void Widget::on_overlayButton_clicked()
{
#ifdef Q_WS_MAC
    static bool overlaySet = false;
    if (!overlaySet)
    {
        QLabel * overlay = new QLabel(this);
        overlay->setPixmap(QPixmap(":/habr_logo.png"));
        overlay->setScaledContents(true);
        overlay->setAttribute(Qt::WA_TranslucentBackground, true);
        overlay->setGeometry(0, 0, 16, 16);
        macIntegration->setDockOverlay(overlay);
        ui->overlayButton->setText("Remove");
    }
    else
    {
        macIntegration->setDockOverlay(NULL);
        ui->overlayButton->setText("Add");
    }
    overlaySet = !overlaySet;
#endif
}
