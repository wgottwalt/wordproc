#include "SearchWindow.hxx"

//--- public constructors ---

SearchWindow::SearchWindow(QWidget *parent)
: QWidget(parent), Ui::SearchWindow()
{
    setupUi(this);
}

SearchWindow::~SearchWindow()
{
}

//--- protected methods ---

void SearchWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslateUi(this);

    QWidget::changeEvent(event);
}
