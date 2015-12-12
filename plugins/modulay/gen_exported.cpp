#include "gen_exported.h"

namespace gen_exported {


/*******************************************************************************************************************
Copyright (c) 2012 Cycling '74

Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies
or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*******************************************************************************************************************/


// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State { 
	CommonState __commonstate;
	DCBlock m_dcblock_11;
	Delay m_delay_2;
	Delay m_delay_3;
	SineCycle m_cycle_12;
	SineData __sinedata;
	double m_mix_9;
	double m_rate_8;
	double m_cutoff_10;
	double m_morph_7;
	double m_time_5;
	double m_repeats_4;
	double m_depth_6;
	double samplerate;
	double m_y_1;
	int vectorsize;
	int __exception;
	// re-initialize all member variables;
	inline void reset(double __sr, int __vs) { 
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_y_1 = 0;
		m_delay_2.reset("m_delay_2", 48000);
		m_delay_3.reset("m_delay_3", 48000);
		m_repeats_4 = 75;
		m_time_5 = 500;
		m_depth_6 = 1;
		m_morph_7 = 50;
		m_rate_8 = 2;
		m_mix_9 = 100;
		m_cutoff_10 = 2500;
		m_dcblock_11.reset();
		m_cycle_12.reset(samplerate, 0);
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) { 
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		t_sample * __out1 = __outs[0];
		if (__exception) { 
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) )) { 
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		double mul_4216 = (m_mix_9 * 0.01);
		double mstosamps_4241 = (m_time_5 * (samplerate * 0.001));
		double expr_4223 = safediv(((m_cutoff_10 * 2) * 3.1415926535898), 48000);
		double sin_4224 = sin(expr_4223);
		double clamp_4225 = ((sin_4224 <= 1e-05) ? 1e-05 : ((sin_4224 >= 0.99999) ? 0.99999 : sin_4224));
		double mul_4220 = (m_repeats_4 * 0.01);
		double mul_4244 = (m_morph_7 * -1.4);
		double add_4246 = (mul_4244 + 70);
		double abs_4245 = fabs(add_4246);
		double mul_4218 = (abs_4245 * 0.01);
		double mul_4242 = (m_morph_7 * 1.4);
		double sub_4243 = (mul_4242 - 70);
		double mul_4219 = (sub_4243 * 0.01);
		int gt_4248 = (m_morph_7 > 50);
		double mul_4247 = (gt_4248 * m_morph_7);
		double mul_4249 = (mul_4247 * -0.6);
		double add_4250 = (mul_4249 + 130);
		double clamp_4251 = ((add_4250 <= 70) ? 70 : ((add_4250 >= 100) ? 100 : add_4250));
		double mul_4217 = (clamp_4251 * 0.01);
		int lt_4258 = (m_morph_7 < 50);
		double mul_4253 = (lt_4258 * m_morph_7);
		double mul_4252 = (mul_4253 * -1.2);
		double add_4257 = (mul_4252 + 30);
		double abs_4256 = fabs(add_4257);
		double mul_4255 = (abs_4256 * -1);
		double add_4254 = (mul_4255 + 30);
		// the main sample loop;
		while ((__n--)) { 
			const double in1 = (*(__in1++));
			double tap_4240 = m_delay_3.read_cubic(mstosamps_4241);
			double mix_4285 = (m_y_1 + (clamp_4225 * (tap_4240 - m_y_1)));
			double mix_4222 = mix_4285;
			double mul_4237 = (mix_4222 * mul_4220);
			double dcblock_4214 = m_dcblock_11(mul_4237);
			double clamp_4215 = ((dcblock_4214 <= -1) ? -1 : ((dcblock_4214 >= 1) ? 1 : dcblock_4214));
			m_cycle_12.freq(m_rate_8);
			double cycle_4228 = m_cycle_12(__sinedata);
			double cycleindex_4229 = m_cycle_12.phase();
			double add_4227 = (cycle_4228 + 1);
			double mul_4226 = (add_4227 * 0.5);
			double mul_4230 = (m_depth_6 * mul_4226);
			double add_4259 = (add_4254 + mul_4230);
			double mstosamps_4221 = (add_4259 * (samplerate * 0.001));
			double tap_4235 = m_delay_2.read_linear(mstosamps_4221);
			double mul_4233 = (tap_4235 * mul_4217);
			double mul_4231 = (tap_4235 * mul_4219);
			double add_4236 = (mix_4222 + mul_4231);
			double mul_4232 = (add_4236 * mul_4218);
			double add_4213 = (mul_4232 + mul_4233);
			double mul_4238 = (add_4213 * mul_4216);
			double out1 = (mul_4238 + in1);
			double y0_next_4260 = mix_4222;
			m_delay_3.write((clamp_4215 + in1));
			m_delay_2.write(add_4236);
			m_y_1 = y0_next_4260;
			m_delay_2.step();
			m_delay_3.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			
		};
		return __exception;
		
	};
	inline void set_repeats(double _value) {
		m_repeats_4 = (_value < 0 ? 0 : (_value > 100 ? 100 : _value));
	};
	inline void set_time(double _value) {
		m_time_5 = (_value < 20 ? 20 : (_value > 1000 ? 1000 : _value));
	};
	inline void set_depth(double _value) {
		m_depth_6 = (_value < 0 ? 0 : (_value > 5 ? 5 : _value));
	};
	inline void set_morph(double _value) {
		m_morph_7 = (_value < 0 ? 0 : (_value > 100 ? 100 : _value));
	};
	inline void set_rate(double _value) {
		m_rate_8 = (_value < 0.1 ? 0.1 : (_value > 10 ? 10 : _value));
	};
	inline void set_mix(double _value) {
		m_mix_9 = (_value < 0 ? 0 : (_value > 100 ? 100 : _value));
	};
	inline void set_cutoff(double _value) {
		m_cutoff_10 = (_value < 500 ? 500 : (_value > 6000 ? 6000 : _value));
	};
	
} State;


