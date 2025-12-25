#ifndef GUI_WINDOWS_ABOUT_ABOUT_H
#define GUI_WINDOWS_ABOUT_ABOUT_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

/**
 * @brief The About class provides an "about" modal dialog window.
 */
class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = nullptr);
};

#endif // GUI_WINDOWS_ABOUT_ABOUT_H
