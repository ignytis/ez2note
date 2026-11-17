#ifndef GUI_WINDOWS_MAIN_SCREEN_HPP
#define GUI_WINDOWS_MAIN_SCREEN_HPP

#include <QStackedWidget>
#include <QString>

#include "../../../config.hpp"
#include "buffers/abstractbuffer.hpp"

namespace Ez2note {
namespace Gui {
namespace Windows {
namespace Main {

/** Central widget of the main window. Shows the active buffer. */
class Screen : public QStackedWidget {
    Q_OBJECT

   public:
    Screen(QWidget* parent, Ez2note::Config& config);

    Buffers::AbstractBuffer* OpenNewFile();
    Buffers::AbstractBuffer* OpenFile(const QString& filePath);
    void CloseBuffer(Buffers::AbstractBuffer* buffer);

    Buffers::AbstractBuffer* GetActiveBuffer() const;
    void SetActiveBuffer(Buffers::AbstractBuffer* buffer);

    // Forwarding methods
    void Undo();
    void Redo();
    void SetShowLineNumbers(bool show);
    void SetWordWrap(bool wrap);
    bool IsModified() const;

   private:
    Ez2note::Config& config;
};

}  // namespace Main
}  // namespace Windows
}  // namespace Gui
}  // namespace Ez2note

#endif  // GUI_WINDOWS_MAIN_SCREEN_HPP
