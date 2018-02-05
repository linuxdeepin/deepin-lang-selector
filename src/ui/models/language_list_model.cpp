/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
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

#include "ui/models/language_list_model.h"

#include <QDebug>

#include "base/file_util.h"

namespace installer {

LanguageList GetLanguageList() {
  LanguageList list;
  const QString content(ReadFile(RESOURCES_DIR "/languages.json"));
  const QJsonArray lang_list =
      QJsonDocument::fromJson(content.toUtf8()).array();
  for (const QJsonValue& lang_value : lang_list) {
    const QJsonObject obj = lang_value.toObject();
    LanguageItem item;
    item.name = obj.value("name").toString();
    item.locale = obj.value("locale").toString();
    item.local_name = obj.value("local_name").toString();
    item.timezone = obj.value("timezone").toString();
    list.append(item);
  }
  return list;
}

LanguageListModel::LanguageListModel(QObject* parent)
    : QAbstractListModel(parent),
      lang_list_() {
  this->setObjectName("language_list_model");

  // TODO(xushaohua): Move to init() function.
  lang_list_ = GetLanguageList();
}

QVariant LanguageListModel::data(const QModelIndex& index, int role) const {
  if (role != Qt::DisplayRole) {
    return QVariant();
  }

  if (index.isValid()) {
    return lang_list_.at(index.row()).local_name;
  } else {
    return QVariant();
  }
}

int LanguageListModel::rowCount(const QModelIndex& parent) const {
  Q_UNUSED(parent);
  return lang_list_.length();
}

LanguageItem LanguageListModel::languageItemAt(const QModelIndex& index) const {
  if (index.isValid()) {
    return lang_list_.at(index.row());
  } else {
    return LanguageItem();
  }
}

QModelIndex LanguageListModel::localeIndex(const QString& locale) const {
  for (int index = 0; index < lang_list_.length(); index++) {
    if (lang_list_.at(index).locale == locale) {
      return this->index(index);
    }
  }
  return QModelIndex();
}

}  // namespace installer