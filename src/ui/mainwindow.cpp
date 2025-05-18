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
}

MainWindow::~MainWindow()
{
    delete ui;
}
