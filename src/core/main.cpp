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

#include "core/command_line_parser.h"
#include "core/process_streaming.h"
#include "core/process_whole.h"

// ----------------------------------------------------------------------------

void help()
{
    logit_s<<"Help: "<<std::endl;
    logit_s<<"Usage: xrf_maps [Options] [Fitting Routines] --dir [dataset directory] \n"<<std::endl;
    logit_s<<"Options: "<<std::endl;
    logit_s<<"--nthreads : <int> number of threads to use (default is all system threads) "<<std::endl;
    logit_s<<"--quantify-with : <standard.txt> File to use as quantification standard "<<std::endl;
    logit_s<<"--detector-range : <int:int> Start and end detector range. Defaults to 0:3 for 4 detector "<<std::endl;
    logit_s<<"--generate-avg-h5 : Generate .h5 file which is the average of all detectors .h50 - h.53 or range specified. "<<std::endl;
//    logit_s<<"--add-exchange : <us:ds:sr> Add exchange group into hdf5 file with normalized data.\n";
//    logit_s<<"    us = upstream ion chamber\n";
//    logit_s<<"    ds = downstream ion chamber\n";
//    logit_s<<"    sr = sr current. "<<std::endl;
    logit_s<<"--quick-and-dirty : Integrate the detector range into 1 spectra. "<<std::endl;
    logit_s<<"--optimize-fit-override-params : <int> Integrate the 8 largest mda datasets and fit with multiple params\n"<<
               "  1 = matrix batch fit\n  2 = batch fit without tails\n  3 = batch fit with tails\n  4 = batch fit with free E, everything else fixed"<<std::endl;
    logit_s<<"--optimizer <lmfit, mpfit> : Choose which optimizer to use for --optimize-fit-override-params or matrix fit routine \n"<<std::endl;
    logit_s<<"Fitting Routines: "<<std::endl;
    logit_s<<"--roi : ROI "<<std::endl;
    logit_s<<"--roi_plus : SVD method "<<std::endl;
    logit_s<<"--nnls : Non-Negative Least Squares"<<std::endl;
    logit_s<<"--tails : Fit with multiple parameters "<<std::endl;
    logit_s<<"--matrix : Fit with locked parameters \n"<<std::endl;
    logit_s<<"Dataset: "<<std::endl;
    logit_s<<"--dir : Dataset directory "<<std::endl;
    logit_s<<"--files : Dataset files: comma (',') separated if multiple \n"<<std::endl;
    logit_s<<"--confocal : load hdf confocal xrf datasets \n"<<std::endl;
    logit_s<<"Examples: "<<std::endl;
    logit_s<<"   Perform roi and matrix analysis on the directory /data/dataset1 "<<std::endl;
    logit_s<<"xrf_maps --roi --matrix --dir /data/dataset1 "<<std::endl;
    logit_s<<"   Perform roi and matrix analysis on the directory /data/dataset1 but only process scan1 and scan2 "<<std::endl;
    logit_s<<"xrf_maps --roi --matrix --dir /data/dataset1 --files scan1.mda,scan2.mda"<<std::endl;
    logit_s<<"   Perform roi, matrix, and nnls  analysis on the directory /data/dataset1, use maps_standard.txt information for quantification "<<std::endl;
    logit_s<<"xrf_maps --roi --matrix --nnls --quantify-with maps_standard.txt --dir /data/dataset1 "<<std::endl;
}

