#include "q_tap_dance.h"
#include "quantum.h"

// Tap dance states
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD,
  DOUBLE_TAP,
  DOUBLE_HOLD,
  DOUBLE_SINGLE_TAP,
  TRIPLE_TAP,
  TRIPLE_HOLD,
};

// Stores the last state for each tap dance
static int q_td_states[] = {
0,0,0,0
};

int cur_dance(qk_tap_dance_state_t *state) {
	int dance = SINGLE_TAP;
	switch (state->count) {
		case 1: {
				if (state->pressed) 
					dance = SINGLE_HOLD;
				break;
			}
		case 2: {
				if (state->interrupted)
					dance = DOUBLE_SINGLE_TAP;
				else if (state->pressed)
					dance = DOUBLE_HOLD;
				else
					dance = DOUBLE_TAP;
				break;
			}
		case 3:
			{
				if (state->pressed)
					dance = TRIPLE_HOLD;
				else
					dance = TRIPLE_TAP;
				break;
			}
	}	

	return dance;
}	

/***************************************************************
 * Taps: <, <>
 * Holds: <=, <<=
 ***************************************************************/
void td_lt_finished(qk_tap_dance_state_t *state, void *user_data) {
	int* dance = &q_td_states[TD_LT];
	*dance = cur_dance(state);

	switch(*dance) {
		case SINGLE_TAP: register_code(KC_LSHIFT); register_code(KC_COMMA); break;
		case SINGLE_HOLD: register_code(KC_LSHIFT); register_code(KC_COMMA); unregister_code(KC_COMMA); unregister_code(KC_LSHIFT); register_code(KC_EQL); break;
		case DOUBLE_TAP:  register_code(KC_LSHIFT); register_code(KC_COMMA); unregister_code(KC_COMMA); register_code(KC_DOT); unregister_code(KC_LSHIFT); register_code(KC_LEFT); break;
		case DOUBLE_HOLD: register_code(KC_LSHIFT); register_code(KC_COMMA); unregister_code(KC_COMMA); register_code(KC_COMMA); unregister_code(KC_COMMA); register_code(KC_EQL);  break;
		case DOUBLE_SINGLE_TAP: register_code(KC_LSHIFT); register_code(KC_COMMA); unregister_code(KC_COMMA); register_code(KC_COMMA); break;
	}	
}

void td_lt_reset(qk_tap_dance_state_t *state, void *user_data) {
	int* dance = &q_td_states[TD_LT];
	switch (*dance) {
		case SINGLE_TAP: unregister_code(KC_COMMA); unregister_code(KC_LSHIFT); break;
		case SINGLE_HOLD: unregister_code(KC_EQL); break;
		case DOUBLE_TAP: unregister_code(KC_LEFT); break;
		case DOUBLE_HOLD: unregister_code(KC_EQL); unregister_code(KC_LSHIFT); break;
		case DOUBLE_SINGLE_TAP: unregister_code(KC_COMMA); unregister_code(KC_LSHIFT); break;
	}	

	*dance = 0;

}	

/***************************************************************
 * Taps: >, ><
 * Holds: >=, >>=
 ***************************************************************/
void td_gt_finished(qk_tap_dance_state_t *state, void *user_data) {
	int* dance = &q_td_states[TD_GT];
	*dance = cur_dance(state);

	switch(*dance) {
		case SINGLE_TAP: register_code(KC_LSHIFT); register_code(KC_DOT); break;
		case SINGLE_HOLD: register_code(KC_LSHIFT); register_code(KC_DOT); unregister_code(KC_DOT); unregister_code(KC_LSHIFT); register_code(KC_EQL); break;
		case DOUBLE_TAP:  register_code(KC_LSHIFT); register_code(KC_DOT); unregister_code(KC_DOT); register_code(KC_COMMA); unregister_code(KC_LSHIFT); register_code(KC_LEFT); break;
		case DOUBLE_HOLD: register_code(KC_LSHIFT); register_code(KC_DOT); unregister_code(KC_DOT); register_code(KC_DOT); unregister_code(KC_DOT); unregister_code(KC_LSHIFT); register_code(KC_EQL);  break;
		case DOUBLE_SINGLE_TAP: register_code(KC_LSHIFT); register_code(KC_DOT); unregister_code(KC_DOT); register_code(KC_DOT); break;
	}	
}

