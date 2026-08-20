/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include <stdexcept>

#include <tbaricault/str.hpp>
#include <tbaricault/uniconvert.hpp>

#include "packages/Version.hpp"


namespace tbaricault::packages
{

    bool Version::ignoreMinor = true;

    bool Version::ignorePatch = true;


    Version::Version(unsigned long major, unsigned long minor, unsigned long patch) noexcept
        : major(major)
        , minor(minor)
        , patch(patch)
    {
        return;
    }

    Version::Version(std::string_view str)
    {
        std::vector<std::string> parts = tbaricault::str::split(str, ".");
        if (
            parts.size() > 3 ||
            (!Version::ignorePatch && parts.size() < 3) ||
            (!Version::ignoreMinor && parts.size() < 2) ||
            (Version::ignorePatch && Version::ignoreMinor && parts.size() < 1)
        )
            throw std::invalid_argument("convertion failed");
        this->major = tbaricault::uniconvert::convert<std::string, unsigned long>(parts.at(0));
        if (parts.size() >= 2)
            this->minor = tbaricault::uniconvert::convert<std::string, unsigned long>(parts.at(1));
        if (parts.size() == 3)
            this->patch = tbaricault::uniconvert::convert<std::string, unsigned long>(parts.at(2));
        return;
    }

    bool Version::operator==(const Version& other) const noexcept
    {
        return (
            this->major == other.major &&
            this->minor == other.minor &&
            this->patch == other.patch
        );
    }

    bool Version::operator!=(const Version& other) const noexcept
    {
        return (
            this->major != other.major ||
            this->minor != other.minor ||
            this->patch != other.patch
        );
    }

    bool Version::operator<=(const Version& other) const noexcept
    {
        if (this->major != other.major)
            return (this->major < other.major);
        if (this->minor != other.minor)
            return (this->minor < other.minor);
        return (this->patch <= other.patch);
    }

    bool Version::operator>=(const Version& other) const noexcept
    {
        if (this->major != other.major)
            return (this->major > other.major);
        if (this->minor != other.minor)
            return (this->minor > other.minor);
        return (this->patch >= other.patch);
    }

    bool Version::operator<(const Version& other) const noexcept
    {
        if (this->major != other.major)
            return (this->major < other.major);
        if (this->minor != other.minor)
            return (this->minor < other.minor);
        return (this->patch < other.patch);
    }

    bool Version::operator>(const Version& other) const noexcept
    {
        if (this->major != other.major)
            return (this->major > other.major);
        if (this->minor != other.minor)
            return (this->minor > other.minor);
        return (this->patch > other.patch);
    }

    Version::operator std::string() const
    {
        std::string result = tbaricault::uniconvert::convert<unsigned long, std::string>(this->major);
        if (this->minor != 0 || this->patch != 0 || !Version::ignoreMinor || !Version::ignorePatch)
            result += '.' + tbaricault::uniconvert::convert<unsigned long, std::string>(this->minor);
        if (this->patch != 0 || !Version::ignorePatch)
            result += '.' + tbaricault::uniconvert::convert<unsigned long, std::string>(this->patch);
        return (result);
    }

    bool Version::match(std::string_view specification) const
    {
        if (specification.empty())
            return (true);
        std::size_t i = 0;
        while (i < specification.size())
        {
            std::size_t j = i;
            while (j < specification.size() && specification.at(j) != '.' && !std::isdigit(specification.at(j)))
                j++;
            if (j == i)
                throw std::invalid_argument("missing operator at the begin of specification");
            if (j > i + 2)
                throw std::invalid_argument(std::string("invalid operator '") + std::string(specification.substr(i, j - i)) + "'");
            char op[2];
            op[0] = specification.at(i);
            op[1] = j == i + 2 ? specification.at(i + 1) : '\0';
            i = j;
            while (j < specification.size() && (specification.at(j) == '.' || std::isdigit(specification.at(j))))
                j++;
            Version version = tbaricault::uniconvert::convert<std::string, Version>(std::string(specification.substr(i, j - i)));
            i = j;
            if (op[0] == '=' && op[1] == '=')
            {
                if (!(*this == version))
                    return (false);
            }
            else if (op[0] == '!' && op[1] == '=')
            {
                if (!(*this != version))
                    return (false);
            }
            else if (op[0] == '<' && op[1] == '=')
            {
                if (!(*this <= version))
                    return (false);
            }
            else if (op[0] == '>' && op[1] == '=')
            {
                if (!(*this >= version))
                    return (false);
            }
            else if (op[0] == '<' && op[1] == '\0')
            {
                if (!(*this < version))
                    return (false);
            }
            else if (op[0] == '>' && op[1] == '\0')
            {
                if (!(*this > version))
                    return (false);
            }
            else if (op[0] == '^' && op[1] == '\0')
            {
                if (!(*this >= version && *this < Version(version.major + 1)))
                    return (false);
            }
            else if (op[0] == '~' && op[1] == '\0')
            {
                if (!(*this >= version && *this < Version(version.major, version.minor + 1)))
                    return (false);
            }
            else
                throw std::invalid_argument("invalid operator");
        }
        return (true);
    }

}
