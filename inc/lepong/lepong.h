//
// Created by lepouki on 10/12/2020.
//

#pragma once

namespace lepong
{

///
/// Initializes the game and all of its systems.<br>
/// If the game is already initialized, this function returns false.
///
/// \return Whether the game was successfully initialized.
///
bool Init() noexcept;

///
/// Starts the game's main loop.
///
void Run() noexcept;

///
/// Cleans up resources used by the game and its systems.
///
void Cleanup() noexcept;

} // namespace lepong
