#include <hpx/hpx.hpp>
#include <hpx/hpx_init.hpp>
#include <hpx/hpx_main.hpp>
#include <hpx/include/iostreams.hpp>
#include <hpx/include/components.hpp>
#include <hpx/include/lcos.hpp>

#include "general_definitions.hpp"
#include "problem/SWE/swe_definitions.hpp"

#include "problem/SWE/problem_function_files/swe_initial_condition_functions.hpp"
#include "problem/SWE/problem_function_files/swe_source_functions.hpp"
#include "problem/SWE/problem_function_files/swe_true_solution_functions.hpp"

#include "problem/SWE/discretization_RKDG/rkdg_swe_problem.hpp"
#include "problem/SWE/discretization_RKDG/kernels_preprocessor/rkdg_swe_kernels_preprocessor.hpp"
#include "problem/SWE/discretization_RKDG/kernels_processor/rkdg_swe_kernels_processor.hpp"
#include "problem/SWE/discretization_RKDG/kernels_postprocessor/rkdg_swe_kernels_postprocessor.hpp"

#include "simulation/simulation_RKDG/hpx/rkdg_simulation_hpx.hpp"
#include "simulation/stepper/rk_stepper.hpp"

RKDG_REGISTER_HPX_COMPONENTS(SWE::RKDG::Problem);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage\n"
                  << "    /path/to/RKDG_SWE_HPX input_file\n";
        return 1;
    } else {
        return hpx::init(argc, argv);
    }
}

int hpx_main(int argc, char* argv[]) {
    std::string input_string = std::string(argv[1]);

    const std::vector<hpx::naming::id_type> localities = hpx::find_all_localities();

    std::vector<RKDG::HPXSimulationClient<SWE::RKDG::Problem>> simulation_clients;
    simulation_clients.reserve(localities.size());

    auto t1 = std::chrono::high_resolution_clock::now();
    for (hpx::naming::id_type const& locality : localities) {
        simulation_clients.emplace_back(hpx::new_<RKDG::HPXSimulation<SWE::RKDG::Problem>>(locality, input_string));
    }

    std::vector<hpx::future<void>> run_futures;
    run_futures.reserve(simulation_clients.size());

    for (auto& sim_client : simulation_clients) {
        run_futures.push_back(sim_client.Run());
    }

    hpx::wait_all(run_futures);
    auto t2 = std::chrono::high_resolution_clock::now();

    std::cout << "Time Elapsed (in us): " << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()
              << std::endl;

    return hpx::finalize();
}
