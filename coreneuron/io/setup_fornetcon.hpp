/*
Copyright (c) 2016, Blue Brain Project
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
3. Neither the name of the copyright holder nor the names of its contributors
   may be used to endorse or promote products derived from this software
   without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _H_SETUP_FORNETCON_
#define _H_SETUP_FORNETCON_

#include "coreneuron/sim/multicore.hpp"

namespace coreneuron {

/**
   If FOR_NETCON in use, setup NrnThread fornetcon related info.

   i.e NrnThread._fornetcon_perm_indices, NrnThread._fornetcon_weight_perm,
   and the relevant dparam element of each mechanism instance that uses
   a FOR_NETCON statement.

   Makes use of nrn_fornetcon_cnt_, nrn_fornetcon_type_,
   and nrn_fornetcon_index_ that were specified during registration of
   mechanisms that use FOR_NETCON.

   nrn_fornetcon_cnt_ is the number of mechanisms that use FOR_NETCON,
   nrn_fornetcon_type_ is an int array of size nrn_fornetcon_cnt, that specifies
   the mechanism type.
   nrn_fornetcon_index_ is an int array of size nrn_fornetcon_cnt, that
   specifies the index into an instance's dparam int array having the
   fornetcon semantics.

   FOR_NETCON (args) means to loop over all NetCon connecting to this
   target instance and args are the names of the items of each NetCon's
   weight vector (same as the enclosing NET_RECEIVE but possible different
   local names).

   NrnThread._weights is a vector of weight groups where the number of groups
   is the number of NetCon in this thread and each group has a size
   equal to the number of args in the target NET_RECEIVE block. The order
   of these groups is the NetCon Object order in HOC (the construction order).
   So the weight vector indices for the NetCons in the FOR_NETCON loop
   are not adjacent.

   NrnThread._fornetcon_weight_perm is an index vector into the
   NrnThread._weight vector such that the list of NetCon that targets a
   mechanism instance are adjacent.
   NrnThread._fornetcon_perm_indices is an index vector into the
   NrnThread._fornetcon_weight_perm to the first of the list of NetCon weights
   that target the instance. The index of _fornetcon_perm_indices
   containing this first in the list is stored in the mechanism instances
   dparam at the dparam's semantic fornetcon slot. (Note that the next index
   points to the first index of the next target instance.)
   
**/

void setup_fornetcon_info(NrnThread& nt);

}  // namespace coreneuron
#endif //_H_SETUP_FORNETCON_