// ----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::string dataset_dir;
    std::vector<std::string> dataset_files;
    std::vector<std::string> optimize_dataset_files;
    std::string quant_standard_filename = "";
    std::string whole_command_line = "";
    bool is_confocal = false;
    bool generated_avg = false;

    //Default is to process detectors 0 through 3
    size_t detector_num_start = 0;
    size_t detector_num_end = 3;

    //Performance measure
    std::chrono::time_point<std::chrono::system_clock> start, end;

    //////// HENKE and ELEMENT INFO /////////////
    std::string element_csv_filename = "../reference/xrf_library.csv";
    std::string element_henke_filename = "../reference/henke.xdr";

    Command_Line_Parser clp(argc, argv);

    if( clp.option_exists("-h") )
    {
       help();
       return 0;
    }


    size_t num_threads = std::thread::hardware_concurrency() - 2;
    if ( clp.option_exists("--nthreads") )
    {
        num_threads = std::stoi(clp.get_option("--nthreads"));
    }

    //main structure for analysis job information
    data_struct::xrf::Analysis_Job analysis_job(num_threads);

    //Look for which analysis types we want to run
    if ( clp.option_exists("--tails") )
    {
        analysis_job.append_fit_routine(data_struct::xrf::GAUSS_TAILS);
    }
    if ( clp.option_exists("--matrix") )
    {
        analysis_job.append_fit_routine(data_struct::xrf::GAUSS_MATRIX);
    }
    if ( clp.option_exists("--roi") )
    {
        analysis_job.append_fit_routine(data_struct::xrf::ROI);
    }
    if ( clp.option_exists("--roi_plus") )
    {
        analysis_job.append_fit_routine(data_struct::xrf::SVD);
    }
    if ( clp.option_exists("--nnls") )
    {
        analysis_job.append_fit_routine(data_struct::xrf::NNLS);
    }

    //Check if we want to quantifiy with a standard
    if ( clp.option_exists("--quantify-with") )
    {
        analysis_job.quantificaiton_standard_filename(clp.get_option("--quantify-with"));
    }

    //Do we want to optimize our fitting parameters
    if( clp.option_exists("--optimize-fit-override-params") )
    {
        analysis_job.optimize_fit_override_params(true);

        std::string opt = clp.get_option("--optimize-fit-override-params");
        if(opt == "1")
            analysis_job.fit_params_preset(fitting::models::MATRIX_BATCH_FIT);
        else if(opt == "2")
            analysis_job.fit_params_preset(fitting::models::BATCH_FIT_NO_TAILS);
        else if(opt == "3")
            analysis_job.fit_params_preset(fitting::models::BATCH_FIT_WITH_TAILS);
        else if(opt == "4")
            analysis_job.fit_params_preset(fitting::models::BATCH_FIT_WITH_FREE_ENERGY);
        else
            logit<<"Defaulting optimize_fit_params_preset to batch fit without tails"<<std::endl;
    }

    //Which optimizer do we want to pick. Default is lmfit
    if( clp.option_exists("--optimizer"))
    {
        analysis_job.set_optimizer(clp.get_option("--optimizer"));
    }

    //Added exchange format to output file. Used as an interface to allow other analysis software to load out output file
    if( clp.option_exists("--add-exchange"))
    {
        //TODO:
    }

    //Should we sum up all the detectors and process it as one?
    if( clp.option_exists("--quick-and-dirty"))
    {
        analysis_job.quick_and_dirty(true);
        analysis_job.generate_average_h5(false);
    }
    //Should create an averaged file of all detectors processed
    else if(clp.option_exists("--generate-avg-h5"))
    {
        analysis_job.generate_average_h5(true);
    }


    else if(clp.option_exists("--confocal"))
    {
        is_confocal = true;
    }


    //TODO: add --quantify-only option if you already did the fits and just want to add quantification

    //What detector range should we process. Usually there are 4 detectors.
    // 0:3 will do the first 4 detectors
    // 0:1 will do the first 2 detectors
    // 2:3 will do the last 2 detectors
    if ( clp.option_exists("--detector-range") )
    {
        std::string detector_range_str = clp.get_option("--detector-range");
        if (detector_range_str.find(':') != std::string::npos )
        {
            // if we found a comma, split the string to get list of dataset files
            std::stringstream ss;
            ss.str(detector_range_str);
            std::string item;
            std::getline(ss, item, ':');
            detector_num_start = std::stoi(item);
            std::getline(ss, item, ':');
            detector_num_end = std::stoi(item);
        }
        else
        {
            detector_num_start = detector_num_end = std::stoi(detector_range_str);
        }
    }

    //Get the dataset directory you want to process
    dataset_dir = clp.get_option("--dir");
    if (dataset_dir.length() < 1)
    {
        help();
        return -1;
    }
    //add a slash if missing at the end
    if (dataset_dir.back() != '/' && dataset_dir.back() != '\\')
    {
        dataset_dir += "/";
    }

    //We save our ouput file in $dataset_directory/img.dat  Make sure we create this directory if it doesn't exist
    io::check_and_create_dirs(dataset_dir);


    //Check to make sure we have something to do. If not then show the help screen
    if (analysis_job.fit_routine_size() == 0 && analysis_job.optimize_fit_override_params() == false && clp.option_exists("--generate-avg-h5") == false)
    {
        help();
        return -1;
    }


    //Look if files were specified
    std::string dset_file = clp.get_option("--files");
    //if they were not then look for them in $dataset_directory/mda
    if (dset_file.length() < 1)
    {
        if(is_confocal)
        {
            dataset_files = io::find_all_dataset_files(dataset_dir, ".hdf5");
        }
        else
        {
            // find all files in the dataset
            dataset_files = io::find_all_dataset_files(dataset_dir + "mda/", ".mda");
        }
        if (dataset_files.size() == 0)
        {
            logit<<"Error: No mda files found in dataset directory "<<dataset_dir<<std::endl;
            return -1;
        }

        for (auto& itr : dataset_files)
        {
            optimize_dataset_files.push_back(itr);
        }

        io::sort_dataset_files_by_size(dataset_dir, &optimize_dataset_files);
        //if no files were specified only take the 8 largest datasets

        while (optimize_dataset_files.size() > 9)
        {
            optimize_dataset_files.pop_back();
        }

    }
    else if (dset_file.find(',') != std::string::npos )
    {
        // if we found a comma, split the string to get list of dataset files
        std::stringstream ss;
        ss.str(dset_file);
        std::string item;
        while (std::getline(ss, item, ','))
        {
            dataset_files.push_back(item);
            optimize_dataset_files.push_back(item);
        }
    }
    else
    {
        dataset_files.push_back(dset_file);
        optimize_dataset_files.push_back(dset_file);
    }

    //gen whole command line to save in hdf5 later
    for(int ic = 0; ic < argc; ic++)
    {
        whole_command_line += " " + std::string(argv[ic]);
    }
    analysis_job.command_line(whole_command_line);
    logit<<"whole command line : "<<whole_command_line<<std::endl;
    logit << "Processing detectors " << detector_num_start << " - "<< detector_num_end <<std::endl;

    start = std::chrono::system_clock::now();

    //load element information
    if(false == io::load_element_info(element_henke_filename, element_csv_filename, data_struct::xrf::Element_Info_Map::inst()))
    {
        logit<<"Error loading element information: "<<std::endl;
        return -1;
    }

    if(analysis_job.optimize_fit_override_params())
    {
        analysis_job.set_optimize_dataset_files(optimize_dataset_files);
    }

    analysis_job.set_dataset_directory(dataset_dir);
    analysis_job.set_dataset_files(dataset_files);

    // init our job and run
    if(analysis_job.init(detector_num_start, detector_num_end) )
    {
        if(analysis_job.optimize_fit_override_params())
        {
            analysis_job.set_dataset_files(optimize_dataset_files);
            //run_optimization_stream_pipeline(&analysis_job);
//            io::populate_netcdf_hdf5_files(dataset_dir);
            generate_optimal_params(&analysis_job);
            analysis_job.set_dataset_files(dataset_files);
        }

        if (analysis_job.quantificaiton_standard_filename().length() > 0)
        {
            perform_quantification(&analysis_job);
        }

        if( clp.option_exists("--stream"))
        {
            run_stream_pipeline(&analysis_job);
        }
        else
        {
            io::populate_netcdf_hdf5_files(dataset_dir);
            process_dataset_files(&analysis_job);
            for(std::string dataset_file : analysis_job.dataset_files())
            {
                io::generate_h5_averages(analysis_job.dataset_directory(), dataset_file, analysis_job.detector_num_start(), analysis_job.detector_num_end());
            }
            generated_avg=true;
        }

        //average all detectors to one files
        if(analysis_job.generate_average_h5() && generated_avg==false)
        {
            for(std::string dataset_file : analysis_job.dataset_files())
            {
                io::generate_h5_averages(analysis_job.dataset_directory(), dataset_file, analysis_job.detector_num_start(), analysis_job.detector_num_end());
            }
        }
    }
    else
    {
        logit<<"Error initializing analysis job"<<std::endl;
    }

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    logit << "=-=-=-=-=-=- Total elapsed time: " << elapsed_seconds.count() << "s =-=-=-=-=-=-=-\n\n";

    data_struct::xrf::Element_Info_Map::inst()->clear();

    return 0;
}
