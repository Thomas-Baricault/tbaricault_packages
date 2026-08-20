/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <string>
#include <string_view>


namespace tbaricault::packages
{

    /**
     * @brief Represents a semantic version number
     * 
     * A version is composed of three numerical components: major, minor, and patch.
     */
    class Version
    {

        public:

            /**
             * @brief Whether minor component can be ignored if it is 0
             */
            static bool ignoreMinor;

            /**
             * @brief Whether patch component can be ignored if it is 0
             */
            static bool ignorePatch;


            /**
             * @brief Major version component
             * 
             * The major version is incremented when incompatible API changes are introduced.
             */
            unsigned long major = 0;

            /**
             * @brief Minor version component
             * 
             * The minor version is incremented when new backward-compatible functionality is added.
             */
            unsigned long minor = 0;

            /**
             * @brief Patch version component
             * 
             * The patch version is incremented for backward-compatible bug fixes.
             */
            unsigned long patch = 0;


            /**
             * @brief Default constructor, initializes all components to zero
             */
            Version() noexcept = default;

            /**
             * @brief Copy constructor
             * 
             * @param other Version to copy
             */
            Version(const Version& other) noexcept = default;

            /**
             * @brief Move constructor
             * 
             * @param other Version to move
             */
            Version(Version&& other) noexcept = default;

            /**
             * @brief Constructs a version from its components
             * 
             * @param major Major version component
             * @param minor Minor version component
             * @param patch Patch version component
             */
            Version(unsigned long major, unsigned long minor = 0, unsigned long patch = 0) noexcept;

            /**
             * @brief Constructs a version from its string representation
             * 
             * @param str String representation
             * 
             * @throws std::invalid_argument If conversion failed
             */
            Version(std::string_view str);

            /**
             * @brief Destructor
             */
            ~Version() noexcept = default;

            /**
             * @brief Copy assignment operator
             * 
             * @param other Version to copy
             * 
             * @return Reference to this version
             */
            Version& operator=(const Version& other) noexcept = default;

            /**
             * @brief Move assignment operator
             * 
             * @param other Version to move
             * 
             * @return Reference to this version
             */
            Version& operator=(Version&& other) noexcept = default;

            /**
             * @brief Checks whether two versions are equal
             * 
             * @param other Version to compare with
             * 
             * @return `true` if both version are equal, `false` otherwise
             */
            bool operator==(const Version& other) const noexcept;

            /**
             * @brief Checks whether two versions are different
             * 
             * @param other Version to compare with
             * 
             * @return `true` if versions differ, `false` otherwise
             */
            bool operator!=(const Version& other) const noexcept;

            /**
             * @brief Checks whether this version is less than or equal to another
             * 
             * @param other Version to compare with
             * 
             * @return `true` if less than or equal to another, `false` otherwise
             */
            bool operator<=(const Version& other) const noexcept;

            /**
             * @brief Checks whether this version is greater than or equal to another
             * 
             * @param other Version to compare with
             * 
             * @return `true` if greater than or equal to another, `false` otherwise
             */
            bool operator>=(const Version& other) const noexcept;

            /**
             * @brief Checks whether this version is less than another
             * 
             * @param other Version to compare with
             * 
             * @return `true` if less than to another, `false` otherwise
             */
            bool operator<(const Version& other) const noexcept;

            /**
             * @brief Checks whether this version is greater than another
             * 
             * @param other Version to compare with
             * 
             * @return `true` if greater than to another, `false` otherwise
             */
            bool operator>(const Version& other) const noexcept;

            /**
             * @brief Converts the version to its string representation
             */
            operator std::string() const;

            /**
             * @brief Checks whether this version matches a version specification
             * 
             * The specification defines the version constraints that must be satisfied by this version, example: `>=1.2<2`.
             * 
             * Supported operators are:
             * 
             * == (equal to)
             * 
             * != (different from)
             * 
             * <= (less than or equal to)
             * 
             * >= (greater than or equal to)
             * 
             * < (less than)
             * 
             * > (greater than)
             * 
             * ^ (greater or equal to but less than next major version)
             * 
             * ~ (greater or equal to but less than next minor version)
             * 
             * @param specification Version specification to evaluate
             * 
             * @return `true` if satisfies the specified constraints, `false` otherwise
             * 
             * @throws std::invalid_argument If specification is invalid
             */
            bool match(std::string_view specification) const;

    };

}