/// 
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs 

int gen_kernel_numins = 1;
int gen_kernel_numouts = 1;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 7; }

/// Assistive lables for the signal inputs and outputs 

const char * gen_kernel_innames[] = { "in1" };
const char * gen_kernel_outnames[] = { "out1" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) { 
	State * self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) { 
	State * self = (State *)cself;
	self->reset(cself->sr, cself->vs); 
}

/// Set a parameter of a State object 

void setparameter(CommonState *cself, long index, double value, void *ref) {
	State * self = (State *)cself;
	switch (index) {
		case 0: self->set_repeats(value); break;
		case 1: self->set_time(value); break;
		case 2: self->set_depth(value); break;
		case 3: self->set_morph(value); break;
		case 4: self->set_rate(value); break;
		case 5: self->set_mix(value); break;
		case 6: self->set_cutoff(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object 

void getparameter(CommonState *cself, long index, double *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_repeats_4; break;
		case 1: *value = self->m_time_5; break;
		case 2: *value = self->m_depth_6; break;
		case 3: *value = self->m_morph_7; break;
		case 4: *value = self->m_rate_8; break;
		case 5: *value = self->m_mix_9; break;
		case 6: *value = self->m_cutoff_10; break;
		
		default: break;
	}
}

/// Allocate and configure a new State object and it's internal CommonState:

void * create(double sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(7 * sizeof(ParamInfo));
	self->__commonstate.numparams = 7;
	// initialize parameter 0 ("m_repeats_4")
	pi = self->__commonstate.params + 0;
	pi->name = "repeats";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_repeats_4;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_time_5")
	pi = self->__commonstate.params + 1;
	pi->name = "time";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_time_5;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 1000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_depth_6")
	pi = self->__commonstate.params + 2;
	pi->name = "depth";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_depth_6;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 5;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_morph_7")
	pi = self->__commonstate.params + 3;
	pi->name = "morph";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_morph_7;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_rate_8")
	pi = self->__commonstate.params + 4;
	pi->name = "rate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_rate_8;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 10;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_mix_9")
	pi = self->__commonstate.params + 5;
	pi->name = "mix";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_mix_9;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_cutoff_10")
	pi = self->__commonstate.params + 6;
	pi->name = "cutoff";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_cutoff_10;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 500;
	pi->outputmax = 6000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) { 
	State * self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self; 
}


} // gen_exported::
