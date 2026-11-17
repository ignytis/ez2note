#include "abstractbuffer.hpp"

#include <QVBoxLayout>

using namespace Ez2note::Gui::Windows::Main::Buffers;

AbstractBuffer::AbstractBuffer(QWidget* parent, Ez2note::Config& config)
    : QWidget(parent), textEdit(new CodeEditor(this)), config(config) {
    // Initial setup from config
    textEdit->SetShowLineNumbers(
        config.getBool(CONFIG_KEY_EDITOR_SHOW_LINE_NUMBERS));
    textEdit->SetWordWrap(config.getBool(CONFIG_KEY_EDITOR_WORD_WRAP));

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(textEdit);
}

void AbstractBuffer::Undo() { textEdit->undo(); }

void AbstractBuffer::Redo() { textEdit->redo(); }

void AbstractBuffer::SetShowLineNumbers(bool show) {
    textEdit->SetShowLineNumbers(show);
}

void AbstractBuffer::SetWordWrap(bool wrap) { textEdit->SetWordWrap(wrap); }

bool AbstractBuffer::IsModified() const {
    return textEdit->document()->isModified();
}
