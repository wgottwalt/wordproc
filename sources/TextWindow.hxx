#pragma once

#include <QWidget>
#include "ui_TextWindow.h"

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

protected:
    //--- protected methods ---
    virtual void changeEvent(QEvent *event) override final;
};
