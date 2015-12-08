/*
 * Copyright (C) 2015 Nino de Wit <ninodig@hotmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any purpose with
 * or without fee is hereby granted, provided that the above copyright notice and this
 * permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
 * TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef DISTRHO_PLUGIN_INFO_H_INCLUDED
#define DISTRHO_PLUGIN_INFO_H_INCLUDED

#define DISTRHO_PLUGIN_BRAND "SHIRO"
#define DISTRHO_PLUGIN_NAME  "Pitchotto"
#define DISTRHO_PLUGIN_URI   "http://distrho.sf.net/plugins/Pitchotto"

#define DISTRHO_PLUGIN_HAS_UI        0
#define DISTRHO_PLUGIN_IS_RT_SAFE    0
#define DISTRHO_PLUGIN_NUM_INPUTS    1
#define DISTRHO_PLUGIN_NUM_OUTPUTS   1
#define DISTRHO_PLUGIN_USES_MODGUI   1

#define DISTRHO_PLUGIN_LV2_CATEGORY "lv2:PitchPlugin"

#define DISTRHO_PLUGIN_DESCRIPTION "Pitchotto is a pitch-shifter based on the \"Pitch-Shift\"-genpatch in Max, where Phase-shifting is used to achieve different intervals.\n\
There are two shifted signals available, both with variable delay-lengths for arpeggio-like sounds."
#define DISTRHO_PLUGIN_VERSION d_cconst('D', 'M', 'p', 'c')

#endif // DISTRHO_PLUGIN_INFO_H_INCLUDED
