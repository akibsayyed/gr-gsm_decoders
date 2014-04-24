/* -*- c++ -*- */
/* 
 * Copyright 2014 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include <gsmtap.h>
#include "ccch_decoder_impl.h"

//v skompilować blok
//v dodać wejście wyjście message
//-dynamiczna zmiana grafu - niepotrzebna w tym momencie
//-deinterleaving 
//-dekodowanie crc
//-dekodowanie

namespace gr {
  namespace gsm_decoders {
    void ccch_decoder_impl::decode(pmt::pmt_t msg)
    {
    	unsigned char iBLOCK[BLOCKS*iBLOCK_SIZE], hl, hn, conv_data[CONV_SIZE], decoded_data[PARITY_OUTPUT_SIZE];
        d_bursts[d_collected_bursts_num] = msg;
        d_collected_bursts_num++;
        //get convecutive bursts
        pmt::pmt_t header_blob = pmt::car(msg);
        gsmtap_hdr * header = (gsmtap_hdr *)pmt::blob_data(header_blob);
        
        if(d_collected_bursts_num==4)
        {
            d_collected_bursts_num=0;
            //reorganize data
            for(int ii = 0; ii < 4; ii++)
            {
                pmt::pmt_t burst_content = pmt::cdr(d_bursts[ii]);
                int8_t * burst_bits = (int8_t *)pmt::blob_data(burst_content);

	            for(int jj = 0; jj < 57; jj++)
	            {
		            iBLOCK[ii*iBLOCK_SIZE+jj] = burst_bits[jj + 3];
		            iBLOCK[ii*iBLOCK_SIZE+jj+57] = burst_bits[jj + 88]; //88 = 3+57+1+26+1
	            }
            }
            //deinterleave
	        for (int k = 0; k < CONV_SIZE; k++)
	        {
		        conv_data[k] = iBLOCK[interleave_trans[k]];
            }
            //convolutional code decode
	        int errors = conv_decode(decoded_data, conv_data);
	        std::cout << "Errors:" << errors << " " << parity_check(decoded_data) << std::endl;
	        // check parity
	        // If parity check error detected try to fix it.
	        
	        if (parity_check(decoded_data))
	        {
		        FC_init(&fc_ctx, 40, 184);
		        unsigned char crc_result[224];
		        if (FC_check_crc(&fc_ctx, decoded_data, crc_result) == 0)
		        {
			        //("error: sacch: parity error (errors=%d fn=%d)\n", errors, ctx->fn);
			        std::cout << "Lol!" << std::endl;
			        errors = -1;
		        } else {
			        //DEBUGF("Successfully corrected parity bits! (errors=%d fn=%d)\n", errors, ctx->fn);
			        std::cout << "Super!" << std::endl;
			        memcpy(decoded_data, crc_result, sizeof crc_result);
			        errors = 0;
		        }
	        } else {
	            std::cout << "Nie ma niczego do poprawiania" << std::endl;
	        }
        }
        return;
    }

    ccch_decoder::sptr
    ccch_decoder::make()
    {
      return gnuradio::get_initial_sptr
        (new ccch_decoder_impl());
    }

    /*
     *
     */
    ccch_decoder_impl::ccch_decoder_impl()
      : gr::block("ccch_decoder",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
              d_collected_bursts_num(0)
    {
        //initialize de/interleaver
    	int j, k, B;
    	for (k = 0; k < CONV_SIZE; k++)
	    {
		    B = k % 4;
		    j = 2 * ((49 * k) % 57) + ((k % 8) / 4);
		    interleave_trans[k] = B * 114 + j; //114=57 + 57
	    }

		FC_init(&fc_ctx, 40, 184);
        message_port_register_in(pmt::mp("bursts_in"));
        set_msg_handler(pmt::mp("bursts_in"), boost::bind(&ccch_decoder_impl::decode, this, _1));
        message_port_register_out(pmt::mp("msgs_out"));
    }

    /*
     *
     */
    ccch_decoder_impl::~ccch_decoder_impl()
    {
    }
  } /* namespace gsm_decoders */
} /* namespace gr */

