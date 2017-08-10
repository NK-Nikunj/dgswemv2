#include "../../general_definitions.hpp"

#include "../../preprocessor/input_parameters.hpp"
#include "../../stepper.hpp"
#include "../../initialize_mesh.hpp"
#include "../../run_simulation.hpp"

#include "swe_problem.hpp"
#include "swe_kernels.hpp"

#include <hpx/hpx_init.hpp>
#include <hpx/hpx.hpp>

int main(int argc, char* argv[]) {
    return hpx::init(argc, argv);
}

int hpx_main(int argc, char* argv[]) {
    boost::program_options::options_description op_desc("Allowed options");

    op_desc.add_options()                                                                //
        ("help", "produce help message")                                                 //
        ("input-file", boost::program_options::value<std::string>(), "set input file");  //
    
    boost::program_options::positional_options_description pos_opt;
    pos_opt.add("input-file", -1);

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(op_desc).positional(pos_opt).run(), vm);

    if (vm.count("help")) {
        std::cout << op_desc << "\n";
        return 1;
    }

    if (vm.count("input-file")) {
        const char* file_name = vm["input-file"].as<std::string>().c_str();

        const InputParameters input(file_name);

        printf("Starting program %s with p=%d for %s mesh\n\n",
               file_name,
               input.polynomial_order,
               input.mesh_file_name.c_str());

        auto mesh = initialize_mesh<SWE::Problem>(input.polynomial_order, input.mesh_data);

        SWE::Problem::initialize_data_kernel(*mesh, input.mesh_data);

        Stepper stepper(input.rk.nstages, input.rk.order, input.dt);

        auto t1 = std::chrono::high_resolution_clock::now();
        run_simulation<SWE::Problem>(input.T_end, stepper, *mesh);
        auto t2 = std::chrono::high_resolution_clock::now();

        std::cout << "Time Elapsed (in us): " << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()
                  << "\n";

        delete mesh;
    } else {
        std::cout << "Input file is not set.\n";
    }

    return hpx::finalize();  // Handles HPX shutdown
}