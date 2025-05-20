#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../ui/vesselinputform.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create the visual widget (the interactive ship box)
    m_visualWidget = new StabilityVisualWidget(this);
    setCentralWidget(m_visualWidget);

    // When the box is clicked, open the VesselInputForm
    connect(m_visualWidget, &StabilityVisualWidget::clicked, this, [this]() {
        VesselInputForm *form = new VesselInputForm(this);
        form->setVessel(m_visualWidget->vessel());

        // When the form emits vesselChanged, update visual and delete form
        connect(form, &VesselInputForm::vesselChanged, this, [this, form](const Vessel &v) {
            m_visualWidget->setVessel(v);
            form->close();
            form->deleteLater();
        });

        form->exec();
    });

    QToolBar* cargoToolBar = new QToolBar("Cargo Items", this);
    cargoToolBar->setIconSize(QSize(24, 24));  // match widget size
    cargoToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);  // if you want labels
    cargoToolBar->setFixedWidth(40);  // or enough for widget + margin
    addToolBar(Qt::LeftToolBarArea, cargoToolBar);

    for (int i = 1; i <= 3; ++i) {
        CargoItemWidget* item = new CargoItemWidget(QString("Cargo %1").arg(i), false);

        QWidgetAction* cargoAction = new QWidgetAction(this);
        cargoAction->setDefaultWidget(item);

        cargoToolBar->addAction(cargoAction);

        cargoToolBar->setStyleSheet(R"(
        QToolBar {
            background: #f0f0f0;
            spacing: 10px;
            padding: 10px;
            }
        )");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
