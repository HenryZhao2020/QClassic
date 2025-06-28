#pragma once

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>

class MainWindow;
class SideBar;

class ImportDialog : public QDialog {
    Q_OBJECT

public:
    ImportDialog(MainWindow *win);

private:
    void browseFile();
    void addMusicField(const QString &label, QComboBox *box);
    void setEditEnabled(bool enabled);
    void importMusic();

    SideBar *sideBar;
    QVBoxLayout *vboxLayout;
    QPushButton *browseButton;
    QString filePath;
    QLineEdit *titleField;
    QComboBox *composerField;
    QComboBox *genreField;
    QComboBox *playlistField;
    QPushButton *importButton;
};
