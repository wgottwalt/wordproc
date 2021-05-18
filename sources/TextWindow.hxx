#pragma once

#include <QWidget>
#include "ui_TextWindow.h"
#include "Types.hxx"

class TextWindow : public QWidget, public Ui::TextWindow {
    Q_OBJECT
public:
    //--- public constructors ---
    TextWindow(QWidget *parent = nullptr);
    TextWindow(const TextWindow &rhs) = delete;
    TextWindow(TextWindow &&rhs) = delete;
    virtual ~TextWindow();

    //--- public operators ---
    TextWindow &operator=(const TextWindow &rhs) = delete;
    TextWindow &operator=(TextWindow &&rhs) = delete;

    //--- public methods ---
    void formatText(const Types::Format format);

protected:
    //--- protected methods ---
    virtual void changeEvent(QEvent *event) override final;
    void setupActions();
    void updateWindowTitle();

private:
    //--- private properties ---
    QString _filename;
    QString _search_string;
    quint64 _id;
    bool _text_changed;
};
