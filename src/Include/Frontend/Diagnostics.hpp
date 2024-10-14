#ifndef DIAGNOSTICS_HPP
#define DIAGNOSTICS_HPP

#include <string>
#include <string_view>
#include <format>
#include "Frontend/Token.hpp"

namespace MPIRectRule::Frontend {
    enum class ParseError {
        unknown_token,
        unexpected_token,
        general_error
    };

    template <ParseError ErrTag>
    constexpr const char* parse_error_heading_v = "General";

    template <>
    inline constexpr const char* parse_error_heading_v<ParseError::unknown_token> = "Unknown token";

    template <>
    inline constexpr const char* parse_error_heading_v<ParseError::unexpected_token> = "Unexpected token";

    template <ParseError ErrTag>
    [[nodiscard]] std::string formatDiagnosticText(const std::string& source, const Token& offender) {
        return std::format("Parse Error [{}]:\noffending token: \"{}\"\n", parse_error_heading_v<ErrTag>, getLexeme(offender, source));
    }
}

#endif