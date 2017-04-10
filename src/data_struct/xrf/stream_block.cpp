/***
Copyright (c) 2016, UChicago Argonne, LLC. All rights reserved.

Copyright 2016. UChicago Argonne, LLC. This software was produced
under U.S. Government contract DE-AC02-06CH11357 for Argonne National
Laboratory (ANL), which is operated by UChicago Argonne, LLC for the
U.S. Department of Energy. The U.S. Government has rights to use,
reproduce, and distribute this software.  NEITHER THE GOVERNMENT NOR
UChicago Argonne, LLC MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR
ASSUMES ANY LIABILITY FOR THE USE OF THIS SOFTWARE.  If software is
modified to produce derivative works, such modified software should
be clearly marked, so as not to confuse it with the version available
from ANL.

Additionally, redistribution and use in source and binary forms, with
or without modification, are permitted provided that the following
conditions are met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in
      the documentation and/or other materials provided with the
      distribution.

    * Neither the name of UChicago Argonne, LLC, Argonne National
      Laboratory, ANL, the U.S. Government, nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY UChicago Argonne, LLC AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL UChicago
Argonne, LLC OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
***/

/// Initial Author <2017>: Arthur Glowacki



#include "stream_block.h"

namespace data_struct
{
namespace xrf
{

//-----------------------------------------------------------------------------

Stream_Block::Stream_Block(size_t row,
                           size_t col,
                           std::vector<fitting::routines::Base_Fit_Routine *> fit_routines,
                           Fit_Element_Map_Dict * elements_to_fit_)
{

    _row = row;
    _col = col;
    elements_to_fit = elements_to_fit_;

    if(elements_to_fit == nullptr)
    {
        //throw Exception;
    }

    fitting_blocks.resize(fit_routines.size());
    int idx = 0;
    for(auto fit_routine : fit_routines)
    {
        fitting_blocks[idx].fit_routine = fit_routine;
        //fitting_blocks[idx].out_fit_counts
        for(auto& e_itr : *elements_to_fit)
        {
            fitting_blocks[idx].fit_counts.emplace(std::pair<std::string, real_t> (e_itr.first, (real_t)0.0));
        }
        fitting_blocks[idx].fit_counts.emplace(std::pair<std::string, real_t> (STR_NUM_ITR, (real_t)0.0));
        idx++;
    }

}

//-----------------------------------------------------------------------------

Stream_Block::~Stream_Block()
{

}

//-----------------------------------------------------------------------------

} //namespace xrf
} //namespace data_struct
