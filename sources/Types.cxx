#include "Types.hxx"

const QString languageToString(const Types::Language lang)
{
    switch (lang)
    {
        case Types::Language::Dutch:
            return "Dutch";

        case Types::Language::French:
            return "French";

        case Types::Language::Italian:
            return "Italian";

        case Types::Language::German:
            return "German";

        case Types::Language::Spanish:
            return "Spanish";

        case Types::Language::English:
        default:
            return "English";
    }
}

Types::Language stringToLanguage(const QString &str)
{
    if (str == "Dutch")
        return Types::Language::Dutch;

    if (str == "French")
        return Types::Language::French;

    if (str == "Italian")
        return Types::Language::Italian;

    if (str == "German")
        return Types::Language::German;

    if (str == "Spanish")
        return Types::Language::Spanish;

    return Types::Language::English;
}
