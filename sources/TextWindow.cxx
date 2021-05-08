#include "TextWindow.hxx"

//--- public constructors ---

TextWindow::TextWindow(QWidget *parent)
: QWidget(parent), Ui::TextWindow()
{
}

TextWindow::~TextWindow()
{
}

//--- protected methods ---

void TextWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslateUi(this);

    QWidget::changeEvent(event);
}
