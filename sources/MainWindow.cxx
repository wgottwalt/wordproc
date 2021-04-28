#include "MainWindow.hxx"

//--- public constructors ---

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), Ui::MainWindow()
{
    setupUi(this);
}

MainWindow::~MainWindow()
{
}

//--- protected methods ---

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslateUi(this);

    QMainWindow::changeEvent(event);
}
