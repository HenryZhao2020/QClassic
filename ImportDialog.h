#pragma once

#include <QDialog>
#include <QUrl>

class LibraryView;
class QLineEdit;
class QComboBox;

class ImportDialog : public QDialog {
    Q_OBJECT

    LibraryView *libView;
    QUrl source;

    QLineEdit *titleField;
    QComboBox *composerBox;
    QComboBox *playlistBox;

    void import();

public:
    ImportDialog(LibraryView *libView, const QUrl &source);
};
