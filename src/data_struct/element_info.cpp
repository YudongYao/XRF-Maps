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

/// Initial Author <2016>: Arthur Glowacki



#include "element_info.h"
#include <cmath>

namespace data_struct
{

// ----------------------------------------------------------------------------

template<typename T_real>
Element_Info<T_real>::Element_Info()
{

    number = 0;
    name = " ";
    density = 1.0;
    mass = 1.0;

	T_real zero = (T_real)0.0;

    xrf.emplace(std::make_pair("ka1", zero));
    xrf.emplace(std::make_pair("ka2", zero));
    xrf.emplace(std::make_pair("kb1", zero));
    xrf.emplace(std::make_pair("kb2", zero));

    xrf.emplace(std::make_pair("la1", zero));
    xrf.emplace(std::make_pair("la2", zero));
    xrf.emplace(std::make_pair("lb1", zero));
    xrf.emplace(std::make_pair("lb2", zero));
    xrf.emplace(std::make_pair("lb3", zero));
    xrf.emplace(std::make_pair("lb4", zero));
    xrf.emplace(std::make_pair("lb5", zero));

    xrf.emplace(std::make_pair("lg1", zero));
    xrf.emplace(std::make_pair("lg2", zero));
    xrf.emplace(std::make_pair("lg3", zero));
    xrf.emplace(std::make_pair("lg4", zero));
    xrf.emplace(std::make_pair("ll", zero));
    xrf.emplace(std::make_pair("ln", zero));

    xrf.emplace(std::make_pair("ma1", zero));
    xrf.emplace(std::make_pair("ma2", zero));
    xrf.emplace(std::make_pair("mb", zero));
    xrf.emplace(std::make_pair("mg", zero));


    xrf_abs_yield.emplace(std::make_pair("ka1", zero));
    xrf_abs_yield.emplace(std::make_pair("ka2", zero));
    xrf_abs_yield.emplace(std::make_pair("kb1", zero));
    xrf_abs_yield.emplace(std::make_pair("kb2", zero));

    xrf_abs_yield.emplace(std::make_pair("la1", zero));
    xrf_abs_yield.emplace(std::make_pair("la2", zero));
    xrf_abs_yield.emplace(std::make_pair("lb1", zero));
    xrf_abs_yield.emplace(std::make_pair("lb2", zero));
    xrf_abs_yield.emplace(std::make_pair("lb3", zero));
    xrf_abs_yield.emplace(std::make_pair("lb4", zero));
    xrf_abs_yield.emplace(std::make_pair("lb5", zero));

    xrf_abs_yield.emplace(std::make_pair("lg1", zero));
    xrf_abs_yield.emplace(std::make_pair("lg2", zero));
    xrf_abs_yield.emplace(std::make_pair("lg3", zero));
    xrf_abs_yield.emplace(std::make_pair("lg4", zero));
    xrf_abs_yield.emplace(std::make_pair("ll", zero));
    xrf_abs_yield.emplace(std::make_pair("ln", zero));

    xrf_abs_yield.emplace(std::make_pair("ma1", zero));
    xrf_abs_yield.emplace(std::make_pair("ma2", zero));
    xrf_abs_yield.emplace(std::make_pair("mb", zero));
    xrf_abs_yield.emplace(std::make_pair("mg", zero));

    yieldD.emplace(std::make_pair("k", zero));
    yieldD.emplace(std::make_pair("l1", zero));
    yieldD.emplace(std::make_pair("l2", zero));
    yieldD.emplace(std::make_pair("l3", zero));
    yieldD.emplace(std::make_pair("m", zero));

    bindingE.emplace(std::make_pair("K", zero));

    bindingE.emplace(std::make_pair("L1", zero));
    bindingE.emplace(std::make_pair("L2", zero));
    bindingE.emplace(std::make_pair("L3", zero));

    bindingE.emplace(std::make_pair("M1", zero));
    bindingE.emplace(std::make_pair("M2", zero));
    bindingE.emplace(std::make_pair("M3", zero));
    bindingE.emplace(std::make_pair("M4", zero));
    bindingE.emplace(std::make_pair("M5", zero));

    bindingE.emplace(std::make_pair("N1", zero));
    bindingE.emplace(std::make_pair("N2", zero));
    bindingE.emplace(std::make_pair("N3", zero));
    bindingE.emplace(std::make_pair("N4", zero));
    bindingE.emplace(std::make_pair("N5", zero));
    bindingE.emplace(std::make_pair("N6", zero));
    bindingE.emplace(std::make_pair("N7", zero));

    bindingE.emplace(std::make_pair("O1", zero));
    bindingE.emplace(std::make_pair("O2", zero));
    bindingE.emplace(std::make_pair("O3", zero));
    bindingE.emplace(std::make_pair("O4", zero));
    bindingE.emplace(std::make_pair("O5", zero));

    bindingE.emplace(std::make_pair("P1", zero));
    bindingE.emplace(std::make_pair("P2", zero));
    bindingE.emplace(std::make_pair("P3", zero));


    jump.emplace(std::make_pair("K", zero));

    jump.emplace(std::make_pair("L1", zero));
    jump.emplace(std::make_pair("L2", zero));
    jump.emplace(std::make_pair("L3", zero));

    jump.emplace(std::make_pair("M1", zero));
    jump.emplace(std::make_pair("M2", zero));
    jump.emplace(std::make_pair("M3", zero));
    jump.emplace(std::make_pair("M4", zero));
    jump.emplace(std::make_pair("M5", zero));

    jump.emplace(std::make_pair("N1", zero));
    jump.emplace(std::make_pair("N2", zero));
    jump.emplace(std::make_pair("N3", zero));
    jump.emplace(std::make_pair("N4", zero));
    jump.emplace(std::make_pair("N5", zero));

    jump.emplace(std::make_pair("O1", zero));
    jump.emplace(std::make_pair("O2", zero));
    jump.emplace(std::make_pair("O3", zero));
}

// ----------------------------------------------------------------------------

template<typename T_real>
Element_Info<T_real>::~Element_Info()
{
    xrf.clear();
    xrf_abs_yield.clear();
    yieldD.clear();
    bindingE.clear();
    jump.clear();

    f1_atomic_scattering_real.clear();
    f2_atomic_scattering_imaginary.clear();
    extra_energies.clear();
    extra_f1.clear();
    extra_f2.clear();
}

// ----------------------------------------------------------------------------

template<typename T_real>
void Element_Info<T_real>::init_f_energies(int len)
{
    f1_atomic_scattering_real.resize(len);
    f2_atomic_scattering_imaginary.resize(len);
}

// ----------------------------------------------------------------------------

template<typename T_real>
void Element_Info<T_real>::init_extra_energies(int len)
{
    extra_energies.resize(len);
    extra_f1.resize(len);
    extra_f2.resize(len);
}

// ----------------------------------------------------------------------------

template<typename T_real>
void Element_Info<T_real>::get_energies_between(T_real energy, T_real* out_low, T_real* out_high, size_t* out_low_idx, size_t* out_high_idx)
{
    *out_low_idx = 0;
    *out_high_idx = energies->size()-1;
    for(size_t l = 0; l < energies->size()-1; l++)
    {
        if(energy < (*energies)[l+1])
        {
            *out_low_idx = l;
            *out_low = (*energies)[l];
            break;
        }
    }
    for(size_t h = energies->size()-1; h > 1; h--)
    {
        if(energy > (*energies)[h-1])
        {
            *out_high_idx = h;
            *out_high = (*energies)[h];
            break;
        }
    }
}

// ----------------------------------------------------------------------------

template<typename T_real>
T_real Element_Info<T_real>::calc_beta(T_real density_val, T_real energy)
{
    T_real beta = 0.0;
    T_real molecules_per_cc = 0.0;
    T_real atwt = Element_Weight<T_real>.at(this->number);
    size_t low_e_idx=0, high_e_idx=0;
    bool found_indexes = false;

    ////z = wo+1
    if (atwt != 0.0)
    {
        molecules_per_cc = density_val * AVOGADRO / atwt;
    }

    T_real wavelength_angstroms = HC_ANGSTROMS / energy;
    // This constant has wavelength in angstroms and then
    // they are converted to centimeters.
    T_real constant = RE * ((T_real)1.0e-16 * wavelength_angstroms * wavelength_angstroms) * molecules_per_cc / ((T_real)2.0 * (T_real)M_PI);


    for(size_t i=1; i< energies->size(); i++)
    {
        if( (*energies)[i] > energy)
        {
            low_e_idx = i - 1;
            high_e_idx = i;
            found_indexes = true;
            break;
        }
    }
    if(false == found_indexes)
    {
        //if(name != "Be" && name != "Ge")
        //{
        //    logW<<"Could not find energy index for element "<< name <<"! Defaulting to 0\n";
        //}
        return beta;
    }

    T_real ln_lower_energy = std::log( (*energies)[low_e_idx] );
    T_real ln_higher_energy = std::log( (*energies)[high_e_idx] );
    T_real fraction = (std::log(energy) - ln_lower_energy) / (ln_higher_energy - ln_lower_energy);

    ////T_real f1_lower = f1_atomic_scattering_real[low_e_idx];
    ////T_real f1_higher = f1_atomic_scattering_real[high_e_idx];
    ////T_real f1_array = f1_lower + fraction * (f1_higher - f1_lower);

    T_real ln_f2_lower = std::log( std::abs(f2_atomic_scattering_imaginary[low_e_idx]) );
    T_real ln_f2_higher = std::log( std::abs(f2_atomic_scattering_imaginary[high_e_idx]) );
    T_real f2_array = std::exp( ln_f2_lower + fraction * (ln_f2_higher - ln_f2_lower) );

    ////delta_array = constant * f1_array
    beta = constant * f2_array;

    return beta;
}

// ----------------------------------------------------------------------------

template<typename T_real>
T_real Element_Info<T_real>::get_f2(T_real energy)
{
    T_real f2 = 0.0;
    T_real molecules_per_cc = 0.0;
   
    size_t low_e_idx = 0, high_e_idx = 0;
    bool found_indexes = false;

    for (size_t i = 1; i < energies->size(); i++)
    {
        if ((*energies)[i] > energy)
        {
            low_e_idx = i - 1;
            high_e_idx = i;
            found_indexes = true;
            break;
        }
    }
    if (false == found_indexes)
    {
        return f2;
    }

    T_real ln_lower_energy = std::log((*energies)[low_e_idx]);
    T_real ln_higher_energy = std::log((*energies)[high_e_idx]);
    T_real fraction = (std::log(energy) - ln_lower_energy) / (ln_higher_energy - ln_lower_energy);

    T_real ln_f2_lower = std::log(std::abs(f2_atomic_scattering_imaginary[low_e_idx]));
    T_real ln_f2_higher = std::log(std::abs(f2_atomic_scattering_imaginary[high_e_idx]));
    f2 = std::exp(ln_f2_lower + fraction * (ln_f2_higher - ln_f2_lower));

    return f2;
}

// ----------------------------------------------------------------------------
// -----------------------------Element_Info_Map-------------------------------
// ----------------------------------------------------------------------------
template<typename T_real>
Element_Info_Map<T_real>* Element_Info_Map<T_real>::_this_inst(0);

// ----------------------------------------------------------------------------
template<typename T_real>
Element_Info_Map<T_real>* Element_Info_Map<T_real>::inst()
{
    if (_this_inst == nullptr)
    {
        _this_inst = new Element_Info_Map();
    }
    return _this_inst;
}

// ----------------------------------------------------------------------------

template<typename T_real>
Element_Info_Map<T_real>::Element_Info_Map()
{
    generate_default_elements(1, 92);
}

// ----------------------------------------------------------------------------

template<typename T_real>
Element_Info_Map<T_real>::~Element_Info_Map()
{
    clear();
}

// ----------------------------------------------------------------------------

template<typename T_real>
void Element_Info_Map<T_real>::clear()
{
    for (auto &itr : _number_element_info_map)
	{
		delete itr.second;
	}
    _number_element_info_map.clear();
    _name_element_info_map.clear();
}

// ----------------------------------------------------------------------------

template<typename T_real>
void Element_Info_Map<T_real>::add_element(Element_Info<T_real>* element)
{
    // set global energies pointer
    element->energies = &_energies;
    _number_element_info_map[element->number] = element;
    _name_element_info_map[element->name] = element;
}

// ----------------------------------------------------------------------------

template<typename T_real>
T_real Element_Info_Map<T_real>::calc_beta(std::string element_name, T_real density, T_real energy)
{
    T_real beta = 0.0;
    if (_name_element_info_map.count(element_name) > 0)
    {
        beta = _name_element_info_map.at(element_name)->calc_beta(density, energy);
    }
    else if(Henke_Compound_Density_Map<T_real>.count(element_name) > 0)
    {
        beta = calc_compound_beta(element_name, density, energy);
    }
    else
    {
        logW<<"Could not find element or compound "<<element_name<<"\n";
    }
    return beta;
}

// ----------------------------------------------------------------------------

template<typename T_real>
T_real Element_Info_Map<T_real>::calc_compound_beta(std::string compound_name, T_real density, T_real energy)
{

    //    return 0;
        //TODO: finish this function
    T_real beta = 0.0;
    T_real molecules_per_cc = 0.0;
    T_real atwt = 0.0;
    T_real f2 = 0;
    //"N:78.08,O:20.95,Ar:0.93"
    int idx = compound_name.find(",");
    while (idx > -1 || compound_name.length() > 0)
    {
        std::string sub_compound;
        if (idx > -1)
        {
            sub_compound = compound_name.substr(0, idx);
            compound_name = compound_name.substr(idx + 1);
        }
        else
        {
            sub_compound = compound_name;
            compound_name = "";
        }


        int idx2 = sub_compound.find(":");
        if (idx2 > -1)
        {
            std::string el_symb = sub_compound.substr(0, idx2);
            std::string str_amt = sub_compound.substr(idx2+1);

            Element_Info<T_real>* element_info = Element_Info_Map<T_real>::inst()->get_element(el_symb);
            if (element_info != nullptr)
            {
                //beta += element_info->calc_beta(density, energy);
                
                T_real amt = std::atof(str_amt.c_str());
                if (amt > 0 && Element_Weight<T_real>.count(element_info->number) > 0)
                {
                    T_real weight = Element_Weight<T_real>.at(element_info->number);
                    atwt += (amt * weight);
                    f2 += element_info->get_f2(energy);
                }
            }
        }

        idx = compound_name.find(",");
    }

    if (atwt != 0.0)
    {
        molecules_per_cc = density * AVOGADRO / atwt;
    }

    T_real wavelength_angstroms = HC_ANGSTROMS / energy;
    // This constant has wavelength in angstroms and then
    // they are converted to centimeters.
    T_real constant = RE * ((T_real)1.0e-16 * wavelength_angstroms * wavelength_angstroms) * molecules_per_cc / ((T_real)2.0 * (T_real)M_PI);

    beta = constant * f2;

    return beta;
}

// ----------------------------------------------------------------------------

template<typename T_real>
Element_Info<T_real>* Element_Info_Map<T_real>::get_element(int element_number)
{
    return _number_element_info_map[element_number];
}

// ----------------------------------------------------------------------------

template<typename T_real>
Element_Info<T_real>* Element_Info_Map<T_real>::get_element(std::string element_name)
{
    return _name_element_info_map[element_name];
}

// ----------------------------------------------------------------------------

template<typename T_real>
void Element_Info_Map<T_real>::generate_default_elements(int start_element, int end_element)
{
    for (int i = start_element; i <end_element; i++)
    {
        Element_Info<T_real>* element = new Element_Info<T_real>();
        element->number = i;
        element->name = Element_Symbols[i];
        element->energies = &_energies;
       _number_element_info_map.insert(std::pair<int, Element_Info<T_real>*>(element->number, element));
       _name_element_info_map.insert(std::pair<std::string, Element_Info<T_real>*>(element->name, element));
       _name_element_info_map.insert(std::pair<std::string, Element_Info<T_real>*>(element->name+"_L", element));
       _name_element_info_map.insert(std::pair<std::string, Element_Info<T_real>*>(element->name+"_M", element));
    }
}
// ----------------------------------------------------------------------------

} //namespace data_struct
