#pragma once

namespace Hall
{
	/// @brief This is a typedef of raylibs KeyboardKey enums
	typedef ::KeyboardKey KeyboardKey;
	typedef unsigned short ControllerState;
	static const int SYSTEM_CLK_FREQUENCY = 50000000; //50 MHz
	static void* const SDRAM_START = 0x0; //Start of the RAM. It is 32 MB large
	static void* const BOOTLOADER_START = (void* const) 0x02010000; //Start of the bootloader. It is 32 kB large
	static void* const SD_CARD_START = (void* const) 0x80000000; //Start of the SD-Card

	/// <summary>
	/// Initialises the system
	/// </summary>
	void Init();

	/// <summary>
	/// 
	/// </summary>
	/// <returns> True, if the program was requested to terminate, else false</returns>
	bool ShouldClose();

	/// <summary>
	/// Returns an 8-Byte int, that represents the number of ticks that passed since the system's boot-up. Divide by SYSTEM_CLK_FREQUENCY to get seconds
	/// </summary>
	/// <returns>The system time since boot-up in ticks</returns>
	unsigned long long GetSystemTime();
	unsigned int GetSystemTimeExcerpt(int precision);

#ifdef DESKTOP
	void SetCONT0_UP(KeyboardKey key);
	void SetCONT0_DOWN(KeyboardKey key);
	void SetCONT0_LEFT(KeyboardKey key);
	void SetCONT0_RIGHT(KeyboardKey key);
	void SetCONT0_START(KeyboardKey key);
	void SetCONT0_SELECT(KeyboardKey key);
	void SetCONT0_A(KeyboardKey key);
	void SetCONT0_B(KeyboardKey key);
	void SetCONT0_X(KeyboardKey key);
	void SetCONT0_Y(KeyboardKey key);
	void SetCONT0_L(KeyboardKey key);
	void SetCONT0_R(KeyboardKey key);
	void SetCONT1_UP(KeyboardKey key);
	void SetCONT1_DOWN(KeyboardKey key);
	void SetCONT1_LEFT(KeyboardKey key);
	void SetCONT1_RIGHT(KeyboardKey key);
	void SetCONT1_START(KeyboardKey key);
	void SetCONT1_SELECT(KeyboardKey key);
	void SetCONT1_A(KeyboardKey key);
	void SetCONT1_B(KeyboardKey key);
	void SetCONT1_X(KeyboardKey key);
	void SetCONT1_Y(KeyboardKey key);
	void SetCONT1_L(KeyboardKey key);
	void SetCONT1_R(KeyboardKey key);
#endif

	/// <summary>
	/// Returns the state of all buttons on the controller.
	/// </summary>
	/// <param name="id">Must be in the range [0,1]</param>
	/// <returns>Each button corresponds to one bit: 0 - B, 1 - Y, 2 - Select, 3 - Start, 4 - Up, 5 - Down, 6 - Left, 7 - Right, 8 - A, 9 - X, 10 - L, 11 - R</returns>
	ControllerState GetController(int id);

	bool GetA(ControllerState controller);
	bool GetB(ControllerState controller);
	bool GetX(ControllerState controller);
	bool GetY(ControllerState controller);
	bool GetStart(ControllerState controller);
	bool GetSelect(ControllerState controller);
	bool GetUp(ControllerState controller);
	bool GetDown(ControllerState controller);
	bool GetLeft(ControllerState controller);
	bool GetRight(ControllerState controller);
	bool GetL(ControllerState controller);
	bool GetR(ControllerState controller);
}
