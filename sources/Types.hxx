#pragma once

#include <QObject>

namespace Types
{
    enum class Language {
        Dutch,
        English,
        French,
        Italian,
        German,
        Spanish
    };
}

Q_DECLARE_METATYPE(Types::Language)

const QString languageToString(const Types::Language lang);
Types::Language stringToLanguage(const QString &str);
