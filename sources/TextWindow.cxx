#include "TextWindow.hxx"

//--- public constructors ---

TextWindow::TextWindow(QWidget *parent)
: QWidget(parent), Ui::TextWindow()
{
    setupUi(this);
}

TextWindow::~TextWindow()
{
}

//--- public methods ---

void TextWindow::formatText(const Types::Format format)
{
    switch (format)
    {
        case Types::Format::Undo:
            wid_text->undo();
            return;

        case Types::Format::Redo:
            wid_text->redo();
            return;

        case Types::Format::Cut:
            wid_text->cut();
            return;

        case Types::Format::Copy:
            wid_text->copy();
            return;

        case Types::Format::Paste:
            wid_text->paste();
            return;

        case Types::Format::Clear:
            wid_text->textCursor().clearSelection();
            return;

        case Types::Format::SelectAll:
            wid_text->selectAll();
            return;

        case Types::Format::Bold:
            return;

        case Types::Format::Italic:
            wid_text->setFontItalic(!wid_text->fontItalic());
            return;

        case Types::Format::Underline:
            wid_text->setFontUnderline(!wid_text->fontUnderline());
            return;

        case Types::Format::Left:
            return;
        case Types::Format::Center:
            return;
        case Types::Format::Right:
            return;
        case Types::Format::Fill:
            return;
    }
}

//--- protected methods ---

void TextWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslateUi(this);

    QWidget::changeEvent(event);
}

void TextWindow::setupActions()
{
    // toolbar buttons
}
