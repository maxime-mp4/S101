//
// Created by maxime on 1/6/25.
//

#ifndef TERMINAL_MANAGEMENT_H
#define TERMINAL_MANAGEMENT_H

#include <iostream>

/** @file terminal_management.h
 *  @brief Functions for managing terminal input, output, and formatting.
 *  @author maxime-mp4
 */

/**
 * @brief Set the terminal to non-canonical mode.
 *
 * This function configures the terminal to operate in non-canonical mode,
 * allowing real-time input processing without waiting for a newline character.
 */
void setNonCanonicalMode();

/**
 * @brief Restore the terminal to its default mode.
 *
 * This function resets the terminal settings to their default values,
 * typically used to undo changes made by setNonCanonicalMode().
 */
void restoreDefaultMode();

/**
 * @brief Clear the current terminal screen.
 *
 * This function clears all content currently displayed in the terminal.
 */
void clearScreen();

/**
 * @brief Set the color of future input in the terminal.
 *
 * This function allows you to set a color for the text input in the terminal.
 * The color is applied to all subsequent terminal outputs.
 *
 * @param COL The color to apply, given as a string (e.g., "red", "blue").
 */
void setColor(const std::string &COL);

/**
 * @brief Create an HTML hyperlink.
 *
 * This function creates a string representing an HTML hyperlink, which can be used in a terminal
 * that supports HTML rendering, or embedded into HTML files.
 *
 * @param LINK The URL to link to.
 * @param TEXT The text to display for the hyperlink.
 *
 * @return A string containing the HTML representation of the hyperlink.
 */
std::string createHyperLink(const std::string &LINK, const std::string &TEXT);

#endif //TERMINAL_MANAGEMENT_H
