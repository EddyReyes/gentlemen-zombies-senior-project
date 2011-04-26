//Where all the game states will be put
//some states may not be used but are there just in case

//game states
#define adventure_mode  0 //top down view
#define menu			1//menu mode also used in stores
#define side_scroll		2//side scroll mode
//states for input
#define input_Menu		0//does input for the menu
#define input_game		1//does input for the game


//character states
#define char_idle		0//character standing still
#define char_moving		1//character moving
#define char_jump		2//character jumping


//enemy states
#define enemy_idle		0//enemy idle
#define enemy_mov		1//enemy movement
#define enemy_atk		2//enemy attack
#define enemy_jmp		3//enemy jump
