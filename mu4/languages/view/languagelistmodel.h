//=============================================================================
//  MuseScore
//  Music Composition & Notation
//
//  Copyright (C) 2020 MuseScore BVBA and others
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//=============================================================================
#ifndef MU_LANGUAGES_LANGUAGELISTMODEL_H
#define MU_LANGUAGES_LANGUAGELISTMODEL_H

#include <QAbstractListModel>

#include "modularity/ioc.h"
#include "../ilanguagescontroller.h"
#include "async/asyncable.h"

namespace mu {
namespace languages {
class LanguageListModel : public QAbstractListModel, async::Asyncable
{
    Q_OBJECT

    INJECT(languages, ILanguagesController, languagesController)

public:
    LanguageListModel(QObject* parent = nullptr);

    enum Roles {
        rName = Qt::UserRole + 1,
        rFileSize,
        rStatus,
        rIsCurrent
    };

    QVariant data(const QModelIndex& index, int role) const override;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QHash<int,QByteArray> roleNames() const override;

    Q_INVOKABLE void load();
    Q_INVOKABLE void updateList();
    Q_INVOKABLE void install(int index);
    Q_INVOKABLE void uninstall(int index);
    Q_INVOKABLE void setLanguage(int index);

private:
    QHash<int, QByteArray> m_roles;
    QList<Language> m_list;
};
}
}

#endif // MU_LANGUAGES_LANGUAGELISTMODEL_H
