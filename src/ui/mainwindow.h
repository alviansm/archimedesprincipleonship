#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QWidgetAction>
#include <QToolBar>

#include "../widgets/stabilityvisualwidget.h"
#include "../widgets/cargoitemwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    StabilityVisualWidget *m_visualWidget;
};

#endif // MAINWINDOW_H
