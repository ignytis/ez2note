#include "filebuffer.hpp"

#include <QFile>
#include <QFileInfo>

using namespace Ez2note::Gui::Windows::Main::Buffers;

FileBuffer::FileBuffer(QWidget* parent, Ez2note::Config& config,
                       const QString& filePath)
    : AbstractBuffer(parent, config), filePath(filePath) {
    if (!filePath.isEmpty()) {
        LoadFile(filePath);
    }
}

bool FileBuffer::LoadFile(const QString& path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) return false;
    textEdit->setPlainText(QString::fromUtf8(file.readAll()));
    textEdit->document()->setModified(false);
    filePath = path;
    return true;
}

bool FileBuffer::WriteFile(const QString& path) {
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) return false;
    file.write(textEdit->toPlainText().toUtf8());
    textEdit->document()->setModified(false);
    return true;
}

bool FileBuffer::SaveFile() {
    return filePath.isEmpty() ? false : WriteFile(filePath);
}

bool FileBuffer::SaveFileAs(const QString& path) {
    if (!WriteFile(path)) return false;
    filePath = path;
    return true;
}

bool FileBuffer::HasFile() const { return !filePath.isEmpty(); }

QString FileBuffer::GetTitle() const {
    return filePath.isEmpty() ? "Untitled" : QFileInfo(filePath).fileName();
}
