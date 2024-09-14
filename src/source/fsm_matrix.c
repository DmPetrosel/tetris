#include "../includes/fsm.h"
#include "../includes/defines.h"
#include "../includes/objects.h"
#include <stdio.h>

typedef struct{
    UserAction_t * user_action;
    Board_t *board;
    BrickState_t * brick_state;
    Board_t * board;
    PlayerPos_t * player_pos;
    GameInfo_t * game_info;
}params_t;

typedef void (*action)(params_t * prms);

void Start(params_t * prms);
void Spawn(params_t * prms);
void Move(params_t * prms);
void Strike(params_t * prms);
void Attach(params_t * prms);
void GameOver(params_t * prms);

action fsm_table[][8] ={
{NULL},
{Start},
{Spawn},
{}

};