void td_gt_reset(qk_tap_dance_state_t *state, void *user_data) {
	int* dance = &q_td_states[TD_GT];
	switch (*dance) {
		case SINGLE_TAP: unregister_code(KC_DOT); unregister_code(KC_LSHIFT); break;
		case SINGLE_HOLD: unregister_code(KC_EQL); break;
		case DOUBLE_TAP: unregister_code(KC_LEFT); break;
		case DOUBLE_HOLD: unregister_code(KC_EQL); unregister_code(KC_LSHIFT); break;
		case DOUBLE_SINGLE_TAP: unregister_code(KC_DOT); unregister_code(KC_LSHIFT); break;
	}	

	*dance = 0;

}	
/***************************************************************
 * Taps: volume up, ______, next track
 * Holds: play/pause
 ***************************************************************/
void td_media_up_finished(qk_tap_dance_state_t *state, void *user_data) {
	int* dance = &q_td_states[TD_MEDIAUP];
	*dance = cur_dance(state);

	switch(*dance) {
		case SINGLE_TAP:
		case DOUBLE_TAP:
		case DOUBLE_HOLD:
			register_code(KC_AUDIO_VOL_UP); break;
		case SINGLE_HOLD: register_code(KC_MEDIA_PLAY_PAUSE); break;
		case TRIPLE_TAP: register_code(KC_MEDIA_NEXT_TRACK);
	}	
}

void td_media_up_reset(qk_tap_dance_state_t *state, void *user_data) {
	int* dance = &q_td_states[TD_MEDIAUP];
	switch (*dance) {
		case SINGLE_TAP:
		case DOUBLE_TAP:
		case DOUBLE_HOLD:
			unregister_code(KC_AUDIO_VOL_UP); break;
		case SINGLE_HOLD: unregister_code(KC_MEDIA_PLAY_PAUSE); break;
		case TRIPLE_TAP: unregister_code(KC_MEDIA_NEXT_TRACK);
	}	

	*dance = 0;
}	

/***************************************************************
 * Taps: volume down, ______, prev track
 * Holds: mute
 ***************************************************************/
void td_media_down_finished(qk_tap_dance_state_t *state, void *user_data) {
	int* dance = &q_td_states[TD_MEDIADN];
	*dance = cur_dance(state);

	switch(*dance) {
		case SINGLE_TAP: 
		case DOUBLE_TAP:
		case DOUBLE_HOLD:
			register_code(KC_AUDIO_VOL_DOWN); break;
		case SINGLE_HOLD: register_code(KC_AUDIO_MUTE); break;
		case TRIPLE_TAP: register_code(KC_MEDIA_PREV_TRACK);
	}	
}

void td_media_down_reset(qk_tap_dance_state_t *state, void *user_data) {
	int* dance = &q_td_states[TD_MEDIADN];
	switch (*dance) {
		case SINGLE_TAP: 
		case DOUBLE_TAP:
		case DOUBLE_HOLD:
				 unregister_code(KC_AUDIO_VOL_UP); break;
		case SINGLE_HOLD: unregister_code(KC_AUDIO_MUTE); break;
		case TRIPLE_TAP: unregister_code(KC_MEDIA_PREV_TRACK);
	}	

	*dance = 0;
}	

//All tap dance functions would go here.
qk_tap_dance_action_t tap_dance_actions[] = {
 [TD_LT] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, td_lt_finished, td_lt_reset),
 [TD_GT] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, td_gt_finished, td_gt_reset),
 [TD_MEDIADN] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, td_media_down_finished, td_media_down_reset),
 [TD_MEDIAUP] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, td_media_up_finished, td_media_up_reset),
};
