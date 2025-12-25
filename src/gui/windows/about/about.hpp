#ifndef GUI_WINDOWS_ABOUT_ABOUT_HPP
#define GUI_WINDOWS_ABOUT_ABOUT_HPP

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

#include "../../../constants.hpp"

/**
 * @brief The About class provides an "about" modal dialog window.
 */
class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = nullptr);
};

#endif // GUI_WINDOWS_ABOUT_ABOUT_HPP
