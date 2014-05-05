/* -*- c++ -*- */
/* GNU GENERAL PUBLIC LICENSE
 */


#ifndef INCLUDED_GSM_DECODERS_GET_CCCH_BURSTS_H
#define INCLUDED_GSM_DECODERS_GET_CCCH_BURSTS_H

#include <gsm_decoders/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace gsm_decoders {

    /*!
     * \brief <+description of block+>
     * \ingroup gsm_decoders
     *
     */
    class GSM_DECODERS_API get_ccch_bursts : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<get_ccch_bursts> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of gsm_decoders::get_ccch_bursts.
       *
       * To avoid accidental use of raw pointers, gsm_decoders::get_ccch_bursts's
       * constructor is in a private implementation
       * class. gsm_decoders::get_ccch_bursts::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace gsm_decoders
} // namespace gr

#endif /* INCLUDED_GSM_DECODERS_GET_CCCH_BURSTS_H */

