/* -*- c++ -*- */

#define GSM_DECODERS_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "gsm_decoders_swig_doc.i"

%{
#include "gsm_decoders/ccch_decoder.h"
%}


%include "gsm_decoders/ccch_decoder.h"
GR_SWIG_BLOCK_MAGIC2(gsm_decoders, ccch_decoder);
