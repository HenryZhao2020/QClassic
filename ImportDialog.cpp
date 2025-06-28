#include "ImportDialog.h"
#include "MainWindow.h"
#include "SideBar.h"
#include "Library.h"

#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>

ImportDialog::ImportDialog(MainWindow *win)
    : QDialog{win}, sideBar{win->getSideBar()},
    vboxLayout{new QVBoxLayout{this}},
    browseButton{new QPushButton{tr("Import Media File"), this}},
    titleField{new QLineEdit{this}}, composerField{new QComboBox{this}},
    genreField{new QComboBox{this}}, playlistField{new QComboBox{this}},
    importButton{new QPushButton{tr("Import"), this}} {

    setModal(true);

    vboxLayout->setAlignment(Qt::AlignTop);
    vboxLayout->addWidget(browseButton, 0, Qt::AlignCenter);
    vboxLayout->addWidget(new QLabel{tr("Title:"), this});
    vboxLayout->addWidget(titleField);

    connect(browseButton, &QPushButton::clicked, this, &ImportDialog::browseFile);

    for (auto item : Library::instance().getComposers()) {
        composerField->addItem(item->getName());
    }
    for (auto item : Library::instance().getGenres()) {
        genreField->addItem(item->getName());
    }
    for (auto item : Library::instance().getPlaylists()) {
        playlistField->addItem(item->getName());
    }

    addMusicField(tr("Composer") + ":", composerField);
    addMusicField(tr("Genre") + ":", genreField);
    addMusicField(tr("Playlist") + ":", playlistField);

    connect(importButton, &QPushButton::clicked, this, &ImportDialog::importMusic);
    vboxLayout->addWidget(importButton);

    setEditEnabled(false);
}

void ImportDialog::browseFile() {
    QString path = QFileDialog::getOpenFileName();
    if (path.isEmpty()) return;

    filePath = QFileInfo(path).absoluteFilePath();

    QString title = QFileInfo(path).completeBaseName();
    titleField->setText(title);

    for (auto composer : Library::instance().getComposers()) {
        if (title.contains(composer->getLastName())) {
            composerField->setCurrentText(composer->getName());
            break;
        }
    }

    for (auto genre : Library::instance().getGenres()) {
        if (title.contains(genre->getName())) {
            genreField->setCurrentText(genre->getName());
            break;
        }
    }

    setEditEnabled(true);
}

void ImportDialog::setEditEnabled(bool enabled) {
    browseButton->setEnabled(!enabled);
    titleField->setEnabled(enabled);
    composerField->setEnabled(enabled);
    genreField->setEnabled(enabled);
    playlistField->setEnabled(enabled);
}

void ImportDialog::addMusicField(const QString &label, QComboBox *box) {
    box->setEditable(true);
    box->setCurrentText("");
    vboxLayout->addWidget(new QLabel{label, this});
    vboxLayout->addWidget(box);
}

void ImportDialog::importMusic() {
    QString title = titleField->text();
    if (title.isEmpty()) {
        QMessageBox::critical(this, "", "Title must not be empty!");
        return;
    }

    QString composerName = composerField->currentText();
    auto music = Library::instance().findMusic(title, composerName);
    if (music) {
        auto response = QMessageBox::question(
            this, "", "Music with the same title and composer already exists!\n"
                      "Do you want to replace the original?");
        if (response != QMessageBox::Yes) return;
    }

    QString genreName = genreField->currentText();
    QString playlistName = playlistField->currentText();

    Composer *composer = nullptr;
    Genre *genre = nullptr;
    Playlist *playlist = nullptr;

    if (!composerName.isEmpty()) {
        composer = Library::instance().findComposer(composerName);
        if (!composer) {
            composer = new Composer{composerName};
            Library::instance().addComposer(composer);
            sideBar->addItem(composerName, Category::Composer);
        }
    }

    if (!genreName.isEmpty()) {
        auto genre = Library::instance().findGenre(genreName);
        if (!genre) {
            genre = new Genre{genreName};
            Library::instance().addGenre(genre);
            sideBar->addItem(genreName, Category::Genre);
        }
    }

    if (!playlistName.isEmpty()) {
        playlist = Library::instance().findPlaylist(playlistName);
        if (!playlist) {
            playlist = new Playlist{playlistName};
            Library::instance().addPlaylist(playlist);
            sideBar->addItem(playlistName, Category::Playlist);
        }
    }

    music = new Music{title, composer, genre, playlist, filePath};
    Library::instance().addMusic(music);

    close();
}
