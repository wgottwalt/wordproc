#pragma once

#include <QObject>
#include <QString>

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

    enum class Theme {
        Fusion,
        Macos,
        Windows
    };
}

Q_DECLARE_METATYPE(Types::Language)
Q_DECLARE_METATYPE(Types::Theme)

const QString languageToString(const Types::Language lang);
Types::Language stringToLanguage(const QString &str);

const QString themeToString(const Types::Theme theme);
Types::Theme stringToTheme(const QString &str);
