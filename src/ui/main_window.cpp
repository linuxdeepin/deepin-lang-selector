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

#include "ui/main_window.h"

#include <QApplication>
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QResizeEvent>
#include <QStackedLayout>

#include "base/file_util.h"
#include "service/settings_manager.h"
#include "ui/frames/select_language_frame.h"
#include "ui/utils/widget_util.h"
#include "ui/widgets/pointer_button.h"

namespace installer {

MainWindow::MainWindow()
    : QWidget(),
      pages_(),
      prev_page_(PageId::NullId),
      current_page_(PageId::NullId),
      log_file_(),
      auto_install_(false) {
  this->setObjectName("main_window");

  this->initUI();
  this->initPages();
  this->initConnections();
}

void MainWindow::fullscreen() {
  ShowFullscreen(this);
}

void MainWindow::resizeEvent(QResizeEvent* event) {
  this->updateBackground();
  QWidget::resizeEvent(event);
}

void MainWindow::initConnections() {
//  connect(select_language_frame_, &SelectLanguageFrame::finished,
//          this, &MainWindow::goNextPage);
}

void MainWindow::initPages() {
  select_language_frame_ = new SelectLanguageFrame(this);
  pages_.insert(PageId::SelectLanguageId,
                stacked_layout_->addWidget(select_language_frame_));
}

void MainWindow::initUI() {
  background_label_ = new QLabel(this);

  close_button_ = new PointerButton();
  close_button_->setObjectName("close_button");
  close_button_->setFlat(true);
  close_button_->setFocusPolicy(Qt::TabFocus);
  close_button_->setFixedSize(12, 12);
  close_button_->setStyleSheet(ReadFile(":/styles/close_button.css"));
  QHBoxLayout* close_layout = new QHBoxLayout();
  close_layout->setContentsMargins(0, 0, 0, 0);
  close_layout->setSpacing(0);
  close_layout->addStretch();
  close_layout->addWidget(close_button_);
  QFrame* close_button_wrapper = new QFrame();
  close_button_wrapper->setFixedHeight(16);
  // Add 4px at top and right margin.
  close_button_wrapper->setContentsMargins(0, 4, 4, 0);
  close_button_wrapper->setLayout(close_layout);

  stacked_layout_ = new QStackedLayout();

  QVBoxLayout* vbox_layout = new QVBoxLayout();
  vbox_layout->setContentsMargins(0, 0, 0, 0);
  vbox_layout->setSpacing(0);
//  vbox_layout->addWidget(close_button_wrapper);
  vbox_layout->addLayout(stacked_layout_);
  vbox_layout->addSpacing(32);

  this->setLayout(vbox_layout);
  this->setContentsMargins(0, 0, 0, 0);
  this->setWindowFlags(Qt::FramelessWindowHint);
}


void MainWindow::updateBackground() {
  if (!background_label_) {
    qWarning() << "background_label is not initialized!";
    return;
  }
  const QString image_path = GetWindowBackground();
  // Other platforms may have performance issue.
  const QPixmap pixmap =
      QPixmap(image_path).scaled(size(), Qt::KeepAspectRatioByExpanding);
  background_label_->setPixmap(pixmap);
  background_label_->setFixedSize(size());
}

}  // namespace installer
