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
#ifndef MU_LANGUAGES_LANGUAGESCONTROLLER_H
#define MU_LANGUAGES_LANGUAGESCONTROLLER_H

#include "modularity/ioc.h"
#include "../ilanguagescontroller.h"
#include "../ilanguagesconfiguration.h"
#include "../ilanguageunpacker.h"
#include "iglobalconfiguration.h"

class QTranslator;

namespace mu {
namespace languages {
class LanguagesController : public ILanguagesController
{
    INJECT(languages, ILanguagesConfiguration, configuration)
    INJECT(languages, ILanguageUnpacker, languageUnpacker)
    INJECT(languages, framework::IGlobalConfiguration, globalConfiguration)

public:
    LanguagesController() = default;

    void init();

    Ret refreshLanguages() override;
    ValCh<LanguagesHash> languages() override;
    Ret install(const QString& languageCode) override;
    Ret uninstall(const QString& languageCode) override;

    Ret setLanguage(const QString &languageCode) override;

    RetCh<Language> languageChanged() override;

private:
    RetVal<LanguagesHash> parseLanguagesConfig(const QByteArray& json) const;
    bool isLanguageExists(const QString& languageCode) const;

    RetVal<LanguagesHash> correctLanguagesStates(LanguagesHash& languages) const;

    RetVal<QString> downloadLanguage(const QString& languageCode) const;
    Ret removeLanguage(const QString& languageCode) const;

    Ret loadLanguage(const QString& languageCode);

    void resetLanguageByDefault();

private:
    async::Channel<Language> m_languageChanged;
    QList<QTranslator*> m_translatorList;
};
}
}

#endif // MU_LANGUAGES_LANGUAGESCONTROLLER_H
