/* 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "git_shorthand.h"

typedef struct { char* key; char* result; } replacements_t;
static replacements_t lookuptable[] = {
    {"g", "git"},
    {"ga", "git add"},
    {"gaa", "git add --all"},
    {"gav", "git add --verbose"},
    {"gb", "git branch"},
    {"gba", "git branch -a"},
    {"gbd", "git branch -d"},
    {"gbD", "git branch -D"},
    {"gc", "git commit -v"},
    {"gca", "git commit -v -a"},
    {"gcb", "git checkout -b"},
    {"gcl", "git clone --recurse-submodules"},
    {"gcm", "git checkout master"},
    {"gcmsg", "git commit -m"},
    {"gco", "git checkout"},
    {"gcs", "git commit -S"},
    {"gd", "git diff"},
    {"gds", "git diff --staged"},
    {"gf", "git fetch"},
    {"gfa", "git fetch --all --prune"},
    {"gfo", "git fetch origin"},
    {"ggpull", "git pull origin \"$(git branch --show-current)\""},
    {"ggpush", "git push origin \"$(git branch --show-current)\""},
    {"gpsup", "git push --set-upstream origin $(git branch --show-current)"},
    {"gl", "git pull"},
    {"glg", "git log --stat"},
    {"glgp", "git log --stat -p"},
    {"glgg", "git log --graph"},
    {"glgga", "git log --graph --decorate --all"},
    {"glgm", "git log --graph --max-count=10"},
    {"glo", "git log --oneline --decorate"},
    {"gp", "git push"},
    {"gpd", "git push --dry-run"},
    {"gpf", "git push --force"},
    {"gpu", "git push upstream"},
    {"gpv", "git push -v"},
    {"grh", "git reset"},
    {"grhh", "git reset --hard"},
    {"grm", "git rm"},
    {"gst", "git status"},
    {"gwch", "git whatchanged -p --abbrev-commit --pretty=medium"},
};

#define N_REPLACEMENTS (sizeof(lookuptable)/sizeof(replacements_t))
#define shift(a, b) (((mods | oneshot_mods) & MOD_MASK_SHIFT) ? b : a)
#define MAX_REPLACEMENT_SIZE 7

bool process_git_shorthand(uint16_t keycode, keyrecord_t* record) {
    static char replacement_string[MAX_REPLACEMENT_SIZE] = "\0";
    static uint8_t replacement_buffer_size = 0;
    const uint8_t mods = get_mods();
    const uint8_t oneshot_mods = get_oneshot_mods();

    // Ignore key release; we only process key presses.
    if (!record->event.pressed) {
        return true;
    }
    // Disable autocorrection while a mod other than shift is active.
    if (((mods | oneshot_mods) & ~MOD_MASK_SHIFT) != 0) {
        memset(replacement_string, 0, MAX_REPLACEMENT_SIZE);
        replacement_buffer_size = 0;
        return true;
    }

    switch (keycode) {
        // Ignore shifts, Caps Lock, one-shot mods, and layer switch keys.
        case KC_NO:
        case KC_LSFT:
        case KC_RSFT:
        case KC_CAPS:
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
        case QK_TO ... QK_TO_MAX:
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:
        case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
        case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
        case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
        case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
        case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
            return true;  // Ignore these keys.

        case KC_SPC:
        case KC_ENT: {
            for (int i=0; i<N_REPLACEMENTS; i++) {
                replacements_t *replacement = &lookuptable[i];
                if (strcmp(replacement->key, replacement_string) == 0) {
                    for (uint8_t j=0; j<replacement_buffer_size; j++) {
                        tap_code(KC_BSPC);
                    }
                    del_oneshot_mods(MOD_MASK_SHIFT);
                    unregister_mods(MOD_MASK_SHIFT); 
                    send_string(replacement->result);
                    register_mods(mods);
                    break;
                }
            }
            memset(replacement_string, 0, MAX_REPLACEMENT_SIZE);
            replacement_buffer_size = 0;
            break;
        }
        case KC_BSPC: {
            if (replacement_buffer_size > 0) {
                replacement_string[replacement_buffer_size--] = '\0';
            }
            break;
        }
        case KC_A ... KC_Z: {
            replacement_string[replacement_buffer_size++] = shift('a', 'A') + (keycode - KC_A);
            break;
        }
        case KC_1 ... KC_0:
        case KC_MINUS ... KC_SLASH:
        {
            replacement_string[replacement_buffer_size++] = '_';
            break;
        }
    }

    if (replacement_buffer_size >= MAX_REPLACEMENT_SIZE) {
        memmove(replacement_string, replacement_string+1, MAX_REPLACEMENT_SIZE-1);
        replacement_buffer_size = MAX_REPLACEMENT_SIZE-1;
    }

    return true;
}