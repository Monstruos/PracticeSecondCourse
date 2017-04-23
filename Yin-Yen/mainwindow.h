#ifndef STARTMENU_H
#define STARTMENU_H

#include <QtGui/QWindow>
#include <QtGui/QOpenGLFunctions>
#include <QDebug>

class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;

class MainWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit MainWindow(QWindow *parent = 0);
    ~MainWindow();

    virtual void render(QPainter *painter);
    virtual void render();

    virtual void initialize();

    void setAnimating(bool animating);

public slots:
    void renderLater();
    void renderNow();

protected:
    bool event(QEvent *event) override;

    void exposeEvent(QExposeEvent *event) override;

private:
    bool m_animating;

    QOpenGLContext *m_context;
    QOpenGLPaintDevice *m_device;
};

#endif // STARTMENU_H
