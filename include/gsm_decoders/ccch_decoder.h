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


#ifndef INCLUDED_GSM_DECODERS_CCCH_DECODER_H
#define INCLUDED_GSM_DECODERS_CCCH_DECODER_H

#include <gsm_decoders/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace gsm_decoders {

    /*!
     * \brief <+description of block+>
     * \ingroup gsm_decoders
     *
     */
    class GSM_DECODERS_API ccch_decoder : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<ccch_decoder> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of gsm_decoders::ccch_decoder.
       *
       * To avoid accidental use of raw pointers, gsm_decoders::ccch_decoder's
       * constructor is in a private implementation
       * class. gsm_decoders::ccch_decoder::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace gsm_decoders
} // namespace gr

#endif /* INCLUDED_GSM_DECODERS_CCCH_DECODER_H */

