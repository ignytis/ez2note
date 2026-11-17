#include "screen.hpp"

#include "buffers/filebuffer.hpp"

using namespace Ez2note::Gui::Windows::Main;

Screen::Screen(QWidget* parent, Ez2note::Config& config)
    : QStackedWidget(parent), config(config) {}

Buffers::AbstractBuffer* Screen::OpenNewFile() {
    Buffers::FileBuffer* newBuffer = new Buffers::FileBuffer(this, config);
    addWidget(newBuffer);
    SetActiveBuffer(newBuffer);
    return newBuffer;
}

Buffers::AbstractBuffer* Screen::OpenFile(const QString& filePath) {
    Buffers::FileBuffer* newBuffer =
        new Buffers::FileBuffer(this, config, filePath);
    addWidget(newBuffer);
    SetActiveBuffer(newBuffer);
    return newBuffer;
}

void Screen::CloseBuffer(Buffers::AbstractBuffer* buffer) {
    // QStackedWidget switches to another page automatically
    removeWidget(buffer);
    buffer->deleteLater();
}

Buffers::AbstractBuffer* Screen::GetActiveBuffer() const {
    return qobject_cast<Buffers::AbstractBuffer*>(currentWidget());
}

void Screen::SetActiveBuffer(Buffers::AbstractBuffer* buffer) {
    setCurrentWidget(buffer);
}

void Screen::Undo() {
    if (Buffers::AbstractBuffer* b = GetActiveBuffer()) b->Undo();
}

void Screen::Redo() {
    if (Buffers::AbstractBuffer* b = GetActiveBuffer()) b->Redo();
}

void Screen::SetShowLineNumbers(bool show) {
    if (Buffers::AbstractBuffer* b = GetActiveBuffer()) {
        b->SetShowLineNumbers(show);
    }
}

void Screen::SetWordWrap(bool wrap) {
    if (Buffers::AbstractBuffer* b = GetActiveBuffer()) b->SetWordWrap(wrap);
}

bool Screen::IsModified() const {
    Buffers::AbstractBuffer* b = GetActiveBuffer();
    return b ? b->IsModified() : false;
}
