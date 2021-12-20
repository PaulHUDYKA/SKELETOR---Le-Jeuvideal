#pragma once

#ifdef _DEBUG

#define ASSERT(Expression, Message) if (!(Expression)) { *(int*)0 = 0; }

#else

#define ASSERT(Expression, Message) ((void)0);

#endif

#define GAME_NAME	"Le JeuVidéal"

#define GAME_Ver	"Alpha-Stage"

#define GAME_RES_WIDTH	384

#define GAME_RES_HEIGHT	240

#define GAME_BPP		32

#define GAME_DRAWING_AREA_MEMORY_SIZE	(GAME_RES_WIDTH * GAME_RES_HEIGHT * (GAME_BPP / 8))

#define CALCULATE_AVG_FPS_EVERY_X_FRAMES	120

#define TARGET_MICROSECONDS_PER_FRAME		16667ULL

#define SIMD

#define SUIT_0	0

#define SUIT_1	1

#define SUIT_2	2

#define STANDING_DOWN_0	0

#define WALKING_DOWN_1	1

#define WALKING_DOWN_2	2

#define STANDING_LEFT_0	3

#define WALKING_LEFT_1	4

#define WALKING_LEFT_2	5

#define STANDING_RIGHT_0	6

#define WALKING_RIGHT_1	7

#define WALKING_RIGHT_2	8

#define STANDING_UP_0	9

#define WALKING_UP_1	10

#define WALKING_UP_2	11


typedef enum DIRECTION
{
	DOWN  = 0,

	LEFT  = 3,

	RIGHT = 6,

	UP	  = 9,

}DIRECTION;

typedef enum LOGLEVEL
{
	LL_NONE		 = 0,

	LL_ERROR	 = 1,

	LL_WARNING	 = 2,

	LL_INFO		 = 3,

	LL_DEBUG	 = 4,

}LOGLEVEL;

#define LOG_FILE_NAME GAME_NAME ".log"

#define FONT_SHEET_CHARACTERS_PER_ROW 98


#pragma warning(disable: 4820)	// Disable warning about structure padding

#pragma warning(disable: 5045)	// Disable warning about Spectre/Meltdown CPU vulnerability

#pragma warning(disable: 4710)	// Disable warning about function not inlined

#pragma warning(disable: 4133)  // Disable warning about PIXEL32* to _m128i *

#pragma warning(disable: 28251)  // Annotation incohérente pour WinMain


typedef LONG(NTAPI* _NtQueryTimerResolution) (OUT PULONG MinimumResolution, OUT PULONG MaximumResolution, OUT PULONG CurrentResolution);

_NtQueryTimerResolution NtQueryTimerResolution;


typedef struct GAMEBITMAP
{
	BITMAPINFO BitmapInfo;

	void* Memory;

} GAMEBITMAP;

typedef struct PIXEL32
{
	uint8_t Blue;

	uint8_t Green;

	uint8_t Red;

	uint8_t Alpha;

} PIXEL32;

typedef struct GAMEPERFDATA
{
	uint64_t TotalFramesRendered;

	float RawFPSAverage;

	float CookedFPSAverage;

	int64_t PerfFrequency;

	MONITORINFO MonitorInfo;

	int32_t MonitorWidth;

	int32_t MonitorHeight;

	BOOL DisplayDebugInfo;

	ULONG MinimumTimerResolution;

	ULONG MaximumTimerResolution;

	ULONG CurrentTimerResolution;

	DWORD HandleCount;

	PROCESS_MEMORY_COUNTERS_EX MemInfo;

	SYSTEM_INFO SystemInfo;

	int64_t CurrentSystemTime;

	int64_t PreviousSystemTime;

	double CPUPercent;

} GAMEPERFDATA;

typedef struct SKELETOR
{
	char Name[12];

	GAMEBITMAP Sprite[3][12];

	int16_t ScreenPosX;

	int16_t ScreenPosY;

	uint8_t MovementRemaining;

	DIRECTION Direction;

	uint8_t CurrentSuit;

	uint8_t SpriteIndex;

	int32_t HP;

	int32_t Strength;

	int32_t MP;

} SKELETOR;

typedef struct REGISTRYPARAMS
{
	DWORD LogLevel;


} REGISTRYPARAMS;


LRESULT CALLBACK MainWindowProc(_In_ HWND WindowHandle, _In_ UINT Message, _In_ WPARAM WParam, _In_ LPARAM LParam);

DWORD CreateMainGameWindow(void);

BOOL GameIsAlreadyRunning(void);

void ProcessPlayerInput(void);

DWORD Load32BppBitmapFromFile(_In_ char* FileName, _Inout_ GAMEBITMAP* GameBitmap);

DWORD InitializeSkeletor(void);

void Blit32BppBitmapToBuffer(_In_ GAMEBITMAP* GameBitmap, _In_ uint16_t x, _In_ uint16_t y);

void BlitStringToBuffer(_In_ char* String, _In_ GAMEBITMAP* FontSheet, _In_ PIXEL32* Color,_In_ uint16_t x, _In_ uint16_t y);

void RenderFrameGraphics(void);

DWORD LoadRegistryParameters(void);

void LogMessageA(_In_ DWORD LogLevel, _In_ char* Message, _In_ ...);

void DrawDebugInfo(void);

void FindFirstConnectedGamepad(void);

#ifdef SIMD
void ClearScreen(_In_ __m128i* Color);
#else
void ClearScreen(_In_ PIXEL32* Color);
#endif

