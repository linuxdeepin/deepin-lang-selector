/*
 * Copyright (C) 2017 ~ 2017 Deepin Technology Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INSTALLER_UI_MAIN_WINDOW_H
#define INSTALLER_UI_MAIN_WINDOW_H

#include <QWidget>
#include <QHash>
class QLabel;
class QPushButton;
class QResizeEvent;
class QShortcut;
class QStackedLayout;

class GlobalShortcut;

namespace installer {

class SelectLanguageFrame;

// MainWindow is a fullscreen window of deepin-installer.
// All of ui frames are placed in MainWindow.
// It does following jobs:
//   * draw window background with a blur image;
//   * handles keyboard shortcut like Ctrl+P and Ctrl+L;
//   * handles window navigation (by providing a content area);
//   * quit / abort installation process.
class MainWindow : public QWidget {
  Q_OBJECT

 public:
  MainWindow();

  // Show fullscreen.
  void fullscreen();

 protected:
  // Move close button to appropriate position when window is resized.
  void resizeEvent(QResizeEvent* event) override;

 private:
  enum PageId {
    NullId,  // page not set.
    SelectLanguageId,
  };

  void initConnections();
  void initPages();
  void initUI();
  void updateBackground();

  QLabel* background_label_ = nullptr;
  QPushButton* close_button_ = nullptr;
  // All of frame pages are stored in this layout.
  // And they are referenced by id in |pages_|.
  QStackedLayout* stacked_layout_ = nullptr;

  SelectLanguageFrame* select_language_frame_ = nullptr;

  // To store frame pages, page_name => page_id.
  QHash<PageId, int> pages_;

  // Keep previous page id. It is used by ConfirmQuitPage.
  PageId prev_page_;
  PageId current_page_;

  QString log_file_;
  bool auto_install_;

};

}  // namespace installer

#endif  // INSTALLER_UI_MAIN_WINDOW_H
