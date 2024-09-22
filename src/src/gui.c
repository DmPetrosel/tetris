#include "../inc/objects.h"


void main_gui(params_t * prms){
    for(int y = 0; y < ROWS_FIELD; y ++){
        for(int x = 0; x < COLS_FIELD; x ++){
            if(prms->state.current_field.field[y][x])
                printf("#");
            else
                printf(" ");
        }
    }
}