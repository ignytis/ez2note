#ifndef GUI_WINDOWS_MAIN_BUFFERS_FILEBUFFER_HPP
#define GUI_WINDOWS_MAIN_BUFFERS_FILEBUFFER_HPP

#include <QString>

#include "abstractbuffer.hpp"

namespace Ez2note {
namespace Gui {
namespace Windows {
namespace Main {
namespace Buffers {

/** Buffer which is backed by a file on disk (or is a new unsaved file). */
class FileBuffer : public AbstractBuffer {
    Q_OBJECT

   public:
    FileBuffer(QWidget* parent, Ez2note::Config& config,
               const QString& filePath = "");
    virtual ~FileBuffer() = default;

    bool LoadFile(const QString& path);
    bool SaveFile();
    bool SaveFileAs(const QString& path);
    bool HasFile() const;

    // Override from AbstractBuffer
    QString GetTitle() const override;

   private:
    bool WriteFile(const QString& path);

    QString filePath;
};

}  // namespace Buffers
}  // namespace Main
}  // namespace Windows
}  // namespace Gui
}  // namespace Ez2note

#endif  // GUI_WINDOWS_MAIN_BUFFERS_FILEBUFFER_HPP
